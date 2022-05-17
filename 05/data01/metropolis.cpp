#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "metropolis.h"
#include "../../rangen/random.h"
using namespace std;

Metropolis :: Metropolis(int dime){
    dim =dime;
    step=1.0;
    tentate=0;
    accettate=0;
    pos=new double[dime];
    for (int i=0; i<dime;i++){
        pos[i]=0.0;
    }
  return;
}

Metropolis :: ~Metropolis(){
    delete[] pos;

}


double Metropolis :: getR() {
    double r2=0;
    for (int i=0; i<dim; i++){
        r2+=(pos[i])*((pos[i]));
    }
    return sqrt(r2);
}
double Metropolis :: getAccRate() {

    return (double)accettate/tentate;

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

void Metropolis :: resetAccRate(){
    accettate=0;
    tentate=0;

}



void Metropolis :: setStep(double s){
    step=s;
}

void Metropolis :: step_PSI100(int op){
    double* newpos= new double[dim];
    if (op==0){
        for (int i=0; i<dim; i++){
            newpos[i]=pos[i]+rnd.Rannyu(-step*0.5,step*0.5);
        }
    }else if(op==1){
        for (int i=0; i<dim; i++){
            newpos[i]=pos[i]+rnd.Gauss(0,step);
        }        
    }else {
        cout<<"option can be 1 or 0"<<endl;
        return;
        }

    double r=this->getR();
    double pold=(exp(-r)/sqrt(M_PI))*(exp(-r)/sqrt(M_PI));
    r=0;
    for (int i=0; i<dim; i++){
        r+=(newpos[i])*((newpos[i]));
    }
    r=sqrt(r);
    double pnew=(exp(-r)/sqrt(M_PI))*(exp(-r)/sqrt(M_PI));

    if (pnew>pold){
        delete[] pos;
        pos=newpos;
        accettate++;        
    }else{
        if (rnd.Rannyu()<pnew/pold){
            delete[] pos;
            pos=newpos;        
            accettate++;        
        }
    }
    tentate++;
}

void Metropolis :: step_PSI210(int op){
    double* newpos= new double[dim];
    if (op==0){
        for (int i=0; i<dim; i++){
            newpos[i]=pos[i]+rnd.Rannyu(-step*0.5,step*0.5);
        }
    }else if(op==1){
        for (int i=0; i<dim; i++){
            newpos[i]=pos[i]+rnd.Gauss(0,step);
        }        
    }else {
        cout<<"option can be 1 or 0"<<endl;
        return;
        }

    double r=this->getR();
    double costheta=pos[2]/r;

    double pold=(exp(-r*0.5)*r*costheta/(8*sqrt(M_PI/2)))*(exp(-r*0.5)*r*costheta/(8*sqrt(M_PI/2)));
    r=0;
    for (int i=0; i<dim; i++){
        r+=(newpos[i])*((newpos[i]));
    }
    r=sqrt(r);
    costheta=newpos[2]/r;
    double pnew=(exp(-r*0.5)*r*costheta/(8*sqrt(M_PI/2)))*(exp(-r*0.5)*r*costheta/(8*sqrt(M_PI/2)));

    if (pnew>pold){
        delete[] pos;
        pos=newpos;        
        accettate++;
    }else{
        if (rnd.Rannyu()<pnew/pold){
            delete[] pos;
            pos=newpos;        
            accettate++;
        }
    }

    tentate++;
}
