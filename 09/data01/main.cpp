#include <iostream>
#include <fstream>
#include <string>
#include "../../rangen/random.h"
#include "path.h"


using namespace std;


int main (int argc, char *argv[]){

    int mode=stoi(argv[1]);

    Manager Manager(34);
    Manager.SetShape(mode);//0 Circ, 1 Square
    Manager.CreateRegion(); 
    Manager.SaveRegion();
    Manager.SetNPaths(500);
    Manager.CreatePopulation();
    /*
    for (int i=0; i<50; i++){
        Manager.CreatePopulation();
        Manager.Mutate();

        Manager.DestroyPopulation();
    }
    */
      
    
    Manager.TestPopulation();
    Manager.RankPopulation();
    
    
    //Manager.Try();
    //Manager.shortPrint();
   
   
    
    cout<<"--------------------Pre Mutazione---------------"<<endl;
    
    for (int i=0; i<500;i++){
    //Manager.Mutate(0.25,0.);//Primo parametro per le mutazioni, secondo per il crossover, sempre un 5% di full random
    Manager.Mutate(0.15,0.45);//Primo parametro per le mutazioni, secondo per il crossover, sempre un 5% di full random
    Manager.TestPopulation();
    Manager.RankPopulation();
    Manager.SaveBest(1);
    }
    
    cout<<"--------------------Post Mutazione---------------"<<endl;
    
    Manager.shortPrint(3);
    Manager.SaveBestCoord();
    Manager.SaveAll();
    //Manager.Try();
    
    
    return 0;
}