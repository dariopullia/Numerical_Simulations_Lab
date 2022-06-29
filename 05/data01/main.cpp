
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
   //int M=10000; // Per vedere bene l'effetto della mancata EQ
   int M=10000000;
   int N=100;  //numero di blocchi
   //int M=1000; // scommentare per misurare l'autocorrelazione
   //int N=1;  //

   int L=M/N;
   double sum_100_unif, sum_100_gauss, sum_210_unif, sum_210_gauss; 
   double r_100_unif=0, r_100_gauss=0, r_210_unif=0, r_210_gauss=0; 
   double r2_100_unif=0, r2_100_gauss=0, r2_210_unif=0, r2_210_gauss=0; 
   double * start=new double[3];
   start[0]=3.0; //Posizione iniziale. 100.0 per apprezzare la differenza
   start[1]=0.0;
   start[2]=0.0;
   //Posiziono i punti alla posizione iniziale e ne imposto il passo
   metro100_unif.setPos(start);
   metro210_unif.setPos(start);
   metro100_gauss.setPos(start);
   metro210_gauss.setPos(start);
   metro100_unif.setStep(2.5);
   metro210_unif.setStep(5.);
   metro100_gauss.setStep(0.8);
   metro210_gauss.setStep(1.8);    

   for (int i=0; i<N; i++){
      sum_100_unif=0;
      sum_100_gauss=0;
      sum_210_unif=0;
      sum_210_gauss=0;
      metro100_unif.resetAccRate();
      metro100_gauss.resetAccRate();
      metro210_unif.resetAccRate();
      metro210_gauss.resetAccRate();

      for (int j=0; j<L; j++){
         //Faccio un passo in modalità uniforme (0) e in modalità gaussiana (1)
         metro100_unif.step_PSI100(0);
         metro100_gauss.step_PSI100(1);
         metro210_unif.step_PSI210(0);
         metro210_gauss.step_PSI210(1);
         sum_100_unif+=metro100_unif.getR();
         sum_100_gauss+=metro100_gauss.getR();
         sum_210_unif+=metro210_unif.getR();
         sum_210_gauss+=metro210_gauss.getR();

         //if (j%4==0){ //Per vedere il punto spostarsi, scommentare anche qui
         if (j%400==0){ //Estraggo dei punti per il grafico 3D
            start=metro100_gauss.getPos();
            out2<<start[0]<<" "<<start[1]<<" "<<start[2]<<" ";
            start=metro210_gauss.getPos();
            out2<<start[0]<<" "<<start[1]<<" "<<start[2]<<endl;
         }
         //out<<metro100_unif.getR()<<" "<<metro100_gauss.getR()<<" "<<metro210_unif.getR()<<" "<<metro210_gauss.getR()<<endl;

      }

      r_100_unif=(sum_100_unif/L+r_100_unif*(i))/(i+1);
      r_100_gauss=(sum_100_gauss/L+r_100_gauss*(i))/(i+1);
      r_210_unif=(sum_210_unif/L+r_210_unif*(i))/(i+1);
      r_210_gauss=(sum_210_gauss/L+r_210_gauss*(i))/(i+1);

      r2_100_unif=((sum_100_unif/L)*(sum_100_unif/L)+r2_100_unif*(i))/(i+1);
      r2_100_gauss=((sum_100_gauss/L)*(sum_100_gauss/L)+r2_100_gauss*(i))/(i+1);
      r2_210_unif=((sum_210_unif/L)*(sum_210_unif/L)+r2_210_unif*(i))/(i+1);
      r2_210_gauss=((sum_210_gauss/L)*(sum_210_gauss/L)+r2_210_gauss*(i))/(i+1);


      cout<<"--------------------------------"<<endl;
      cout<<"Acc. rate 100 Uniform: "<<metro100_unif.getAccRate()<<endl;
      cout<<"Acc. rate 100 Gauss: "<<metro100_gauss.getAccRate()<<endl;
      cout<<"Acc. rate 210 Uniform: "<<metro210_unif.getAccRate()<<endl;
      cout<<"Acc. rate 210 Gauss: "<<metro210_gauss.getAccRate()<<endl;
      cout<<"--------------------------------"<<endl;
      out<<r_100_unif<<" "<<error_prog(r_100_unif, r2_100_unif,i)<<" "<<r_100_gauss<<" "<<error_prog(r_100_gauss, r2_100_gauss,i)<<" "<<r_210_unif<<" "<<error_prog(r_210_unif, r2_210_unif,i)<<" "<<r_210_gauss<<" "<<error_prog(r_210_gauss, r2_210_gauss,i)<<endl;
   }

   return 0;
}
