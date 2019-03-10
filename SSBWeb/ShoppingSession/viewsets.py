from rest_framework import viewsets,status
from rest_framework.decorators import action
from rest_framework.response import Response
from django.shortcuts import get_object_or_404
from .serializers import SessionSerializer
from CommodityManage.models import  Commodity,RFIDTag
from ShoppingSession.models import  ShoppingSession,SessionItems

class SessionViewset(viewsets.ModelViewSet):
    serializer_class = SessionSerializer
    queryset = ShoppingSession.objects.all()

    @action(methods=['post'],detail=True)
    def add(self,request,pk):
        data = request.data.dict() #type:dict
        SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
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
        SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
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
    def deal(self,request,pk):
        SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        SessionObj.State=SessionObj.SESSION_PAYING
        SessionObj.save()
        return Response(status=status.HTTP_200_OK)


    @action(methods=['post'],detail=True)
    def pay(self,request,pk):
        SessionObj = get_object_or_404(ShoppingSession,pk=pk)  #type: ShoppingSession
        SessionObj.State=SessionObj.SESSION_CLOSE
        SessionObj.save()
        return Response(status=status.HTTP_200_OK)
