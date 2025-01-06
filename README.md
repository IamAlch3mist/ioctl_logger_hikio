# ioctl_logger_hikio
ioctl logger (for debugging purpose)

```
I wrote the driver to log IOCTL calls made by the davinci binary to the hikio driver on Hikvision cameras. 
It is designed to make debugging more verbose, specifically for security research purposes.

# -- In emulated kernel --
insmod driver.ko
mknod /dev/hikio c 253 0
chmod 666 /dev/hikio
```
