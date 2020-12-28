Files: maths_prog.c, add.h, add.c, subtract.h, subtract.c

all: add.o subtract.o maths_prog.c
	gcc -o maths_prog maths_prog.c subtract.o add.o -Wall -Wextra -pedantic -std=c11

add.o: add.c add.h
	gcc -c add.c -Wall -Wextra -pedantic -std=c11

subtract.o: subtract.c subtract.h
	gcc -c subtract.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf maths_prog add.o subtract.o