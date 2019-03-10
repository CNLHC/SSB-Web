from rest_framework.test import APITestCase
from Test.SetUpAll import SetUp
from CommodityManage.models import Commodity,RFIDTag
from ShoppingSession.models import ShoppingSession,ShoppingCart
import  random

class TestShoppingScene(APITestCase):
    def setUp(self):
        SetUp()

    def testShopping(self):
        Tags =RFIDTag.objects.all()[:5] #type:List[Commodity]
        SessionInfo=self.client.post('/api/session/',data={ 'ShoppingCart':2 }).data
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[0].RFID})
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[1].RFID})
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[2].RFID})
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[3].RFID})
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[3].RFID})
        self.client.post('/api/session/{id}/add/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[3].RFID})
        se = ShoppingSession.objects.all().first() #type:ShoppingSession
        self.assertEquals(se.Items.count(),4)
        self.client.post('/api/session/{id}/remove/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[3].RFID})
        self.client.post('/api/session/{id}/remove/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[3].RFID})
        self.client.post('/api/session/{id}/remove/'.format(id=SessionInfo['id']),data={ 'RFID':Tags[0].RFID})
        self.assertEquals(se.Items.count(),3)

