from socket import *

def smtp_client(port=1025, mailserver='127.0.0.1'):
    # Create socket called clientSocket and establish a TCP connection with mailserver and port
    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((mailserver, port))

    recv = clientSocket.recv(1024).decode()

    # Send HELO command and print server response.
    heloCommand = 'HELO Alice\r\n'
    clientSocket.send(heloCommand.encode())
    recv1 = clientSocket.recv(1024).decode()

    # Send MAIL FROM command and handle server response.
    mailfrom = "MAIL FROM:<from@example.com>\r\n"
    clientSocket.send(mailfrom.encode())
    recv2 = clientSocket.recv(1024).decode()

    # Send RCPT TO command and handle server response.
    rcptto = "RCPT TO:<to@example.com>\r\n"
    clientSocket.send(rcptto.encode())
    recv3 = clientSocket.recv(1024).decode()

    # Send DATA command and handle server response.
    data = "DATA\r\n"
    clientSocket.send(data.encode())
    recv4 = clientSocket.recv(1024).decode()

    # Send message data.
    message = "Subject: Test Message\r\n\r\nThis is a test email message.\r\n"
    clientSocket.send(message.encode())

    # Message ends with a single period, send message end and handle server response.
    endmsg = "\r\n.\r\n"
    clientSocket.send(endmsg.encode())
    recv5 = clientSocket.recv(1024).decode()

    # Send QUIT command and handle server response.
    quitmsg = "QUIT\r\n"
    clientSocket.send(quitmsg.encode())
    recv6 = clientSocket.recv(1024).decode()

    clientSocket.close()


if __name__ == '__main__':
    smtp_client(1025, '127.0.0.1')

