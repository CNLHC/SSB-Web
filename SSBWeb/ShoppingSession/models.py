from django.db import models

# Create your models here.

class ShoppingCart(models.Model):
    CartID = models.CharField(max_length=10)

class ShoppingSession(models.Model):
    StartTime = models.DateTimeField(auto_created=True)
    EndTime = models.DateTimeField(auto_created=True)
    ShoppingCart  = models.ForeignKey(ShoppingCart,on_delete=models.CASCADE,related_name="shoppingSession")
