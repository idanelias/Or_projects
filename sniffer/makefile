all: clean start compile 

start:
	cd ~ubuntu/Or_projects/sniffer
	cp -R /mnt/sniffer/*  .
	dos2unix makefile src/* include/* 
	chown ubuntu:ubuntu ../sniffer

compile:
	gcc src/raw_socket.c -o raw_socket.o -c
	gcc src/server.c raw_socket.o -o server
        chown ubuntu:ubuntu server

run:
	./server &


clean:
	rm -f -- *.o
	rm -f -- server
