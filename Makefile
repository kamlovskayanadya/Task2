all: prog

prog: main.o f.o
	gcc -m32 -o prog main.o f.o 
main.o: main.c
	gcc -m32 -c main.c 
f.o: f.asm
	nasm -f elf32 f.asm
clean:
	rm -rf *.o prog
