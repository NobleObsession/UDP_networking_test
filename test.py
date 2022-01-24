import socket
from time import sleep

msg_counter = 500 
serverAddressPort   = ("127.0.0.1", 55514)
bufferSize          = 100

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

for i in range(msg_counter):
	msgFromClient = "/ᐠ｡ꞈ｡ᐟ\cat=^._.^=∫" + str(i)
	bytesToSend = str.encode(msgFromClient)
	UDPClientSocket.sendto(bytesToSend, serverAddressPort)
	sleep(0.02)