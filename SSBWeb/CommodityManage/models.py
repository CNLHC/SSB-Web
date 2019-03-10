from django.db import models

# Create your models here.

class RFIDTag(models.Model):
    RFID=models.CharField(max_length=64,unique=True)
    CommodityItem = models.ForeignKey('CommodityManage.Commodity',on_delete=models.CASCADE,related_name='RFID')

class Commodity(models.Model):
    Name = models.CharField(max_length=100)
    Price = models.FloatField(default=0.0)

