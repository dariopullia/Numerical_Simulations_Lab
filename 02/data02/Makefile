CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: main.exe
	./main.exe

main.exe : main.o /home/dario/Uni_ubu/lsn/rangen/random.o point.o
	$(CC) /home/dario/Uni_ubu/lsn/rangen/random.o main.o point.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

point.o: point.h point.cpp
	$(CC) -c point.cpp -o point.o $(CFLAGS)	

/home/dario/Uni_ubu/lsn/rangen/random.o : /home/dario/Uni_ubu/lsn/rangen/random.cpp /home/dario/Uni_ubu/lsn/rangen/random.h
	$(CC) -c /home/dario/Uni_ubu/lsn/rangen/random.cpp -o /home/dario/Uni_ubu/lsn/rangen/random.o $(CFLAGS)
clean :
	rm /home/dario/Uni_ubu/lsn/rangen/*.o main.exe seed.out
