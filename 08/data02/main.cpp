
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../rangen/random.h"
#include "metropolis.h"
using namespace std;



//Variabili globali
Metropolis metroPSI, oldmetroPSI;
double Enew, sigmaEnew; 
double Eold, sigmaEold; 

Random rnd;
double sum; 

int M=100000;
int N=100;  //numero di blocchi
int L=1000;

double error_prog(double AV, double AV2, int n){
   if (n==0){
      return 0;
   }
   else{
      return sqrt((AV2-AV*AV)/n);
   };
}


void MeasureH(Metropolis metro, double beta){
   //Posiziono i punti alla posizione iniziale e ne imposto il passo
   metroPSI.setMuSig(metro.getMu()+rnd.Rannyu(-1,1)/beta,metro.getSig()+rnd.Rannyu(-1,1)/beta);
   double E=0; 
   double E2=0;
   for (int i=0; i<N; i++){
      sum=0;

      for (int j=0; j<L; j++){
         metroPSI.step_PSI();
         sum+=metroPSI.getEnergy();
         //if (i==0) cout<<sum/j<<" "<< metroPSI.getEnergy()<<" "<<metroPSI.getPos()<<endl;

      }

      E=(sum/L+E*(i))/(i+1);

      E2=((sum/L)*(sum/L)+E2*(i))/(i+1);
      //cout<<E<<" "<<error_prog(E, E2,i)<<endl;
      //cout<<"Acceptance Rate: "<<metroPSI.getAccRate()<<endl;

      //out<<E<<" "<<error_prog(E, E2,i)<<endl;

   }
   Enew=E;
   sigmaEnew=error_prog(E, E2,N-1);

}





int main (int argc, char *argv[]){
   ofstream out("data02.dat");
   ofstream outMuSig("data02_MuSig.dat");

   double beta=1;
   double mu, mu2, sig, sig2;
   double musum, sigsum, sum1, sum2;
   double Eprog=1, sigmaEprog=10,E2prog;//Imposto questi valori per entrare nel ciclo
   metroPSI.setMuSig(1, 1);
   MeasureH(metroPSI, beta);
   oldmetroPSI=metroPSI;
   Eold=Enew;


      //while (abs(sigmaEprog/Eprog)>0.005){ //Ciclo in modo da finire con un errore relativo a mia scelta
      for (int i=0; i<100; i++){
         beta+=1;
         sum1=0;
         sum2=0;
         for (int i=0; i<10; i++){//Evolvo 10 volte per temperatura, dando il tempo di raffreddarsi
         musum=0, sigsum=0;
         MeasureH(metroPSI, beta);

         if (Enew<Eold){ //Metropolis
            oldmetroPSI=metroPSI;
            Eold=Enew;
            sigmaEold=sigmaEnew;
            }else{
               if (rnd.Rannyu()<exp((Eold-Enew)*beta)){
                  oldmetroPSI=metroPSI;
                  Eold=Enew;
                  sigmaEold=sigmaEnew;
                  //cout<<"Accetto"<<endl;

               }else{
                  metroPSI=oldmetroPSI;
                  //cout<<"Rifiuto"<<endl;

               }
            }//fine Metropolis

         
         sum1+=Eold;
         sum2+=Eold*Eold;

         out<<Eold<<" "<<sigmaEold<<endl;
         outMuSig<<metroPSI.getMu()<<" "<<metroPSI.getSig()<<endl;
         }
         Eprog=sum1/10;
         E2prog=sum2/10;
         sigmaEprog=error_prog(Eprog, E2prog, 10);
         cout<<Eprog<<" "<<sigmaEprog<<endl;
      }
   cout<<"Mu e sigma: "<<metroPSI.getMu()<<" "<<metroPSI.getSig()<<endl;
   return 0;
}
