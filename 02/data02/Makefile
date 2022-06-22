CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: main.exe
	./main.exe

main.exe : main.o ../../rangen/random.o point.o
	$(CC) ../../rangen/random.o main.o point.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

point.o: point.h point.cpp
	$(CC) -c point.cpp -o point.o $(CFLAGS)	

../../rangen/random.o : ../../rangen/random.cpp ../../rangen/random.h
	$(CC) -c ../../rangen/random.cpp -o ../../rangen/random.o $(CFLAGS)
clean :
	rm ../../rangen/*.o main.exe seed.out
