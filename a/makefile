
.mainFiles: maths_prog.c  
.addFiles: add.h add.c
.subFiles: subtract.h subtract.c
	
all: .mainFiles libmaths
	
	gcc maths_prog.c -L ./ -lmaths -o maths_prog -Wall -Wextra -pedantic -std=c11


	#setting dynamic library search path for linker:

	# mira version:
	# setenv LD_LIBRARY_PATH \.:$LD_LIBRARY_PATH

	# bash version:
	#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	
	

libmaths: add.o subtract.o
	gcc -shared add.o subtract.o -o libmaths.so -Wall -Wextra -pedantic -std=c11

add.o: .addFiles
	gcc -c add.c -fPIC -Wall -Wextra -pedantic -std=c11

subtract.o: .subFiles
	gcc -c subtract.c -fPIC -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf *.o *.so maths_prog
	
	