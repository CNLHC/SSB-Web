from rest_framework import viewsets,status
from rest_framework.decorators import action
from rest_framework.response import Response
from django.shortcuts import get_object_or_404
from .serializers import SessionSerializer
from CommodityManage.models import  Commodity,RFIDTag
from ShoppingSession.models import  ShoppingSession,SessionItems
from django_filters.rest_framework import DjangoFilterBackend
from urllib import  request as req
from urllib import  parse
from django.core.files import File

import  json
import  tempfile

class SessionViewset(viewsets.ModelViewSet):
    serializer_class = SessionSerializer
    queryset = ShoppingSession.SSB.all()
    filter_backends = (DjangoFilterBackend,)
    filterset_fields = ('State','ShoppingCart')


    def retrieve(self, request, *args, **kwargs):
        print(args,kwargs)
        SessionObj = ShoppingSession.SSB.getActive(kwargs.get('pk',-1))
        return Response(data  = SessionSerializer(SessionObj).data)

    def create(self, request, *args, **kwargs):
        data = request.data
        print(data,args,kwargs)
        try:
            ShoppingSession.SSB.getActive(data['ShoppingCart'])
        except ShoppingSession.DoesNotExist:
                return super(SessionViewset,self).create( request, *args, **kwargs)
        return Response(status=status.HTTP_406_NOT_ACCEPTABLE)

    @action(methods=['post'],detail=True)
    def add(self,request,pk):
        data = request.data.dict() #type:dict
        # SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        SessionObj = ShoppingSession.SSB.getActive(pk)
        Tag = get_object_or_404(RFIDTag,RFID=data.get('RFID'))
        try:
            sessionItem = SessionObj.Items.get(Item__id=Tag.CommodityItem.id)
        except SessionItems.DoesNotExist:
            sessionItem =SessionItems.objects.create(Session=SessionObj,Item=Tag.CommodityItem)

        sessionItem.Numbers+=1
        sessionItem.save()
        return Response(status=status.HTTP_200_OK)

    @action(methods=['post'],detail=True)
    def barCodeAdd(self,request,pk):
        try:
            data = request.data.dict() #type:dict
        except AttributeError:
            data = request.data

        barCode = data.get('barCode')
        if barCode is None:
            return  Response(status=status.HTTP_400_BAD_REQUEST)

        SessionObj = ShoppingSession.SSB.getActive(pk)


        try:
            Tag = RFIDTag.objects.get(RFID=barCode)
        except RFIDTag.DoesNotExist:
            data={"barcode":barCode}
            reqObj = req.Request("https://api.jisuapi.com/barcode2/query?appkey=31ebb5d61ef22191",data =parse.urlencode(data).encode() )
            res = req.urlopen(reqObj)
            resObj = json.loads(str(res.read(),'utf-8'))
            assert(resObj['status']=="0")
            resultObj = resObj['result']
            commodityPrice = 10.0 if len(resultObj['price'])==0 else float(resultObj['price'].replace('￥',''))


            tf = tempfile.NamedTemporaryFile(suffix='jpg')
            try:
                req.urlretrieve(resultObj['pic'],tf.name)
                with open(tf.name,'rb') as fp:
                    commodity=Commodity.objects.create(Name=resultObj['name'],Price=commodityPrice,Thumbnail=File(fp))
            except:
                commodity=Commodity.objects.create(Name=resultObj['name'],Price=commodityPrice)

            Tag = RFIDTag.objects.create(RFID=barCode , CommodityItem = commodity)

        try:
            sessionItem = SessionObj.Items.get(Item__id=Tag.CommodityItem.id)
        except SessionItems.DoesNotExist:
            sessionItem =SessionItems.objects.create(Session=SessionObj,Item=Tag.CommodityItem)

        sessionItem.Numbers+=1
        sessionItem.save()
        return Response(status=status.HTTP_200_OK)
    
    @action(methods=['post'],detail=True)
    def remove(self,request,pk):
        try:
            data = request.data.dict() #type:dict
        except AttributeError:
            data = request.data

        SessionObj = ShoppingSession.SSB.getActive(pk)
        # SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        Tag = get_object_or_404(RFIDTag,RFID=data.get('RFID'))
        try:
            sessionItem = SessionObj.Items.get(Item__id=Tag.CommodityItem.id)
            if sessionItem.Numbers>1:
                sessionItem.Numbers-=1
                sessionItem.save()
            else:
                sessionItem.delete()

        except SessionItems.DoesNotExist:
            pass
        return Response(status=status.HTTP_200_OK)

    @action(methods=['post'],detail=True)
    def removeByID(self,request,pk):
        try:
            data = request.data.dict() #type:dict
        except AttributeError:
            data = request.data
        SessionObj = ShoppingSession.SSB.getActive(pk)
        # SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        ItemID=data.get('ItemID')
        try:
            sessionItem = SessionObj.Items.all().get(Item=ItemID)
            sessionItem.delete()
        except SessionItems.DoesNotExist:
            print("not found")
            pass
        return Response(status=status.HTTP_200_OK)

    @action(methods=['post'],detail=True)
    def deal(self,request,pk):
        SessionObj = ShoppingSession.SSB.getActive(pk)
        # SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        SessionObj.State=SessionObj.SESSION_PAYING
        SessionObj.save()
        return Response(status=status.HTTP_200_OK)


    @action(methods=['post'],detail=True)
    def pay(self,request,pk):
        SessionObj = ShoppingSession.SSB.getActive(pk)
        # SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        SessionObj.State=SessionObj.SESSION_CLOSE
        SessionObj.save()
        return Response(status=status.HTTP_200_OK)
