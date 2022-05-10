CC = gcc
RM = rm -rf
CFLAGS = -std=c99 -c -g -O0 -Wall
LDFLAGS = -shared
TARGET = hello
LIB = libPrint.so

all: exe

exe: hello.c print.h lib
	$(CC) $< -fPIC -L. -lPrint -o $(TARGET)

lib: print.c print.h
	$(CC) $(LDFLAGS) $^ -fPIC -o $(LIB)

clean:
	$(RM) $(TARGET) 
	$(RM) $(LIB)
	$(RM) *.d
