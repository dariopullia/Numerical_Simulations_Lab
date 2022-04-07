CC = g++
CFLAGS = -Wall -O3 --std=c++11


esegui: NVE_NVT.exe
	./NVE_NVT.exe 

NVE_NVT.exe : MD_MC.o ../../rangen/random.o
	$(CC) ../../rangen/random.o MD_MC.o -o NVE_NVT.exe
MD_MC.o : MD_MC.cpp
	$(CC) -c MD_MC.cpp -o MD_MC.o $(CFLAGS)
../../rangen/random.o : ../../rangen/random.cpp ../../rangen/random.h
	$(CC) -c ../../rangen/random.cpp -o ../../rangen/random.o $(CFLAGS)
clean :
	rm *.o NVE_NVT.exe