#!/usr/bin/python

import firebase_admin
from firebase_admin import credentials, db
import os

#credentials needed to acess the database
cred = credentials.Certificate('rpitank-8338d-firebase-adminsdk-cxhr8-21dfd0e67c.json')
firebase_admin.initialize_app(cred, {
        'databaseURL' : 'https://rpitank-8338d.firebaseio.com'
        })

#initilize variables
x = "0"
y = "0"
while 1:    #go for ever
        
    pid = os.fork()#fork
    if pid == 0: #run the motors for the current coordinates
        os.system("./motorcontrol "+x+" "+y)
        exit()
    else :
        loc = db.reference('users').get()#get coordinates from the database
        x = str(loc["X"])
        y = str(loc["Y"])


