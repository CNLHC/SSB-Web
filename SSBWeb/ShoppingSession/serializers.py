from rest_framework import serializers
from .models import ShoppingSession,ShoppingCart,SessionItems
from CommodityManage.serializers import CommoditySerializer

class CartSerializer(serializers.ModelSerializer):
    class Meta:
        model = ShoppingCart
        fields= '__all__'

class SessionItemSerializer(serializers.ModelSerializer):
    Commodity=CommoditySerializer(many=True,read_only=True )

    class Meta:
        model =  SessionItems
        fields= '__all__'

class SessionSerializer(serializers.ModelSerializer):
    Items=SessionItemSerializer(many=True,read_only=True)

    class Meta:
        model = ShoppingSession
        fields= '__all__'


