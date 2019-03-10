from django.urls import path
from rest_framework import routers
from ShoppingSession.viewsets import  SessionViewset

router = routers .SimpleRouter()
router.register('session',SessionViewset)

urlpatterns = router.urls

