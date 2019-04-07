from django.contrib import admin
from  ShoppingSession.models import  ShoppingSession,SessionItems
from django import forms

from django.contrib import auth

# Register your models here.
admin.site.unregister(auth.models.User)
admin.site.unregister(auth.models.Group)

class SessionItemsAdmin(admin.StackedInline):
    model =  SessionItems



@admin.register(ShoppingSession)
class ShoppingSessionAdmin(admin.ModelAdmin):
    readonly_fields = ['StartTime','EndTime','ShoppingCart','State' ]
    inlines = [SessionItemsAdmin,]

admin.site.site_header = '易迈无人超市后台管理'


