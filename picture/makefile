all: test_picture

test_picture: test_picture.cpp picture.o
	g++ -Wall -o test_picture test_picture.cpp picture.o

picture.o : picture.h picture.cpp
	g++ -Wall -o picture.o picture.cpp -c
clean: 
	rm *.o

mrproper: clean
	rm test_picture
