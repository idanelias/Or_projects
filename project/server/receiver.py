import socket
import time
import os
import threading
from Database import *


AGENT_COUNTER = 1
agents = {}

def session_with_agent(client_socket, client_name):
    agents[client_name] = client_socket
    while (True):
        data = client_socket.recv(1024)
        print(client_name)
        print(data)
        sine_pack = data[0]
        data = data[2:]
        if sine_pack == 'g':
            number_of_packets = data[0:data.find(' ')+1]
            data = data[data.find(' ') + 1:]
            avg_psize = data[0:data.find(' ')+1]
            data = data[data.find(' ') + 1:]
            bps = data
            ip1 = 0
            ip2 = 0
            port1 = 0
            port2 = 0
            service_type = 0

        else:
            ip1 = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            ip2 = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            port1 = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            port2 = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            service_type = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            bps = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            avg_psize = data[data.find(':'):data.find(' ') + 1]
            data = data[data.find(' ') + 1:]
            number_of_packets = data[data.find(':'):]

        creation()
        newstring(client_name, sine_pack, number_of_packets, avg_psize, bps, ip1, ip2, port1, port2, service_type, time.asctime())


        if data == 'EXIT':
            agents.pop(client_name)
            client_socket.close()
            #for s in clients.values():
            #    s.send(bytes(create_msg_with_header(f'client num.{client_name} has left the building!!'), "utf-8"))
            break



def receiver(packet):
    pass


server_socket = socket.socket()
server_socket.bind(('0.0.0.0', 3333))
server_socket.listen(2)

while True:
    client_socket, client_address = server_socket.accept()
    #data = client_socket.recv(1024)
    #print(data)

    t1 = threading.Thread(target=session_with_agent, args=(client_socket, AGENT_COUNTER))
    AGENT_COUNTER = AGENT_COUNTER + 1
    t1.start()
#while (data != "Exit") and (data != "EXIT"):
#    if data == "Time":
       # r = time.asctime()
      #  client_socket.send(r)
     #   data = client_socket.recv(1024)
    #elif data == "Rand":
   #     r = str(random.randint(1, 10))
  #      client_socket.send(r)
 #       data = server_socket.recv(1024)
#    elif data == "Name":
    #    r = str(os.getenv('HOSTNAME'))
   #     client_socket.send(r)
  #      data = client_socket.recv(1024)
 #   else:
#        client_socket.send("this is error anser \nyou can choose only Exit, Time, Rand or Name")
#        data = client_socket.recv(1024)

# client_socket.close()
server_socket.close()
