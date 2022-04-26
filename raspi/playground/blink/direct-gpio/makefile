RM = rm -rf
CC = gcc

all: blink 

blink: blink.o
	$(CC) $^ -o $@
	
%.o: %.c
	$(CC) -c $^ -o $@

clean:
	$(RM) *.o
	$(RM) blink
