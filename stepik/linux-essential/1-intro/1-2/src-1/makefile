CC=gcc
RM=rm
AR=ar
TARGET=test

all: test.c libmy.a
	$(CC) $< -L. -lmy -o $(TARGET)

libmy.a: obj1.o obj2.o
	$(AR) r $@ $^

obj1.o: obj1.c
	$(CC) -c $^

obj2.o: obj2.c
	$(CC) -c $^

clean:
	@$(RM) -f libmy.a *.o $(TARGET)
	@echo 'Cleaning ... Done'

