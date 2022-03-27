
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "/home/dario/Uni_ubu/lsn/rangen/random.h"

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
   //-----------------------------NUMERI CASUALI INIZIALIZZAZIONE------------------
   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("/home/dario/Uni_ubu/lsn/rangen/Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("/home/dario/Uni_ubu/lsn/rangen/seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;
   //-----------------------------FINE INIZIALIZZAZIONE------------------
   
   
   ofstream out("data02.dat");
   double unif1, unif2, unif10, unif100;
   double exp1, exp2, exp10, exp100;
   double lorentz1, lorentz2, lorentz10, lorentz100;
   double tirou, tiroe, tirol;
   int N=10e4;
   for (int i=0;i<N;i++){
      unif2=0, unif10=0, unif100=0;
      exp2=0, exp10=0, exp100=0;
      lorentz2=0, lorentz10=0, lorentz100=0;  
      for (int j=0;j<100;j++){
         tirou=rnd.Rannyu();
         tiroe=rnd.Exp(1);
         tirol=rnd.Lorentz(0,1);
         if (j==0) {
            unif1=tirou;
            exp1=tiroe;
            lorentz1=tirol;
         }
         if(j<2){
            unif2+=tirou;
            exp2+=tiroe;
            lorentz2+=tirol;            
         }
         if(j<10){
            unif10+=tirou;
            exp10+=tiroe;
            lorentz10+=tirol;            

         }         
         unif100+=tirou;
         exp100+=tiroe;
         lorentz100+=tirol;            

      }
         
      out<<unif1<<" "<<unif2/2<<" "<<unif10/10<<" "<<unif100/100<<" "<<exp1<<" "<<exp2/2<<" "<<exp10/10<<" "<<exp100/100<<" "<<lorentz1<<" "<<lorentz2/2<<" "<<lorentz10/10<<" "<<lorentz100/100<<endl;

   }

   return 0;
}

