from socket import *
import os
import sys
import struct
import time
import select
import binascii
import pandas as pd
import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)
timeRTT = []
packet_min = 0
packet_avg = 0
packet_max = 0
pstdev_var = 0


import binascii
# Should use stdev

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

       # Fill in start

       # Fetch the ICMP header from the IP packet
       icmpHeader = recPacket[20:28]
       icmpType, code, mychecksum, packetID, sequence = struct.unpack("bbHHh", icmpHeader)

       # verify the ID of packet
       if icmpType != 8 and packetID == ID:
           bytesInDouble = struct.calcsize("d")
       timeSent = struct.unpack("d", recPacket[28:28 + bytesInDouble])[0]
       return timeReceived - timeSent

       # Fill in end
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
       # Convert 16-bit integers from host to network  byte order
       myChecksum = htons(myChecksum) & 0xffff
   else:
       myChecksum = htons(myChecksum)


   header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
   packet = header + data

   mySocket.sendto(packet, (destAddr, 1))  # AF_INET address must be tuple, not str


   # Both LISTS and TUPLES consist of a number of objects
   # which can be referenced by their position number within the object.

def doOnePing(destAddr, timeout):
   icmp = getprotobyname("icmp")


   # SOCK_RAW is a powerful socket type. For more details:   http://sockraw.org/papers/sock_raw
   mySocket = socket(AF_INET, SOCK_RAW, icmp)

   myID = os.getpid() & 0xFFFF  # Return the current process i
   sendOnePing(mySocket, destAddr, myID)
   delay = receiveOnePing(mySocket, myID, timeout, destAddr)
   mySocket.close()
   return delay


def ping(host, timeout=1):
    dest = gethostbyname(host)
    print("Pinging " + dest + " using Python:")
    print("")
    timeRTT = []
    for i in range(0,10):
        delay = doOnePing(dest, timeout)
        print(delay)
        timeRTT.append(delay)
        if len(timeRTT) > 0:
            avgRTT = round(sum(timeRTT) / len(timeRTT), 2)
            minRTT = min(timeRTT)
            maxRTT = max(timeRTT)
        else:
            avgRTT = 0
            minRTT = 0
            maxRTT = 0
        #print('max:', maxRTT, '\tmin:', minRTT, '\naverage:', avgRTT)
        time.sleep(1)  # one second

    vars = pd.DataFrame(columns=['min', 'avg', 'max', 'stddev'])
    vars = pd.concat([vars, pd.DataFrame([{'min': str(round(minRTT, 2)),
                                           'avg': str(round(avgRTT, 2)),
                                           'max': str(round(maxRTT, 2)),
                                           'stddev': str(round(pd.Series(timeRTT).std(), 2))}],
                                         columns=['min', 'avg', 'max', 'stddev'])], ignore_index=True)
    print(vars)
    return vars




if __name__ == '__main__':
   ping("google.com")
