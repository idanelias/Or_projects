all: clean start compile 

start:
	cd ~ubuntu/Or_projects/task
	cp -R /mnt/task/*  .
	dos2unix makefile src/* include/* 
	chown ubuntu:ubuntu ../task

compile:
	gcc src/TASK.c -o task.o -c
	gcc src/TASKS.c -o tasks.o -c
	gcc src/main.c -o main.o -c
	gcc -o tasks-list main.o tasks.o task.o 
        chown ubuntu:ubuntu tasks-list

run:
#	./tasks-list  &


clean:
	rm -f -- *.o
	rm -f -- tasks-list 
