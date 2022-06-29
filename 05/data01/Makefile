CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: main.exe main_autoc.exe main_eq.exe
	./main.exe; ./main_autoc.exe; ./main_eq.exe; 

main.exe: main.o ../../rangen/random.o metropolis.o
	$(CC) ../../rangen/random.o main.o metropolis.o -o main.exe

main_autoc.exe: main_autoc.o ../../rangen/random.o metropolis.o
	$(CC) ../../rangen/random.o main_autoc.o metropolis.o -o main_autoc.exe

main_eq.exe: main_eq.o ../../rangen/random.o metropolis.o
	$(CC) ../../rangen/random.o main_eq.o metropolis.o -o main_eq.exe

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

main_eq.o: main_eq.cpp
	$(CC) -c main_eq.cpp -o main_eq.o $(CFLAGS)

main_autoc.o: main_autoc.cpp
	$(CC) -c main_autoc.cpp -o main_autoc.o $(CFLAGS)

../../rangen/random.o: ../../rangen/random.cpp ../../rangen/random.h
	$(CC) -c ../../rangen/random.cpp -o ../../rangen/random.o $(CFLAGS)

clean :
	rm ../../rangen/*.o main.exe main_autoc.exe main_eq.exe seed.out

metropolis.o : metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)
