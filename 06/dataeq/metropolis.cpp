#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "metropolis.h"
#include "../../rangen/random.h"
using namespace std;


Metropolis :: Metropolis(int dime){
    dim =dime;
    h=0.;
    T=1;
    
    pos=new double[dime];
    for (int i=0; i<dime; ++i)
    {
        if(rnd.Rannyu() >= 0.5) pos[i] = 1;
        else pos[i] = -1;
    }
    
    E=0;
    for (int i=0; i<dime-1; ++i){
        E+=-1*(pos[i]*pos[Pbc(i+1, dime)])-h*0.5*(pos[i]+pos[Pbc(i+1, dime)]);
    }    

  return;
}

Metropolis :: ~Metropolis(){
    delete[] pos;

}



double* Metropolis :: getPos() {
    double * cedibile=new double[dim];
    for(int i=0; i<dim; i++){
    cedibile[i]=pos[i];
}
    return cedibile;
}

void Metropolis :: setPos(double* posi){
    for(int i=0; i<dim; i++){
        pos[i]=posi[i];
    }

}

void Metropolis :: setH(double bfield){
    h=bfield;
}


void Metropolis :: spin_flip(){
    int newpos;
    int i= (int)rnd.Rannyu(0,dim);
    if (pos[i]==-1) newpos=1;
    if (pos[i]==1) newpos=-1;

    double deltaE=-(-1*(pos[Pbc(i-1, dim)]*pos[i]+pos[i]*pos[Pbc(i+1, dim)])-h*0.5*(pos[Pbc(i-1, dim)]+pos[i]+pos[i]+pos[Pbc(i+1, dim)]))-(-1*(pos[Pbc(i-1, dim)]*newpos+newpos*pos[Pbc(i+1, dim)])-h*0.5*(pos[Pbc(i-1, dim)]+newpos+newpos+pos[Pbc(i+1, dim)]));


    if (deltaE<0){
        pos[i]=newpos;        
    }else{
        if (rnd.Rannyu()<exp(-deltaE/T)){
            pos[i]=newpos;        
        }
    }
}





void Metropolis :: spin_flip_gibbs(){
    int newpos=1;
    int i= (int)rnd.Rannyu(0,dim);
    if (pos[i]==newpos){

    }else{

    }

    double deltaE=-(-1*(pos[i-1]*pos[i]+pos[i]*pos[i+1])-h*0.5*(pos[i-1]+pos[i]+pos[i]+pos[i+1]))-(-1*(pos[i-1]*newpos+newpos*pos[i+1])-h*0.5*(pos[i-1]+newpos+newpos+pos[i+1]));
    E*=deltaE;

    //prob=exp(-E/T)/



}

