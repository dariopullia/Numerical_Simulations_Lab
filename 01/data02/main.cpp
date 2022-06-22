
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../rangen/random.h"

using namespace std;


double error_prog(double AV, double AV2, int n){
   if (n==0){
      return 0;
   }
   else{
      return sqrt((AV2-AV*AV)/n);
   };
}
double chi2(int* n, int L, int N){
   double chi2=0;
   for (int i=0; i<N;i++){
      chi2+=(n[i]-L/N)*(n[i]-L/N)/((double)L/N);
   }

   return chi2;
}


int main (int argc, char *argv[]){

   Random rnd;
   ofstream out("data02.dat");
   double unif1, unif2, unif10, unif100;
   double exp1, exp2, exp10, exp100;
   double lorentz1, lorentz2, lorentz10, lorentz100;
   double tirou, tiroe, tirol;
   int N=10e4;
   
   for (int i=0;i<N;i++){//Ciclo sui blocchi
      unif2=0, unif10=0, unif100=0;
      exp2=0, exp10=0, exp100=0;
      lorentz2=0, lorentz10=0, lorentz100=0;  
      for (int j=0;j<100;j++){ //Ciclo in ogni blocco
         tirou=rnd.Rannyu();
         tiroe=rnd.Exp(1);
         tirol=rnd.Lorentz(0,1);
         if (j==0) {//Caso 1 passo per blocco
            unif1=tirou;
            exp1=tiroe;
            lorentz1=tirol;
         }
         if(j<2){//Caso 2 passi per blocco
            unif2+=tirou;
            exp2+=tiroe;
            lorentz2+=tirol;            
         }
         if(j<10){//Caso 10 passi per blocco
            unif10+=tirou;
            exp10+=tiroe;
            lorentz10+=tirol;            

         }         //Caso 100 passi per blocco
         unif100+=tirou;
         exp100+=tiroe;
         lorentz100+=tirol;            

      }
         
      out<<unif1<<" "<<unif2/2<<" "<<unif10/10<<" "<<unif100/100<<" "<<exp1<<" "<<exp2/2<<" "<<exp10/10<<" "<<exp100/100<<" "<<lorentz1<<" "<<lorentz2/2<<" "<<lorentz10/10<<" "<<lorentz100/100<<endl;

   }

   return 0;
}

