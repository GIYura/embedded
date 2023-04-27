RM:=rm -rf
CC:=gcc
LIB:=wiringPi

all: test

test: test.o
	@$(CC) $^ -o $@ -l$(LIB)
	@echo 'Build done !!!'

%.o: %.c
	@$(CC) -c $^ -o $@

clean:
	@$(RM) *.o
	@$(RM) test
	@echo 'Cleaning ... done !!!'
