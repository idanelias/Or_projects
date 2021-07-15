all: clean start server client

start:
	cp /mnt/1/udp*.c /var/tmp
	dos2unix udpserver.c udpclient.c

server:
	gcc udpserver.c -o server

client: 
	gcc udpclient.c -o client


clean:
	rm -f -- client 
	rm -f -- server 
