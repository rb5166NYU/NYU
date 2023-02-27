import smtplib
from socket import *

def smtp_client(port=1025, mailserver='127.0.0.1'):
    msg = "\r\n My message"
    endmsg = "\r\n.\r\n"

    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((mailserver, port))

    recv = clientSocket.recv(1024).decode()

    heloCommand = 'HELO Alice\r\n'
    clientSocket.send(heloCommand.encode())
    recv1 = clientSocket.recv(1024).decode()

    sender = "MAIL FROM:<from@fromdomain.com>\r\n"
    clientSocket.send(mailFromCommand.encode())
    recv2 = clientSocket.recv(1024).decode()

    receivers = "RCPT TO:<my@emailadress.com'>\r\n"
    clientSocket.send(rcptToCommand.encode())
    recv3 = clientSocket.recv(1024).decode()

    dataCommand = "DATA\r\n"
    clientSocket.send(dataCommand.encode())
    recv4 = clientSocket.recv(1024).decode()

    clientSocket.send(msg.encode())

    clientSocket.send(endmsg.encode())
    recv5 = clientSocket.recv(1024).decode()

    quitCommand = "QUIT\r\n"
    clientSocket.send(quitCommand.encode())
    recv6 = clientSocket.recv(1024).decode()

    clientSocket.close()

    if name == 'main':
        smtp_client(1025, '127.0.0.1')




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

 
