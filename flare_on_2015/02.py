a = [168, 154, 144, 179, 182, 188, 180, 171, 157, 174, 249, 184, 157, 184, 175, 186, 165, 165, 186, 154, 188, 176, 167, 192, 138, 170, 174, 175, 186, 164, 236, 170, 174, 235, 173, 170, 175]


s = 0
result = []
for i in a:
    result.append((i-(1<<(s&3))-1)^0xc7)
    s += i
print ''.join(map(chr,result))

