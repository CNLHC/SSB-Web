from django.db import models

# Create your models here.

class RFIDTag(models.Model):
    RFID=models.CharField(max_length=64,unique=True)
    CommodityItem = models.ForeignKey('CommodityManage.Commodity',on_delete=models.CASCADE,related_name='RFID')
    def __str__(self):
        return "({RFID})-->{Name}".format(RFID=self.RFID,Name=self.CommodityItem.Name)

class Commodity(models.Model):
    Name = models.CharField(max_length=100)
    Price = models.FloatField(default=0.0)
    Thumbnail =  models.FileField('media/')

    def __str__(self):
        return "({id}){Name}".format(id=self.id,Name=self.Name)

