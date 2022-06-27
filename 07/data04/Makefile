CC = g++
CFLAGS = -Wall -O3 --std=c++11

esegui_all: NVE_NVT.exe 
	./NVE_NVT.exe gas MC;	./NVE_NVT.exe solid MC; ./NVE_NVT.exe liquid MC;	./NVE_NVT.exe gas MD;	./NVE_NVT.exe solid MD; ./NVE_NVT.exe liquid MD 


MC: NVE_NVT.exe 
	./NVE_NVT.exe gas MC;	./NVE_NVT.exe solid MC; ./NVE_NVT.exe liquid MC

MD: NVE_NVT.exe 
	./NVE_NVT.exe gas MD;	./NVE_NVT.exe solid MD; ./NVE_NVT.exe liquid MD

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