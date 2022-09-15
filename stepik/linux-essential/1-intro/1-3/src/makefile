CC = gcc
RM = rm -rf
CFLAGS = -std=c99 -c -g -O0 -Wall
LDFLAGS = -shared
TARGET = hello
LIB = libPrint.so

all: exe lib

exe: hello.c print.h
	$(CC) $< -fPIC -ldl -o $(TARGET)

lib: print.c print.h
	$(CC) $(LDFLAGS) $^ -fPIC -o $(LIB)

clean:
	$(RM) $(TARGET) 
	$(RM) $(LIB)
	$(RM) *.d
