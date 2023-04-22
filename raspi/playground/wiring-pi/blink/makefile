RM:=rm -rf
CC:=gcc
LIB:=wiringPi

all: blink 

blink: blink.o
	@$(CC) $^ -o $@ -l$(LIB)
	@echo 'Build done !!!'

%.o: %.c
	@$(CC) -c $^ -o $@

clean:
	@$(RM) *.o
	@$(RM) blink
	@echo 'Cleaning ... done !!!'
