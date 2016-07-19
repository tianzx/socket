.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=echosrv echocli echosrv2 p2psrv p2pcli
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

