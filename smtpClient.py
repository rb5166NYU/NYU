from socket import *
import time
from socket import socket
import base64

def smtp_client(port=1025, mailserver='127.0.0.1'):
    msg = "\r\n My message"
    endmsg = "\r\n.\r\n"

    # Create socket called clientSocket and establish a TCP connection with mailserver and port

    # Fill in start
    clientSocket: socket = socket(socket.AF_INET, socket.SOCK_STREAM)
    # clientSocket = ssl.wrap_socket(clientSocket)
    clientSocket.connect(mailserver)
    # Fill in end

    recv = clientSocket.recv(1024).decode()
    print(recv)  # You can use these print statement to validate return codes from the server.
    if recv[:3] != '220':
        print('220 reply not received from server.')

    # Send HELO command and print server response.
    heloCommand = 'HELO Alice\r\n'
    clientSocket.send(heloCommand.encode())
    recv1 = clientSocket.recv(1024).decode()
    print(recv1)
    if recv1[:3] != '250':
        print('250 reply not received from server.')

    command = 'STARTTLS \r\n'
    command = command.encode()
    clientSocket.send(command)
    recv2 = clientSocket.recv(1024)
    recv2 = recv2.decode()
    print("Message after STARTTLS command:" + recv2)
    if recv2[:3] != '250':
        print('260 reply not received from server.')

    # Send MAIL FROM command and handle server response.
    # Fill in start
    mailFrom = "MAIL FROM: <heimdall1010@gmail.com> \r\n"
    clientSocket.send(mailFrom.encode())
    recv2 = recv2.decode()
    print("After MAIL FROM command: " + recv2)
    # Fill in end

    # Send RCPT TO command and handle server response.
    # Fill in start
    rcptTo = "RCPT TO: <rb5166@nyu.edu> \r\n"
    clientSocket.send(rcptTo.encode())
    recv3 = clientSocket.recv(10485760)
    recv3 = recv3.decode()
    print("After RCPT TO command: " + recv3)

    # Fill in end

    # Send DATA command and handle server response.
    # Fill in start
    # Fill in end

    # Send message data.
    # Fill in start
    data = "DATA\r\n"
    clientSocket.send(data.encode())
    recv4 = clientSocket.recv(10485760)
    recv4 = recv4.decode()
    print("After DATA command: " + recv4)
    # Fill in end

    # Message ends with a single period, send message end and handle server response.
    # Fill in start
    subject = "Subject: SMTP Client Python Script \r\n\r\n"
    clientSocket.send(subject.encode())
    date = time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
    date = date + "\r\n\r\n"
    clientSocket.send(date.encode())
    clientSocket.send(msg.encode())
    clientSocket.send(endmsg.encode())
    recv_msg = clientSocket.recv(10485760)
    print("Response after sending message body:" + recv_msg.decode())
    # Fill in end

    # Send QUIT command and handle server response.
    # Fill in start
    quit = "qUIT\r\n"
    clientSocket.send(quit.encode())
    recv5 = clientSocket.recv(10485760)
    print(recv5.decode())
    clientSocket.close()
    # Fill in end


#if __name__ == '__main__':
 #   smtp_client(1025, '127.0.0.1')
