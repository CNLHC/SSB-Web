from django.db import models
from django.utils.timezone import now

# Create your models here.

class ShoppingCart(models.Model):
    CartID = models.CharField(max_length=10,unique=True)


class SessionItems(models.Model):
    Session=models.ForeignKey('ShoppingSession.ShoppingSession',on_delete=models.CASCADE,related_name='Items')
    Item = models.ForeignKey('CommodityManage.Commodity',on_delete=models.CASCADE,related_name="SessionItem",)
    Numbers = models.IntegerField(default=0)

    def __str__(self):
        return '{Name}({Number})'.format(Name = self.Item.Name,Number=self.Numbers)

class ShoppingSession(models.Model):
    SESSION_SHOPPING="SHOPPING"
    SESSION_PAYING="PAYING"
    SESSION_CLOSE="CLOSE"
    SESSION_STATE=(
        (SESSION_SHOPPING,"正在购物"),
        (SESSION_PAYING,"正在付款"),
        (SESSION_CLOSE,"付款结束")
    )
    ShoppingCart  = models.ForeignKey(ShoppingCart,on_delete=models.CASCADE,related_name="shoppingSession")
    State = models.CharField(max_length=20,choices=SESSION_STATE,default=SESSION_SHOPPING)
    StartTime = models.DateTimeField(auto_created=True,default=now)
    EndTime = models.DateTimeField(null=True,default=None)

