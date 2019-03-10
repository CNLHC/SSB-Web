from django.conf import  settings
from django.db.transaction import atomic
from CommodityManage.models import Commodity,RFIDTag
import  csv

@atomic
def SetUpCommodity():
    with open('{baseDir}/CommodityManage/TestUtil/CommodityList.csv'.format(baseDir=settings.BASE_DIR),'r',encoding='utf8') as fp:
        reader = csv.reader(fp)
        for RFID,Name,Price in reader:
            try:
                Commodity.objects.get(Name__exact=Name)
            except Commodity.DoesNotExist:
                Commodity.objects.create(Name=Name,Price=Price)

            try:
                RFIDTag.objects.get(RFID__exact=RFID)
            except RFIDTag.DoesNotExist:
                goodObj=Commodity.objects.get(Name__exact=Name)
                RFIDTag.objects.create(RFID=RFID,CommodityItem=goodObj)
