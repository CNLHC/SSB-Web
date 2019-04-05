from django.contrib import admin
from .models import Commodity,RFIDTag

# Register your models here.

admin.site.register(Commodity)
admin.site.register(RFIDTag)
