obj-m += chrdev.o

KERNEL_VERSION := $(shell uname -r)

KDIR ?= /lib/modules/$(KERNEL_VERSION)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load:
	sudo insmod chrdev.ko
	sudo dmesg -c

unload:
	sudo rmmod chrdev.ko
	sudo dmesg -c
