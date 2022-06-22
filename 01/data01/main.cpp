
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
   ofstream out("data01.dat");

   double tiro;
   int M=100000;
   int N=100;
   int L= (int) M/N;
   double sum=0, ssum=0;
   double ave=0, save=0;
   double ave2=0, save2=0;
   double ave_prog=0, save_prog=0;
   double ave2_prog=0, save2_prog=0;
   double err_prog=0, serr_prog=0;
   double X2=0;
   int* n= new int[N];


   for (int i=0; i<N;i++){ //Ciclo sui blocchi
      sum=0;
      ssum=0;
      for (int k=0; k<N; k++){
         n[k]=0;
      }

      for (int j=0; j<L;j++){ //Ciclo in ogni blocco
         tiro=rnd.Rannyu();
         sum+=tiro;         
         ssum+=((tiro-0.5)*(tiro-0.5));
         n[(int(tiro*N))%N]++;
      }
      
      ave= sum/((double)L);
      ave2=ave*ave;
      ave_prog= (ave + ave_prog*(i))/(i+1);
      ave2_prog=(ave2 + ave2_prog*(i))/(i+1);
      err_prog=error_prog(ave_prog,ave2_prog,i);

      save= ssum/((double)L);
      save2=save*save;
      save_prog= (save + save_prog*(i))/(i+1);
      save2_prog=(save2 + save2_prog*(i))/(i+1);
      serr_prog=error_prog(save_prog,save2_prog,i);

      X2=chi2(n, L, N);

      out<<ave_prog<<" "<<err_prog<<" "<<save_prog<<" "<<serr_prog<<" "<<X2<<endl;
   }
   
   return 0;
}