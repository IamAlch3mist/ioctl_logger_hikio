obj-m += driver.o
KDIR := /home/kiyotaka/Desktop/kernels/corpus/current/kernel/linux-2.6.38.8
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
