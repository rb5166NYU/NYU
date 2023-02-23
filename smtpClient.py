import time
from socket import *
from socket import socket

msg = "\r\n I love Computer Networks"
endmsg = "\r\n.\r\n"

mailserver = ("smtp.gmail.com", 587)  # Fill in start #Fill in end

clientSocket: socket = socket(AF_INET, SOCK_STREAM)
# clientSocket = ssl.wrap_socket(clientSocket)
clientSocket.connect(mailserver)

recv = clientSocket.recv(1024)
recv = recv.decode()
print("Message after connection request:" + recv)
if recv[:3] != '220':
    print('220 reply not received from server.')

heloCommand = 'HELO Alice\r\n'
clientSocket.send(heloCommand.encode())
recv1 = clientSocket.recv(1024)
recv1 = recv1.decode()
print("Message after EHLO command:" + recv1)
if recv1[:3] != '250':
    print('250 reply not received from server.')

# command = 'STARTTLS \r\n'
# command = command.encode()
# clientSocket.send(command)
# recv2 = clientSocket.recv(1024)
# recv2 = recv2.decode()
# print("Message after STARTTLS command:" + recv2)
# if recv2[:3] != '250':
#    print('250 reply not received from server.')


# Info for username and password
# username =  "heimdall1010@gmail.com" 	#input("Enter the username : ")
# password =  "Password" 				#input("Enter the password : ")
# base64_str = ("\x00"+username+"\x00"+password).encode()
# base64_str = base64.b64encode(base64_str)
# authMsg = "AUTH PLAIN ".encode()+base64_str+"\r\n".encode()
# clientSocket.send(authMsg)
# recv_auth = clientSocket.recv(1024)
# print(recv_auth.decode())

mailFrom = "MAIL FROM: <heimdall1010@gmail.com> \r\n"
clientSocket.send(mailFrom.encode())
recv2 = clientSocket.recv(1024)
recv2 = recv2.decode()
print("After MAIL FROM command: " + recv2)

rcptTo = "RCPT TO: <rb5166@nyu.edu> \r\n"
clientSocket.send(rcptTo.encode())
recv3 = clientSocket.recv(1024)
recv3 = recv3.decode()
print("After RCPT TO command: " + recv3)

data = "DATA\r\n"
clientSocket.send(data.encode())
recv4 = clientSocket.recv(1024)
recv4 = recv4.decode()
print("After DATA command: " + recv4)

# sub = input("Enter the subject : ")
subject = "Subject: SMTP Client Python Script \r\n\r\n"
clientSocket.send(subject.encode())
date = time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
date = date + "\r\n\r\n"
clientSocket.send(date.encode())
clientSocket.send(msg.encode())
clientSocket.send(endmsg.encode())
recv_msg = clientSocket.recv(1024)
print("Response after sending message body:" + recv_msg.decode())

quit = "qUIT\r\n"
clientSocket.send(quit.encode())
recv5 = clientSocket.recv(1024)
print(recv5.decode())
clientSocket.close()
