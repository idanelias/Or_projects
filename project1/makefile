all: start clean server client

start:
	cd ~ubuntu/Or_projects/project1 
	cp /mnt/1/udp*.c .
	dos2unix udpserver.c udpclient.c

server:
	gcc udpserver.c -o server

client: 
	gcc udpclient.c -o client


clean:
	rm -f -- client 
	rm -f -- server 
