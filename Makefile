CC=gcc
CFLAGS+= -Wall -fsanitize=address -pedantic -g
#CFLAGS+= -Wall -pedantic -g
TARGET=list
RM=rm -f

all: $(TARGET)

$(TARGET): *.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET)
