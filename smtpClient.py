from socket import *
import time
from socket import socket


def smtp_client(mailserver='127.0.0.1'):
    msg = "\r\n My message"
    enomsg = "\r\n.\r\n"

    mailserver = ("127.0.0.1", 1025)

    client_socket: socket = socket(AF_INET, SOCK_STREAM)
    client_socket.connect(mailserver)

    recv = client_socket.recv(1024).decode()

    helo_command = 'HELO Alice\r\n'
    client_socket.send(helo_command.encode())
    recv1 = client_socket.recv(1024).decode()

    command = 'STARTTLS \r\n'
    command = command.encode()
    client_socket.send(command)
    recv2 = client_socket.recv(1024)
    recv2 = recv2.decode()

    mailfrom = "MAIL FROM: <rb5166@nyu.edu> \r\n"
    client_socket.send(mailfrom.encode())
    recv2 = recv2.decode()

    rcpt_to = "RCPT TO: <rb5166@nyu.edu> \r\n"
    client_socket.send(rcpt_to.encode())
    recv3 = client_socket.recv(1024)
    recv3 = recv3.decode()

    data = "DATA\r\n"
    client_socket.send(data.encode())
    recv4 = client_socket.recv(1024)
    recv4 = recv4.decode()

    subject = "Subject: SMTP Client Python Script \r\n\r\n"
    client_socket.send(subject.encode())
    date = time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
    date = date + "\r\n\r\n"
    client_socket.send(date.encode())
    client_socket.send(msg.encode())
    client_socket.send(enomsg.encode())
    recv_msg = client_socket.recv(1024)

    quit = "qUIT\r\n"
    client_socket.send(quit.encode())
    recv5 = client_socket.recv(1024)
    client_socket.close()

    if __name__ == '__main__':
        smtp_client(1025, '127.0.0.1')
