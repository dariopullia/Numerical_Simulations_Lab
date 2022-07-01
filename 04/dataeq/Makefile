CC = g++
CFLAGS = -Wall -O3 --std=c++11


esegui_all: NVE_NVT.exe 
	bash clean.sh; ./NVE_NVT.exe gas; ./NVE_NVT.exe solid; ./NVE_NVT.exe liquid

gas: NVE_NVT.exe
	./NVE_NVT.exe gas
liquid: NVE_NVT.exe
	./NVE_NVT.exe liquid
solid: NVE_NVT.exe
	./NVE_NVT.exe solid

NVE_NVT.exe : MD_MC.o ../../rangen/random.o
	$(CC) ../../rangen/random.o MD_MC.o -o NVE_NVT.exe
MD_MC.o : MD_MC.cpp
	$(CC) -c MD_MC.cpp -o MD_MC.o $(CFLAGS)
../../rangen/random.o : ../../rangen/random.cpp ../../rangen/random.h
	$(CC) -c ../../rangen/random.cpp -o ../../rangen/random.o $(CFLAGS)
clean :
	rm *.o NVE_NVT.exe