
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
   Metropolis metro100_unif(3),metro100_gauss(3);
   Metropolis metro210_unif(3), metro210_gauss(3);

   ofstream out("data01.dat");
   ofstream out2("data01_3d.dat");
   int M=10000000;
   int N=100;  //numero di blocchi
   int L=M/N;
   double sum_100_unif, sum_100_gauss, sum_210_unif, sum_210_gauss; 
   double r_100_unif=0, r_100_gauss=0, r_210_unif=0, r_210_gauss=0; 
   double r2_100_unif=0, r2_100_gauss=0, r2_210_unif=0, r2_210_gauss=0; 
   double * start=new double[3];
   start[0]=10.0;
   start[1]=0.0;
   start[2]=0.0;
   metro100_unif.setPos(start);
   metro210_unif.setPos(start);
   metro100_gauss.setPos(start);
   metro210_gauss.setPos(start);
   metro100_unif.setStep(1.);
   metro210_unif.setStep(1.);
   metro100_gauss.setStep(1.);
   metro210_gauss.setStep(1.);    

   for (int i=0; i<N; i++){
      sum_100_unif=0;
      sum_100_gauss=0;
      sum_210_unif=0;
      sum_210_gauss=0;

      for (int j=0; j<L; j++){
         metro100_unif.step_PSI100(0);
         metro100_gauss.step_PSI100(1);
         metro210_unif.step_PSI210(0);
         metro210_gauss.step_PSI210(1);
         sum_100_unif+=metro100_unif.getR();
         sum_100_gauss+=metro100_gauss.getR();
         sum_210_unif+=metro210_unif.getR();
         sum_210_gauss+=metro210_gauss.getR();

         if (j%400==0){
            start=metro100_gauss.getPos();
            out2<<start[0]<<" "<<start[1]<<" "<<start[2]<<" ";
            start=metro210_gauss.getPos();
            out2<<start[0]<<" "<<start[1]<<" "<<start[2]<<endl;
         }

      }

      r_100_unif=(sum_100_unif/L+r_100_unif*(i))/(i+1);
      r_100_gauss=(sum_100_gauss/L+r_100_gauss*(i))/(i+1);
      r_210_unif=(sum_210_unif/L+r_210_unif*(i))/(i+1);
      r_210_gauss=(sum_210_gauss/L+r_210_gauss*(i))/(i+1);

      r2_100_unif=((sum_100_unif/L)*(sum_100_unif/L)+r2_100_unif*(i))/(i+1);
      r2_100_gauss=((sum_100_gauss/L)*(sum_100_gauss/L)+r2_100_gauss*(i))/(i+1);
      r2_210_unif=((sum_210_unif/L)*(sum_210_unif/L)+r2_210_unif*(i))/(i+1);
      r2_210_gauss=((sum_210_gauss/L)*(sum_210_gauss/L)+r2_210_gauss*(i))/(i+1);


 
      out<<r_100_unif<<" "<<error_prog(r_100_unif, r2_100_unif,i)<<" "<<r_100_gauss<<" "<<error_prog(r_100_gauss, r2_100_gauss,i)<<" "<<r_210_unif<<" "<<error_prog(r_210_unif, r2_210_unif,i)<<" "<<r_210_gauss<<" "<<error_prog(r_210_gauss, r2_210_gauss,i)<<endl;
   }

   return 0;
}
