from django.db import models

# Create your models here.

class RFIDTag(models.Model):
    RFID=models.CharField(max_length=64,unique=True)
    CommodityItem = models.ForeignKey('CommodityManage.Commodity',on_delete=models.CASCADE,related_name='RFID')
    def __str__(self):
        return "({RFID})-->{Name}".format(RFID=self.RFID,Name=self.CommodityItem.Name)
    class Meta:
        verbose_name="RFID标签管理"
        verbose_name_plural="RFID标签管理"


class Commodity(models.Model):
    Name = models.CharField(max_length=100,verbose_name="商品名称")
    Price = models.FloatField(default=0.0,verbose_name="商品价格")
    Thumbnail =  models.FileField('media/',blank=True)

    def __str__(self):
        return "({id}){Name}".format(id=self.id,Name=self.Name)

    class Meta:
        verbose_name="商品管理"
        verbose_name_plural="商品管理"

