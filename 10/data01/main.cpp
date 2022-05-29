#include <iostream>
#include <fstream>
#include <string>
#include "../../rangen/random.h"
#include "path.h"
#include "mpi.h"


using namespace std;


int main (int argc, char *argv[]){

    int size, rank;
    Random random;
    int npaths=200;
    int ntowns=10;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    


    Manager Manager(ntowns);
    Manager.SetShape(1);//0 Circ, 1 Square
    Manager.LoadMap("American_capitals"); 
    Manager.SaveRegion();
    Manager.SetRandomComb(rank);
    Manager.ExtendDir(to_string(rank));
    Manager.SetNPaths(npaths);

    Manager.CreatePopulation();
    Manager.TestPopulation();
    Manager.RankPopulation();
    
   
    //cout<<"--------------------Pre Mutazione---------------"<<endl;
    
    for (int i=0; i<500;i++){
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