from socket import *
import os
import sys
import struct
import time
import select
import binascii
import pandas as pd

ICMP_ECHO_REQUEST = 8
MAX_HOPS = 10
TIMEOUT = 2.0
TRIES = 1

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

def build_packet():
    my_checksum = 0
    ID = os.getpid() & 0xFFFF
    header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, my_checksum, ID, 1)
    my_checksum = checksum(header)
    header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, my_checksum, ID, 1)
    packet = header
    return packet

def get_route(hostname):
    timeLeft = TIMEOUT
    df = pd.DataFrame(columns=['Hop Count', 'Try', 'IP', 'Hostname', 'Response Code'])
    destAddr = gethostbyname(hostname)

    for ttl in range(1, MAX_HOPS):
        for tries in range(TRIES):
            mySocket = socket(AF_INET, SOCK_RAW, getprotobyname("icmp"))

            mySocket.setsockopt(IPPROTO_IP, IP_TTL, struct.pack('I', ttl))
            mySocket.settimeout(TIMEOUT)
            try:
                d = build_packet()
                mySocket.sendto(d, (hostname, 0))
                t = time.time()
                startedSelect = time.time()
                whatReady = select.select([mySocket], [], [], timeLeft)
                howLongInSelect = (time.time() - startedSelect)
                if whatReady[0] == []:  # Timeout
                    df = pd.concat([df, pd.DataFrame({"Hop Count": [ttl], "Try": [tries + 1], "IP": [""], "Hostname": [""], "Response Code": ["timeout"]})], ignore_index=True)
                recvPacket, addr = mySocket.recvfrom(1024)
                timeReceived = time.time()
                timeLeft = timeLeft - howLongInSelect
                if timeLeft <= 0:
                    df = pd.concat([df, pd.DataFrame({"Hop Count": [ttl], "Try": [tries + 1], "IP": [""], "Hostname": [""], "Response Code": ["timeout"]})], ignore_index=True)
            except Exception as e:
                continue
            else:
                icmp_header = recvPacket[20:28]
                types, _, _, _, _ = struct.unpack("bbHHh", icmp_header)

                try:
                    router_hostname = gethostbyaddr(addr[0])[0]
                except herror:
                    router_hostname = "hostname not returnable"

                df = pd.concat([df, pd.DataFrame({"Hop Count": [ttl], "Try": [tries + 1], "IP": [addr[0]], "Hostname": [router_hostname], "Response Code": [types]})], ignore_index=True)

                if types == 0:
                    break
                elif types == 3:
                    break
                elif types == 11:
                    break
    dest_canonical_name, _, _ = gethostbyaddr(destAddr)
    df = pd.concat([df, pd.DataFrame({"Hop Count": [ttl + 1], "Try": [1], "IP": [destAddr], "Hostname": [hostname], "Response Code": [0]})], ignore_index=True)
    return df

if __name__ == '__main__':
    print(get_route("google.com"))
