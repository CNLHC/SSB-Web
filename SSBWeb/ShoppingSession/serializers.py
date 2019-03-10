from rest_framework import serializers
from .models import ShoppingSession,ShoppingCart

class SessionSerializer(serializers.ModelSerializer):
    class Meta:
        model = ShoppingSession
        fields= '__all__'


class CartSerializer(serializers.ModelSerializer):
    class Meta:
        model = ShoppingCart
        fields= '__all__'
