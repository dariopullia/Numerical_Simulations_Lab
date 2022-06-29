CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui: Monte_Carlo_ISING_1D.exe
	bash metro_clean.sh; bash gibbs_clean.sh; ./Monte_Carlo_ISING_1D.exe 0; ./Monte_Carlo_ISING_1D.exe 1; 

metropolis: Monte_Carlo_ISING_1D.exe
	bash metro_clean.sh; ./Monte_Carlo_ISING_1D.exe 1

gibbs: Monte_Carlo_ISING_1D.exe
	bash gibbs_clean.sh; ./Monte_Carlo_ISING_1D.exe 0

Monte_Carlo_ISING_1D.exe : Monte_Carlo_ISING_1D.o  ../../rangen/random.o 
	$(CC)  ../../rangen/random.o Monte_Carlo_ISING_1D.o -o Monte_Carlo_ISING_1D.exe
Monte_Carlo_ISING_1D.o : Monte_Carlo_ISING_1D.cpp
	$(CC) -c Monte_Carlo_ISING_1D.cpp -o Monte_Carlo_ISING_1D.o $(CFLAGS)
random.o :  ../../rangen/random.cpp  ../../rangen/random.h
	$(CC) -c  ../../rangen/random.cpp -o  ../../rangen/random.o $(CFLAGS)
clean :
	rm *.o Monte_Carlo_ISING_1D.exe
