all: rat

rat: main.o math.o
	@echo "Linking all files"
	gcc main.o math.o -o rat

main.o: main.c
	@echo "Compiling main file"
	gcc -c main.c

math.o: math.c
	@echo "Compiling math file"
	gcc -c math.c

clean:
	@echo "Removing everything but the source files"
	rm main.o math.o rat
