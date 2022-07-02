CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: main.exe
	bash cleanCirc.sh; bash cleanSquare.sh; ./main.exe 0; ./main.exe 1;

main.exe : main.o ../../rangen/random.o path.o
	$(CC) ../../rangen/random.o main.o path.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
../../rangen/random.o : ../../rangen/random.cpp ../../rangen/random.h
	$(CC) -c ../../rangen/random.cpp -o ../../rangen/random.o $(CFLAGS)
clean :
	rm ../../rangen/*.o main.exe seed.out

path.o : path.cpp path.h
	$(CC) -c path.cpp -o path.o $(CFLAGS)
