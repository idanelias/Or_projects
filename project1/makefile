all: start clean server client

start:
	cd ~ubuntu/Or_projects/project1/
	cp /mnt/1/src/udp*.c src
	dos2unix src/udpserver.c src/udpclient.c

server:
	gcc src/udpserver.c -o server

client: 
	gcc src/udpclient.c -o client


clean:
	rm -f -- client 
	rm -f -- server 
