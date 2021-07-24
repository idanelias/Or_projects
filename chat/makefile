all: clean start server client

start:
	mkdir /var/tmp/chat
	cd /var/tmp/chat
	cp -R /mnt/chat/*  .
	dos2unix makefile src/* include/* 
	chown ubuntu:ubuntu ../chat

server:
	gcc -pthread src/chatserver.c -o server

client: 
	gcc -pthread src/chatclient.c -o client

run:
#	./server 3333 &
#	./server 4444 &


clean:
	rm -f -- client 
	rm -f -- server 
