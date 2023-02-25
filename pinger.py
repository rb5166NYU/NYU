from socket import *
import os
import sys
import struct
import time
import select
import binascii
import pandas as pd

ICMP_ECHO_REQUEST = 8

def checksum(string):
    csum = 0
    countTo = (len(string) // 2) * 2
    count = 0

    while count < countTo:
        thisVal = (string[count + 1]) * 256 + (string[count])
        csum += thisVal
        csum &= 0xffffffff
        count += 2

    if countTo < len(string):
        csum += (string[len(string) - 1])
        csum &= 0xffffffff

    csum = (csum >> 16) + (csum & 0xffff)
    csum = csum + (csum >> 16)
    answer = ~csum
    answer = answer & 0xffff
    answer = answer >> 8 | (answer << 8 & 0xff00)
    return answer

def receiveOnePing(mySocket, ID, timeout, destAddr):
    timeLeft = timeout

    while 1:
        startedSelect = time.time()
        whatReady = select.select([mySocket], [], [], timeLeft)
        howLongInSelect = (time.time() - startedSelect)
        if whatReady[0] == []:  # Timeout
            return "Request timed out."

        timeReceived = time.time()
        recPacket, addr = mySocket.recvfrom(1024)

    # Fetch the ICMP header from the IP packet
    icmpHeader = recPacket[20:28]

    # Unpack the header to obtain type, code, checksum, id, and sequence
    icmpType, code, checksum, packetID, sequence = struct.unpack("bbHHh", icmpHeader)

    if packetID == ID:
        byte_size = len(recPacket)
        timeSent = struct.unpack("d", recPacket[28:28 + struct.calcsize("d")])[0]
        rtt = (timeReceived - timeSent) * 1000
        ttl = ord(struct.unpack("c", recPacket[8:9])[0])
        return (byte_size, rtt, ttl)

    timeLeft = timeLeft - howLongInSelect
    if timeLeft <= 0:
        return "Request timed out."


    def sendOnePing(mySocket, destAddr, ID):
        # Header is type (8), code (8), checksum (16), id (16), sequence (16)
        myChecksum = 0
        # Make a dummy header with a 0 checksum
        # struct -- Interpret strings as packed binary data
        header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
        data = struct.pack("d", time.time())
        # Calculate the checksum on the data and the dummy header.
        myChecksum = checksum(header + data)

        # Get the right checksum, and put in the header
        if sys.platform == 'darwin':
            # Convert 16-bit integers from host to network byte order
            myChecksum = htons(myChecksum) & 0xffff
        else:
            myChecksum = htons(myChecksum)

        header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
        packet = header + data

        mySocket.sendto(packet, (destAddr, 1))  # AF_INET address must be tuple, not str

    def doOnePing(destAddr, timeout):
        icmp = getprotobyname("icmp")

        mySocket = socket(AF_INET, SOCK_RAW, icmp)

        myID = os.getpid() & 0xFFFF  # Return the current process i
        sendOnePing(mySocket, destAddr, myID)
        delay = receiveOnePing(mySocket, myID, timeout, destAddr)
        mySocket.close()
        return delay

    def ping(host, timeout=1):
        # timeout=1 means: If one second goes by without a reply from the server,
        # the client assumes that either the client's ping or the server's pong is lost
        dest = gethostbyname(host)
        print("\nPinging " + dest + " using Python:")
        print("")

        response = pd.DataFrame(columns=['bytes', 'rtt',
                                             'ttl'])  # This creates an empty dataframe with 3 headers with the column specific names declared
        delays = []  # to collect the delays of each ping in a list so you can calculate vars after your ping

        # Send ping requests to a server separated by approximately one second
        for i in range(0, 4):  # Four pings will be sent (loop runs for i=0, 1, 2, 3)
            delay, statistics = doOnePing(dest, timeout)  # Do one ping and store the delay and statistics
            delays.append(delay)  # Store the delay in the list
            response = response.append({'bytes': delay[0], 'rtt': delay[1], 'ttl': delay[2]},
                                        ignore_index=True)  # Store the delay in the response dataframe
            print(delay)
            time.sleep(1)  # Wait one second

        packet_lost = 0
        packet_recv = 0
        # Fill in start. Calculate the number of packets lost and received.
        for index, row in response.iterrows():
            if row['rtt'] == 'Request timed out.':  # Check if the response was "Request timed out."
                packet_lost += 1  # Increment the packet_lost counter
            else:
                packet_recv += 1  # Increment the packet_recv counter
        # Fill in end

        # You should have the values of delay for each ping here structured in a pandas dataframe;
        # Calculate the minimum, average, maximum, and standard deviation of the delay.
        vars = pd.DataFrame(columns=['min', 'avg', 'max', 'stddev'])
        vars = vars.append(
            {'min': str(round(min(delays)[1], 2)), 'avg': str(round(sum([d[1] for d in delays]) / len(delays), 2)),
                'max': str(round(max(delays)[1], 2)),
                'stddev': str(round(pd.Series([d[1] for d in delays]).std(), 2))}, ignore_index=True)
        print(vars)  # Print the calculated statistics
        return vars

    if name == 'main':
        ping("google.com")



