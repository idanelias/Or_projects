all: clean start compile

start:
	mkdir -p /var/tmp/chat
	cd /var/tmp/chat
	cp -R /mnt/chat/*  .
	dos2unix makefile src/* include/* 
	chown -R ubuntu:ubuntu ../chat

compile:
	gcc src/chat.c -o chat.o -c
	gcc src/client.c -o client.o -c
	gcc src/server.c -o server.o -c
	gcc -pthread src/chatserver.c chat.o server.o -o server
	gcc -pthread src/chatclient.c chat.o client.o -o client

run:
#	./server 3333 &
#	./server 4444 &


clean:
	rm -f -- *.o
	rm -f -- client 
	rm -f -- server 
