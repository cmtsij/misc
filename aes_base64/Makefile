#################################
# App config
#################################
app=aes_base64
CC=gcc
CFLAGS+=
LDFLAGS+= -lssl


#################################
# Framework for dependency check
#################################
sources=$(wildcard *.c)
CFLAGS+= -MMD -MP
LDFLAGS+=

all: $(app)

${app}: $(sources:.c=.o)
	$(CC) $(LDFLAGS) $^ -o $(app)

clean:
	rm -rf *.o *.d ${app}
	
-include $(sources:.c=.d)

