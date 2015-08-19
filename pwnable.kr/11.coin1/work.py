import socket
from time import sleep

IP = 'pwnable.kr'
PORT = 9007

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect((IP, PORT))

buf = sock.recv(1024)
print buf
sleep(3)

while True:
    buf = sock.recv(1024)
    print buf
    c_i = buf.rindex('C')
    n_i = buf.rindex('N')
    c = int(buf[c_i+2:-1])
    n = int(buf[n_i+2:c_i])

    l = 0
    r = n
    while True:
        mid = (l+r)/2
        if l + 1 == r:
            break
        tosend = ' '.join(map(str,range(l,mid)))
        sock.send(tosend + '\n')
        print tosend
        buf = sock.recv(1024)
        print buf

        if (int(buf.strip()) % 10 == 0):
            l = mid
        else:
            r = mid
    buf = ''
    while 'Correct!' not in buf:
        sock.send(str(l) + '\n')
        buf = sock.recv(1024)

    print buf
