from django.conf import  settings
from django.db.transaction import atomic
from CommodityManage.models import Commodity,RFIDTag
import  csv
import  sqlite3
import  urllib.request
from django.core.files import File


conn = sqlite3.connect('{baseDir}/CommodityManage/TestUtil/book.db'.format(baseDir=settings.BASE_DIR))
cursor= conn.cursor()

@atomic
def SetUpCommodity():
    with open('{baseDir}/CommodityManage/TestUtil/CommodityList.csv'.format(baseDir=settings.BASE_DIR),'r',encoding='utf8') as fp:
        reader = csv.reader(fp)
        for RFID,Name,Price in reader:
            try:
                CObj=Commodity.objects.get(Name__exact=Name)
                CObj.Name=Name
                CObj.Price=Price
                CObj.save()
            except Commodity.DoesNotExist:
                Commodity.objects.create(Name=Name,Price=Price)

            try:
                RFIDObj=RFIDTag.objects.get(RFID__exact=RFID)
                RFIDObj.RFID=RFID
                RFIDObj.save()
            except RFIDTag.DoesNotExist:
                goodObj=Commodity.objects.get(Name__exact=Name)
                RFIDTag.objects.create(RFID=RFID,CommodityItem=goodObj)

    with open('{baseDir}/CommodityManage/TestUtil/BookList.txt'.format(baseDir=settings.BASE_DIR),'r',encoding='utf8') as fp:
        for ISBN in fp.readlines():
            for item in cursor.execute("SELECT * FROM book WHERE ISBN ={ISBN}".format(ISBN=ISBN)):
                ISBN,_,Image,Name,_,Pages,Publisher,Author,_=item
                DBName="{Name}-{Author}".format(Name=Name,Author=Author)
                Pages=int(Pages)

                try:
                    CObj=Commodity.objects.get(Name__exact=DBName)
                    CObj.Name=DBName
                    CObj.Price=Pages/10.0
                    CObj.save()

                except Commodity.DoesNotExist:
                    with open('{0}/{1}.jpg'.format(settings.MEDIA_ROOT,ISBN),'w+b')as tfp:
                        with urllib.request.urlopen(Image) as res:
                            tfp.write(res.read())
                    with open('{0}/{1}.jpg'.format(settings.MEDIA_ROOT,ISBN),'rb')as tfp:
                        Commodity.objects.create(Name=DBName,Price=Pages/10.0,Thumbnail=File(tfp))

