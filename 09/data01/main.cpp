#include <iostream>
#include <fstream>
#include <string>
#include "../../rangen/random.h"
#include "path.h"


using namespace std;


int main (int argc, char *argv[]){
    Manager Manager(100);
    Manager.SetShape(1);//0 Circ, 1 Square
    Manager.CreateRegion(); 
    Manager.SaveRegion();
        
    Manager.SetNPaths(1000);
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
    
    for (int i=0; i<800;i++){
    Manager.Mutate();
    Manager.TestPopulation();
    Manager.RankPopulation();
    Manager.SaveBest(1);

    }
    
    cout<<"--------------------Post Mutazione---------------"<<endl;
    
    Manager.shortPrint(3);
    Manager.SaveBestCoord();

    //Manager.Try();
    
    
    return 0;
}