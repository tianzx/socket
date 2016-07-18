.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=echoServer echoCli
all:$(BIN)
%.O:%.C
	$(CC) $(CFLAGS) -c $< -O $@
clean:
	rm -f *.o $(BIN)
