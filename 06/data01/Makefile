CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: Monte_Carlo_ISING_1D.exe
	./Monte_Carlo_ISING_1D.exe

Monte_Carlo_ISING_1D.exe : Monte_Carlo_ISING_1D.o  /home/dario/Uni_ubu/lsn/rangen/random.o 
	$(CC)  /home/dario/Uni_ubu/lsn/rangen/random.o Monte_Carlo_ISING_1D.o -o Monte_Carlo_ISING_1D.exe
Monte_Carlo_ISING_1D.o : Monte_Carlo_ISING_1D.cpp
	$(CC) -c Monte_Carlo_ISING_1D.cpp -o Monte_Carlo_ISING_1D.o $(CFLAGS)
random.o :  /home/dario/Uni_ubu/lsn/rangen/random.cpp  /home/dario/Uni_ubu/lsn/rangen/random.h
	$(CC) -c  /home/dario/Uni_ubu/lsn/rangen/random.cpp -o  /home/dario/Uni_ubu/lsn/rangen/random.o $(CFLAGS)
clean :
	rm *.o Monte_Carlo_ISING_1D.exe
