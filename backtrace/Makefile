app=backtrace
CFLAGS+=-g -O0 -finstrument-functions
LDFLAGS=-rdynamic
CC=gcc

sources=$(wildcard *.c)
CFLAGS+= -MMD -MP

all:$(app)

${app}: $(sources:.c=.o)
	$(CC) $(LDFLAGS) $^ -o $(app)

clean:
	rm -rf *.o *.d ${app}
	
-include $(sources:.c=.d)

