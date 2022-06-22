
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

double fun(double x){ //definisco la funzione da integrare
   return M_PI*0.5*cos(M_PI*0.5*x);
}

double Inv_Cumu_Linear( double x){ //Inv della cumulativa, la scrivo qui perchè è improbabile che mi servirà ancora
   return 1-sqrt(1-x);
}

double Inv_Cumu_Cos( double x){ //Inv della cumulativa della funzione stessa. Voglio vedere varianza nulla
   return sin(M_PI*0.5*x);
}




int main (int argc, char *argv[]){
   //-----------------------------NUMERI CASUALI INIZIALIZZAZIONE------------------
   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("../../rangen/Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("../../rangen/seed.in");
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
   
   
   ofstream out("data01.dat");
   int M=1000000;
   int N=100;  //numero di blocchi
   int L=M/N;
   double IntUnif=0, IntUnif2=0;
   double IntLin=0, IntLin2=0;
   double IntCos=0, IntCos2=0;   
   double IntUnif_prog=0, IntUnif2_prog=0;
   double IntLin_prog=0, IntLin2_prog=0;   
   double IntCos_prog=0, IntCos2_prog=0;


   double sum=0, sum_lin,sum_cos;
   double tiro=0;
   for (int i=0;i<N;i++){
      sum=0;
      sum_lin=0;
      sum_cos=0;      
      for (int j=0; j<L; j++){
         tiro=rnd.Rannyu();
         sum+=fun(tiro);
         sum_lin+=fun(Inv_Cumu_Linear(tiro))/(2-2*Inv_Cumu_Linear(tiro));
         sum_cos+=fun(Inv_Cumu_Cos(tiro))/(M_PI*0.5*cos(M_PI*0.5* Inv_Cumu_Cos(tiro)));         
      }

      IntUnif= sum/L;
      IntUnif2=IntUnif*IntUnif;
      IntUnif_prog=(IntUnif+IntUnif_prog*(i))/(i+1);
      IntUnif2_prog=(IntUnif2+IntUnif2_prog*(i))/(i+1);

      IntLin= sum_lin/L;
      IntLin2=IntLin*IntLin;
      IntLin_prog=(IntLin+IntLin_prog*(i))/(i+1);
      IntLin2_prog=(IntLin2+IntLin2_prog*(i))/(i+1);


      IntCos= sum_cos/L;
      IntCos2=IntCos*IntCos;
      IntCos_prog=(IntCos+IntCos_prog*(i))/(i+1);
      IntCos2_prog=(IntCos2+IntCos2_prog*(i))/(i+1);





      out<<IntUnif_prog<<" "<<error_prog(IntUnif_prog, IntUnif2_prog,i)<<" "<<IntLin_prog<<" "<<error_prog(IntLin_prog, IntLin2_prog,i)<<" "<<IntCos_prog<<" "<<error_prog(IntCos_prog, IntCos2_prog,i)<<endl;
   }










   return 0;
}

