#!/usr/bin/env

ARCH=arm CROSS_COMPILE=~/Desktop/hikvision/toolchain/arm-2011.09/bin/arm-none-linux-gnueabi- make
#cp driver.ko ../firmware_dump/fs/

# -- In emulated kernel --

#insmod driver.ko
#mknod /dev/hikio c 253 0
#chmod 666 /dev/hikio
