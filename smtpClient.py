from socket import *
import time
from socket import socket


def smtp_client(mailserver='127.0.0.1'):
    msg = "\r\n My message"
    enomsg = "\r\n.\r\n"

    mailserver = ("127.0.0.1", 1025)
    # Create socket called client_socket and establish a TCP connection with mailserver and port

    # Fill in start
    client_socket: socket = socket(AF_INET, SOCK_STREAM)
    client_socket.connect(mailserver)
    # Fill in end

    recv = client_socket.recv(1024).decode()
    print(recv)  # You can use these print statement to validate return codes from the server.
    if recv[:3] != '220':
        print('220 reply not received from server.')

    # Send HELO command and print server response.
    helo_command = 'HELO Alice\r\n'
    client_socket.send(helo_command.encode())
    recv1 = client_socket.recv(1024).decode()
    print(recv1)
    if recv1[:3] != '250':
        print('250 reply not received from server.')

    command = 'STARTTLS \r\n'
    command = command.encode()
    client_socket.send(command)
    recv2 = client_socket.recv(1024)
    recv2 = recv2.decode()
    print("Message after STARTTLS command:" + recv2)
    if recv2[:3] != '250':
        print('260 reply not received from server.')

    # Send MAIL FROM command and handle server response.
    # Fill in start
    mailfrom = "MAIL FROM: <email@email.com> \r\n"
    client_socket.send(mailfrom.encode())
    recv2 = recv2.decode()
    print("After MAIL FROM command: " + recv2)
    # Fill in end

    # Send RCPT TO command and handle server response.
    # Fill in start
    rcpt_to = "RCPT TO: <email1@email.com> \r\n"
    client_socket.send(rcpt_to.encode())
    recv3 = client_socket.recv(1024)
    recv3 = recv3.decode()
    print("After RCPT TO command: " + recv3)

    # Fill in end

    # Send DATA command and handle server response.
    # Fill in start
    data = "DATA\r\n"
    client_socket.send(data.encode())
    recv4 = client_socket.recv(1024)
    recv4 = recv4.decode()
    print("After DATA command: " + recv4)
    # Fill in end

    # Send message data.
    # Fill in start

    # Fill in end

    # Message ends with a single period, send message end and handle server response.
    # Fill in start
    subject = "Subject: SMTP Client Python Script \r\n\r\n"
    client_socket.send(subject.encode())
    date = time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
    date = date + "\r\n\r\n"
    client_socket.send(date.encode())
    client_socket.send(msg.encode())
    client_socket.send(enomsg.encode())
    recv_msg = client_socket.recv(1024)
    print("Response after sending message body:" + recv_msg.decode())
    # Fill in end

    # Send QUIT command and handle server response.
    # Fill in start
    quit = "qUIT\r\n"
    client_socket.send(quit.encode())
    recv5 = client_socket.recv(1024)
    print(recv5.decode())
    client_socket.close()
    # Fill in end

    if __name__ == '__main__':
        smtp_client(1025, '127.0.0.1')
