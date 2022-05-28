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
    int nchange;
    int npaths=500;
    int ntowns=10;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    


    Manager Manager(ntowns);
    Manager.SetShape(1);//0 Circ, 1 Square
    Manager.LoadMap("Capoluoghi"); 
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
    
    for (int i=0; i<1500;i++){
        if(i%100==0){
            if (rank==0){
            nchange=npaths*(pow(random.Rannyu(),3));
                //nchange=5;

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


    Manager.Mutate();
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