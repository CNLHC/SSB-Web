from rest_framework import viewsets,status
from rest_framework.decorators import action
from rest_framework.response import Response
from django.shortcuts import get_object_or_404
from .serializers import SessionSerializer
from CommodityManage.models import  Commodity,RFIDTag
from ShoppingSession.models import  ShoppingSession,SessionItems
from django_filters.rest_framework import DjangoFilterBackend

class SessionViewset(viewsets.ModelViewSet):
    serializer_class = SessionSerializer
    queryset = ShoppingSession.SSB.all()
    filter_backends = (DjangoFilterBackend,)
    filterset_fields = ('State','ShoppingCart')


    def retrieve(self, request, *args, **kwargs):
        print(args,kwargs)
        SessionObj = ShoppingSession.SSB.getActive(pk)
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
    def remove(self,request,pk):
        data = request.data.dict() #type:dict
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
