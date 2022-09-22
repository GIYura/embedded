obj-m += test-module.o

KERNEL_VERSION := $(shell uname -r)

KDIR ?= /lib/modules/$(KERNEL_VERSION)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load:
	sudo insmod test-module.ko
	sudo dmesg -c

unload:
	sudo rmmod test-module.ko
	sudo dmesg -c
