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
pid = os.fork()
while 1:
    if pid == 0:
        loc = db.reference('users').get()
        x = str(loc["X"])
        y = str(loc["Y"])
        exit()
    else :   
        os.system("./motorsteven "+x+" "+y)
        print x
        print y


