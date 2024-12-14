flags = -g3 -Wall -Wextra -fsanitize=address,leak,undefined

rat: rat.o mymath.o
	gcc $(flags) -o rat rat.o mymath.o


PHONY: clean

clean:
	rm rat *.o
