obj-m := call_dev.o

CC := gcc

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all :
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(MAKE) clean
	$(CC) -o call_app.exe call_app.c

clean :
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf modules.order
	rm -rf Module.symvers
	rm -rf .tmp_versions
#	rm -rf *.ko
