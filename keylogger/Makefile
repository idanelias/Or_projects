obj-m += keylogger.o

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

start:
	cp /mnt/keylogger/* /var/tmp/keylogger/
	cd /var/tmp/keylogger/
	dos2unix makefile keylogger.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean



