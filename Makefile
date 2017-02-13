CC=gcc
INC_DIR = "../kernel-code/linux-3.16.36/include/"
CFLAGS= -Wall -c -g -I$(INC_DIR)


all: proc_stat_test prio name

name: name.o

name.o: name.c
	gcc $(CFLAGS) name.c

prio: prio.o

prio.o: prio.c
	gcc $(CFLAGS) prio.c


proc_stat_test: proc_stat_test.o

proc_stat_test.o: proc_stat_test.c
	gcc $(CFLAGS) proc_stat_test.c

clean:
	rm *.o proc_stat_test prio name
