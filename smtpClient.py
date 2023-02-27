import smtplib

sender = 'from@fromdomain.com'
receivers = ['my@emailadress.com']

message = """From: From Person <from@fromdomain.com>
To: To Person <to@todomain.com>
Subject: SMTP e-mail test

This is a test e-mail message.
"""

try:
    smtpObj = smtplib.SMTP('127.0.0.1', 1025)
    smtpObj.sendmail(sender, receivers, message)
    print ("Successfully sent email")
except smtplib.SMTPException:
    print ("Error: unable to send email")

    if name == 'main':
        smtp_client(1025, '127.0.0.1')
