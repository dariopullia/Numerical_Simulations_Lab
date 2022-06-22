
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

bool hasIntersected(double c, double y, double space){

   int n=(int)(c/space);
   //cout<<n<<endl;
   if (c+y>(n+1)*space or c-y<n*space){
      return true;
   }else{
      return false;
   }
}

double extractyAR(double r, Random* rnd){
   double x=rnd->Rannyu(0,r);
   double y=rnd->Rannyu(0,r);
   while ((x*x+y*y)>r*r){
      x=rnd->Rannyu(0,r);
      y=rnd->Rannyu(0,r);
   }
   y=r*y/sqrt(x*x+y*y); 
   return y;

}



int main (int argc, char *argv[]){

   Random rnd;

   ofstream out("data03.dat");

   int M=1000000;
   int N=100;  //numero di blocchi
   int L=M/N;
   double r=2; //raggio dell'ago
   double space=5; //distanza tra le righe
   double c;
   double max=100;
   int sum=0;
   double pi=0,pi2=0;
   double pi_prog=0,pi2_prog=0;
   

   for (int i=0; i<N; i++){ //ciclo su tutti i blocchi
      sum =0;
      for (int j=0;j<L;j++){ //ciclo su tutti i lanci nel blocco
         c=rnd.Rannyu(0, max);
         if (hasIntersected(c, extractyAR(r,&rnd), space)){ //la funzione restituisce true se c'e' il contatto, false altrimenti
            sum++;
         }
      }
      
      pi=(4*r)/(space*((double)sum/L));
      pi2=pi*pi;
      pi_prog=(pi+pi_prog*(i))/(i+1);
      pi2_prog=(pi2+pi2_prog*(i))/(i+1);
      
      out<<pi_prog<<" "<<error_prog(pi_prog, pi2_prog, i)<<endl;
   }
   return 0;
}
