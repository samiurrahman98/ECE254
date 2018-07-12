# Makefile, ECE254 lab5 Linux Concurrency Control
# Yiqing Huang, 2014/07/16

CC = gcc
CFLAGS = -Wall -g #-DDEBUG_1
LD = gcc
LDFLAGS = -g 
LDLIBS = -lrt -lpthread -lm

SRCS   = produce.c 
OBJS   = produce.o
TARGETS= produce

all: ${TARGETS}


produce: $(OBJS) 
	$(LD) $(LDFLAGS) -o $@.out $^ $(LDLIBS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

.PHONY: clean
clean:
	rm -f *.d *.o *.out
