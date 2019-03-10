from rest_framework.test import APITestCase
from Test.SetUpAll import SetUp
from CommodityManage.models import Commodity,RFIDTag
from ShoppingSession.models import ShoppingSession,ShoppingCart
import  random

class TestShoppingAPI(APITestCase):
    def setUp(self):
        SetUp()

    def testRepeatCreateSession(self):
        a=self.client.post('/api/session/',data={ 'ShoppingCart':2 })
        self.assertEquals(a.status_code,201)
        a=self.client.post('/api/session/',data={ 'ShoppingCart':2 })
        self.assertEquals(a.status_code,406)



