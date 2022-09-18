CC=gcc
RM=rm -f
TARGET=test

all: test.c libmy.so
	$(CC) $< -L. -lmy -o $(TARGET)

libmy.so: obj1.o obj2.o
	$(CC) -shared -o libmy.so $^

obj1.o: obj1.c
	$(CC) -fPIC -c $^

obj2.o: obj2.c
	$(CC) -fPIC -c $^

clean:
	@$(RM) *.so *.o
	@echo 'Cleaning ... Done'
