Files: maths_prog.c, add.h, add.c, subtract.h, subtract.c

all: libmaths maths_prog.c
	gcc maths_prog.c -L. -lmaths -o maths_prog -Wall -Wextra -pedantic -std=c11

	# mira version:
	# setenv LD_LIBRARY_PATH \.:$LD_LIBRARY_PATH
	# bash version:
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

libmaths: add.o subtract.o
	gcc -shared add.o subtract.o -o libmaths.so -Wall -Wextra -pedantic -std=c11

add.o: add.c add.h
	gcc -c add.c -fPIC -Wall -Wextra -pedantic -std=c11

subtract.o: subtract.c subtract.h
	gcc -c subtract.c -fPIC -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf maths_prog add.o subtract.o libmaths.so
	export LD_LIBRARY_PATH=home:$LD_LIBRARY_PATH