from django.conf import  settings
from django.db.transaction import atomic
from  ShoppingSession.models import ShoppingCart

import  csv

@atomic
def SetUpShoppingCart():
    with open('{baseDir}/ShoppingSession/TestUtil/CartList.csv'.format(baseDir=settings.BASE_DIR),'r',encoding='utf8') as fp:
        reader = csv.reader(fp)
        for (CartID,) in reader:
            try:
                ShoppingCart.objects.get(CartID=CartID)
            except ShoppingCart.DoesNotExist:
                ShoppingCart.objects.create(CartID=CartID)
