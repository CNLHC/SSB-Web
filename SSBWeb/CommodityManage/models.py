from django.db import models

# Create your models here.

class RFIDTag(models.Model):
    ID = models.CharField(max_length=15)
    Commodity = models.ForeignKey(Commodity,on_delete=models.CASCADE,related_name="RFID")

class Commodity(models.Model):
    Name = models.CharField(max_length=100)
    Price = models.FloatField(default=0.0)

