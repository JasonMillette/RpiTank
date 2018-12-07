#!/usr/bin/python

import firebase_admin
from firebase_admin import credentials, db
import os

cred = credentials.Certificate('rpitank-8338d-firebase-adminsdk-cxhr8-21dfd0e67c.json')
firebase_admin.initialize_app(cred, {
        'databaseURL' : 'https://rpitank-8338d.firebaseio.com'
        })


x = "0"
y = "0"
while 1:
    pid = os.fork()
    if pid == 0:
        os.system("./motorsteven "+x+" "+y)
        exit()
    else :
        loc = db.reference('users').get()
        x = str(loc["X"])
        y = str(loc["Y"])
       # exit()
    #else :   
     #   os.system("./motorsteven "+x+" "+y)
      #  print x
       # print y


