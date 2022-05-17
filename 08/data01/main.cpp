
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../rangen/random.h"
#include "metropolis.h"
using namespace std;


double error_prog(double AV, double AV2, int n){
   if (n==0){
      return 0;
   }
   else{
      return sqrt((AV2-AV*AV)/n);
   };
}





int main (int argc, char *argv[]){
   Metropolis metroPSI;

   ofstream out("data01.dat");
   int M=100000;
   int N=100;  //numero di blocchi
   int L=M/N;
   double sum; 
   double E=0; 
   double E2=0;

   //Posiziono i punti alla posizione iniziale e ne imposto il passo
   metroPSI.setPos(0);
   metroPSI.setStep(3);
   metroPSI.setMuSig(1,1);

   for (int i=0; i<N; i++){
      sum=0;

      for (int j=0; j<L; j++){
         //Faccio un passo in modalità uniforme (0) e in modalità gaussiana (1)
         metroPSI.step_PSI();
         sum+=metroPSI.getEnergy();
         //if (i==0) cout<<sum/j<<" "<< metroPSI.getEnergy()<<" "<<metroPSI.getPos()<<endl;

      }

      E=(sum/L+E*(i))/(i+1);

      E2=((sum/L)*(sum/L)+E2*(i))/(i+1);
      //cout<<E<<" "<<error_prog(E, E2,i)<<endl;
      cout<<"Acceptance Rate: "<<metroPSI.getAccRate()<<endl;

      out<<E<<" "<<error_prog(E, E2,i)<<endl;

   }

   return 0;
}
