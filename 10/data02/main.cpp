#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../rangen/random.h"
#include "path.h"
#include "mpi.h"


using namespace std;


int main (int argc, char *argv[]){

    int size, rank;
    Random random;
    random.SetPrimesComb(0);
    int nchange;
    int ntowns=10;
    int npaths=500;
    int nmutations=1500;
    //int npaths=200;
    //int nmutations=500;
    int migration_freq=nmutations/4 +1;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    


    Manager Manager(ntowns);
    Manager.LoadMap("Capoluoghi"); 
    //Manager.LoadMap("American_capitals"); 
    Manager.SaveRegion();
    Manager.SetRandomComb(rank);
    Manager.ExtendDir(to_string(rank));
    Manager.SetNPaths(npaths);

    ntowns=Manager.GetDim();
    int goodOrderMatrix[size][ntowns];
    int goodOrder[ntowns];




    Manager.CreatePopulation();
    Manager.TestPopulation();
    Manager.RankPopulation();
    
   
    //cout<<"--------------------Pre Mutazione---------------"<<endl;
    
    for (int i=0; i<nmutations;i++){
        if(i%migration_freq==0){
            if (rank==0){
                //nchange=npaths*(pow(random.Rannyu(),3));
                //nchange=5;
                nchange=(int)random.Rannyu(npaths/100,npaths/20);
                //cout<<nchange<<endl;
            }
            MPI_Bcast(&nchange, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

            for(int j=0;j<nchange;j++){
                Manager.GetGoodOrder(goodOrder);

                MPI_Allgather(&goodOrder, ntowns, MPI_INT, goodOrderMatrix, ntowns, MPI_INT, MPI_COMM_WORLD);

                for (int k=0; k<size;k++){
                    Manager.Import(goodOrderMatrix[k]);
                }

            }
            Manager.TestPopulation();
            Manager.RankPopulation();
        }


    Manager.Mutate(0.15,0.45);
    Manager.TestPopulation();
    Manager.RankPopulation();
    Manager.SaveBest(1);

    }
    
    //cout<<"--------------------Post Mutazione---------------"<<endl;
    
    //Manager.shortPrint(3);
    Manager.SaveBestCoord();
    
    
    //Manager.Try();
    //cout<<" Sono il nodo "<<rank<<" dei "<<size<<" che hai utilizzato!"<<endl;
    MPI_Finalize();

    return 0;
}