arm-linux-gnueabi-gcc ./leg.c -o leg
qemu-arm -g 2345 -L /usr/arm-linux-gnueabi ./leg
