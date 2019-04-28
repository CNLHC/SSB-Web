from django.db import models
from django.utils.timezone import now


# Create your models here.

class ShoppingCart(models.Model):
    CartID = models.CharField(max_length=10,unique=True,verbose_name="终端唯一识别码")
    def __str__(self):
        return "购物车({0})".format(self.id)

class SessionItems(models.Model):
    Session=models.ForeignKey('ShoppingSession.ShoppingSession',on_delete=models.CASCADE,related_name='Items',verbose_name="商品")
    Item = models.ForeignKey('CommodityManage.Commodity',on_delete=models.CASCADE,related_name="SessionItem",verbose_name="商品")
    Numbers = models.IntegerField(default=0,verbose_name="数量")

    def __str__(self):
        return '{Name}({Number})'.format(Name = self.Item.Name,Number=self.Numbers)

    class Meta:
        verbose_name="订单商品"
        verbose_name_plural="订单商品信息"

class SessionManager(models.Manager):
    def get_queryset(self):
        return super().get_queryset()
    
    def getActive(self,CartID):
        return self.get_queryset().get(State=ShoppingSession.SESSION_SHOPPING)




class ShoppingSession(models.Model):
    SESSION_SHOPPING="SHOPPING"
    SESSION_PAYING="PAYING"
    SESSION_CLOSE="CLOSE"
    SESSION_STATE=(
        (SESSION_SHOPPING,"正在购物"),
        (SESSION_PAYING,"正在付款"),
        (SESSION_CLOSE,"付款结束")
    )
    ShoppingCart  = models.ForeignKey(ShoppingCart,on_delete=models.CASCADE,related_name="shoppingSession",verbose_name="购物车ID")
    State = models.CharField(max_length=20,choices=SESSION_STATE,default=SESSION_SHOPPING,verbose_name="购物状态")
    StartTime = models.DateTimeField(auto_created=True,default=now,verbose_name="订单创建时间")
    EndTime = models.DateTimeField(null=True,default=None,verbose_name="订单关闭时间")
    
    SSB=SessionManager()

    objects=models.Manager()
    
    class Meta:
        verbose_name="订单信息"
        verbose_name_plural="订单信息"



    def __str__(self):
        return "订单({0})(购物车ID{1})({2})".format(self.id,self.ShoppingCart.id,self.StartTime)


