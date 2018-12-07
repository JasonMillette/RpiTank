#!/usr/bin/python

import firebase_admin
from firebase_admin import credentials, db

cred = credentials.Certificate('rpitank-8338d-firebase-adminsdk-cxhr8-21dfd0e67c.json')
firebase_admin.initialize_app(cred, {
        'databaseURL' : 'https://rpitank-8338d.firebaseio.com'
        })



while 1:
    loc = db.reference('users').get()
    print 'X:',loc['X']
    print 'Y:',loc['Y']
