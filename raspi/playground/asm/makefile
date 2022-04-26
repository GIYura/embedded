RM = rm -rf
ASM = as
LD = ld

all: hello

hello: hello.o
	$(LD) $^ -o $@

%.o: %.asm
#hello.o: hello.asm
	$(ASM) -g $^ -o $@

clean:
	$(RM) *.o
	$(RM) hello
