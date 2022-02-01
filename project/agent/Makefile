all: clean compile

start:
	cd ~ubuntu/Or_projects/sniffer
	cp -R /proj/agent/sniffer/* ~ubuntu/Or_projects/sniffer
	dos2unix Makefile src/* include/*

compile:
	gcc src/packet_analyzer/packet_analzer.c -o ~ubuntu/Or_projects/sniffer/packet_analzer.o -c
	gcc src/sniffer/raw_socket.c -o ~ubuntu/Or_projects/sniffer/raw_socket.o -c
	gcc src/agent.c -o ~ubuntu/Or_projects/sniffer/agent.o -c
	gcc src/server_communicator/server_communicator.c -o ~ubuntu/Or_projects/sniffer/server_commumicator.o -c
	#gcc -pthread src/everything.c ~ubuntu/Or_projects/sniffer/agent.o ~ubuntu/Or_projects/sniffer/raw_socket.o ~ubuntu/Or_projects/sniffer/packet_analzer.o -o ~ubuntu/Or_projects/sniffer/server
	gcc -pthread ~ubuntu/Or_projects/sniffer/server_commumicator.o ~ubuntu/Or_projects/sniffer/agent.o ~ubuntu/Or_projects/sniffer/raw_socket.o ~ubuntu/Or_projects/sniffer/packet_analzer.o -o ~ubuntu/Or_projects/sniffer/server


clean:
	rm -f -- *.o
	rm -f -- server
