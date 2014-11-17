all: ppm

ppm: ppm.c ppm_function.o
	gcc -Wall -o ppm ppm.c ppm_function.o

ppm_function.o : ppm.h ppm_function.c
	gcc -Wall -o ppm_function.o ppm_function.c -c
