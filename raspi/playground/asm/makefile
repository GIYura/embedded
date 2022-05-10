ASM = as
ASM_FLAGS = -g
LINKER = ld
RM = rm -rf
TARGET = hello

all: $(TARGET)

$(TARGET): hello.o
	$(LD) $^ -o $@

%.o: %.S
	$(ASM) $(ASM_FLAGS) $^ -o $@

clean:
	$(RM) *.o
	$(RM) $(TARGET)
