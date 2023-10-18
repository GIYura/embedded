CC = gcc
RM = rm -rf
CFLAGS = -std=c99 -c -g -O2 -MD -Wall -save-temps
CFLAGS += -DEXPECT=1
LDFLAGS = 
SRC = $(wildcard *.c)
OBJ = $(addsuffix .o, $(basename $(SRC)))
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo 'Done!'

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@

include $(wildcard *.d)

clean:
	@$(RM) *.o *.d *.i *.s
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'
