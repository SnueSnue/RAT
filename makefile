all: rat

rat: main.o math.o
	@echo " - Linking all files - "
	gcc main.o math.o -o rat

main.o: main.c
	@echo " - Compiling main file - "
	gcc -c main.c

math.o: math.c
	@echo " - Compiling math file - "
	gcc -c math.c


test.o: test.c
	@echo " - Compiling tests - "
	gcc -c test.c

test: test.o math.o
	@echo " - Linking all files - "
	gcc test.o math.o -o test

deploy: rat
	@echo " - Deploying rat - "
	sudo cp rat /usr/local/bin/rat


clean:
	@echo " - Removing everything but the source files - "
	rm main.o math.o test.o rat test
