all: clean start compile

start:
	mkdir -p /var/tmp/chat
	cd /var/tmp/chat
	cp -R /mnt/chat/*  .
	dos2unix makefile src/* include/* 
	chown -R ubuntu:ubuntu ../chat

compile:
	gcc src/chat.c -o chat.o -c
	gcc -pthread src/chatserver.c chat.o -o server
	gcc -pthread src/chatclient.c chat.o -o client

run:
#	./server 3333 &
#	./server 4444 &


clean:
	rm -f -- chat.o
	rm -f -- client 
	rm -f -- server 
