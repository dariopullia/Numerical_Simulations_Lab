#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "metropolis.h"
#include "../../rangen/random.h"
using namespace std;

Metropolis :: Metropolis(){
    step=1.0;
    pos=0;
    accettato=0;
    tentato=0;
    rnd.SetPrimesComb(32);
    return;
}

Metropolis :: ~Metropolis(){

}


double Metropolis :: getPos() {
    return (pos);
}
double Metropolis :: getSig() {
    return (sig);
}
double Metropolis :: getMu() {
    return (mu);
}


double Metropolis :: getAccRate() {
    return (double)accettato/tentato;
}

double Metropolis :: getEnergy() {
    double Num1=-0.5*(
                      (exp(-(pos-mu)*(pos-mu)/(2*sig*sig))*((pos-mu)*(pos-mu)/pow(sig,4)-1/pow(sig,2)))+
                      (exp(-(pos+mu)*(pos+mu)/(2*sig*sig))*((pos+mu)*(pos+mu)/pow(sig,4)-1/pow(sig,2)))
                     );
    double Num2=pow(pos,4)-2.5*pow(pos,2);
    double Den = exp(-(pos-mu)*(pos-mu)/(2*sig*sig))+
                 exp(-(pos+mu)*(pos+mu)/(2*sig*sig));
    
    return Num2+Num1/Den;
}

void Metropolis :: setPos(double posi){
    pos=posi;
    }
void Metropolis :: resetAccRate(){
    accettato=0;
    tentato=0;
    }


void Metropolis :: setMuSig(double munew,double signew){
    mu=munew;
    sig=signew;
    }


void Metropolis :: setStep(double s){
    step=s;
}

void Metropolis :: step_PSI(){
    double newpos;
    newpos=pos+rnd.Rannyu(-step,step);

    double pold=pow(exp(-(pos-mu)*(pos-mu)/(2*sig*sig))
                +exp(-(pos+mu)*(pos+mu)/(2*sig*sig)),2);

    double pnew=pow(exp(-(newpos-mu)*(newpos-mu)/(2*sig*sig))
                +exp(-(newpos+mu)*(newpos+mu)/(2*sig*sig)),2);

    if (pnew>pold){
        pos=newpos;     
        accettato++;
    }else{
        if (rnd.Rannyu()<pnew/pold){
            pos=newpos;
            accettato++;    
            }

        }
    tentato++;
}
