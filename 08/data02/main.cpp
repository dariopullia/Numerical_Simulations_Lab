
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
   int M=100000;
   int N=100;  //numero di blocchi che AL MASSIMO accetto
   int L=M/N;
   
   metroPSI.setMuSig(metro.getMu()+rnd.Rannyu(-1,1)/beta,metro.getSig()+rnd.Rannyu(-1,1)/beta); // Il range -1,1 è completamente arbitrario, questa scelta sembra ragionevole ma potrei scegliere di dargli più o meno libertà
   double E=0; 
   double E2=0;
   /*
   for (int i=0; (i<N); i++){
      cout<<"ciclo Inf? "<<i<<endl;
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
   */
   int i=0;
   metroPSI.resetAccRate();

   do
   {

   sum=0;
   for (int j=0; j<L; j++){
      metroPSI.step_PSI();
      sum+=metroPSI.getEnergy();
      //if (i==0) cout<<sum/j<<" "<< metroPSI.getEnergy()<<" "<<metroPSI.getPos()<<endl;

   }

   E=(sum/L+E*(i))/(i+1);

   E2=((sum/L)*(sum/L)+E2*(i))/(i+1);
   i++;  
   //cout<<E<<" "<<abs(error_prog(E, E2,i)/E)<<endl;
   //cout<<"ciclo Inf? "<<i<<endl;
   } while (i==1 or (i<N and abs(error_prog(E, E2,i)/E)>0.01));
   //} while (i<N);

   //cout<<"ciclo Inf? "<<i<<endl;
   //cout<<metroPSI.getAccRate()<<" "<<beta<<endl;
   
   Enew=E;
   sigmaEnew=error_prog(E, E2,i);

}





int main (int argc, char *argv[]){
   ofstream out("data02.dat");
   ofstream outMuSig("data02_MuSig.dat");
   ofstream outMuSigFinal("data02_MuSigFinal.dat");
   ofstream outMuSigInstant("data02_MuSigInstant.dat");
   ofstream outEnergyOPT("data02_EnergyOPT.dat");   
   ofstream outXInstant("data02_XInstant.dat");

   double beta=1;
   double mu=0, mu2=0, sig=0, sig2=0;
   double musum, sigsum, sum1, sum2;
   double Eprog=1, sigmaEprog=10,E2prog;//Imposto questi valori per entrare nel ciclo
   metroPSI.setMuSig(1, 1);
   MeasureH(metroPSI, beta);
   oldmetroPSI=metroPSI;
   Eold=Enew;
   int acc=0, tent=0;

      //while (abs(sigmaEprog/Eprog)>0.005){ //Ciclo in modo da finire con un errore relativo a mia scelta
      for (int i=0; i<50; i++){ //Scelgo arbitrariamente quanti cicli fare perchè ogni ciclo aumento beta, che è inversamente proporzionale al range di valori (circa l'errore) che Mu e Sigma possono valere. 
         beta+=1.5;
         acc=0, tent=0;
         for (int i=0; i<40; i++){//Evolvo 40 volte per temperatura, dando il tempo di raffreddarsi
         MeasureH(metroPSI, beta);

         if (Enew<Eold){ //Metropolis
            oldmetroPSI=metroPSI;
            Eold=Enew;
            sigmaEold=sigmaEnew;
            acc++;
            }else{
               if (rnd.Rannyu()<exp((Eold-Enew)*beta)){
                  oldmetroPSI=metroPSI;
                  Eold=Enew;
                  sigmaEold=sigmaEnew;
                  acc++;
                  //cout<<"Accetto"<<endl;

               }else{
                  metroPSI=oldmetroPSI;
                  //cout<<"Rifiuto"<<endl;

               }
            }//fine Metropolis
            tent++;

         }
         outMuSig<<metroPSI.getMu()<<" "<<metroPSI.getSig()<<endl;
         //cout<<"Energia: "<<Eold<<" "<<sigmaEold<<endl;
         out<<Eold<<" "<<sigmaEold<<endl;
         cout<<"Acc Rate: "<<(double) acc/tent<<"  beta: "<<beta<<endl;
      }


   cout<<"Energia: "<<Eold<<" "<<sigmaEold<<endl;
   cout<<"Mu e sigma: "<<metroPSI.getMu()<<" "<<metroPSI.getSig()<<endl;

   cout<<"Fissato questo beta, mi muovo per trovare la StDev di Mu e Sigma"<<endl;

   int M=40000;
   int N=100;
   int L=M/N;

   for (int i=0; (i<N); i++){
      musum=0, sigsum=0;
      for (int j=0; j<L; j++){
         metroPSI.setMuSig(metroPSI.getMu()+rnd.Rannyu(-1,1)/beta,metroPSI.getSig()+rnd.Rannyu(-1,1)/beta); // Il range -1,1 è completamente arbitrario, questa scelta sembra ragionevole ma potrei scegliere di dargli più o meno libertà

         MeasureH(metroPSI, beta);

         if (Enew<Eold){ //Metropolis
            oldmetroPSI=metroPSI;
            Eold=Enew;
            sigmaEold=sigmaEnew;
            acc++;
            }else{
               if (rnd.Rannyu()<exp((Eold-Enew)*beta)){
                  oldmetroPSI=metroPSI;
                  Eold=Enew;
                  sigmaEold=sigmaEnew;
                  acc++;
                  //cout<<"Accetto"<<endl;

               }else{
                  metroPSI=oldmetroPSI;
                  //cout<<"Rifiuto"<<endl;

               }
            }//fine Metropolis
            tent++;
            musum +=oldmetroPSI.getMu();
            sigsum +=oldmetroPSI.getSig();
            outMuSigInstant<<oldmetroPSI.getMu()<<" "<<oldmetroPSI.getSig()<<endl;

         //if (i==0) cout<<sum/j<<" "<< metroPSI.getEnergy()<<" "<<metroPSI.getPos()<<endl;

      }


      mu=(musum/L+mu*(i))/(i+1);

      mu2=((musum/L)*(musum/L)+mu2*(i))/(i+1);
      
      sig=(sigsum/L+sig*(i))/(i+1);

      sig2=((sigsum/L)*(sigsum/L)+sig2*(i))/(i+1);
      
      //cout<<E<<" "<<error_prog(E, E2,i)<<endl;
      //cout<<"Acceptance Rate: "<<metroPSI.getAccRate()<<endl;
      cout<<mu<<" "<<error_prog(mu, mu2,N)<<" "<<sig<<" "<<error_prog(sig, sig2,N)<<endl;

      outMuSigFinal<<mu<<" "<<error_prog(mu, mu2,N)<<" "<<sig<<" "<<error_prog(sig, sig2,N)<<endl;
   }

   metroPSI.setMuSig(mu, sig);

   M=100000;
   N=100;  //numero di blocchi
   L=M/N;
   sum; 
   double E=0; 
   double E2=0;

   for (int i=0; i<N; i++){
      sum=0;

      for (int j=0; j<L; j++){
         //Faccio un passo in modalità uniforme (0) e in modalità gaussiana (1)
         metroPSI.step_PSI();
         sum+=metroPSI.getEnergy();
         //if (i==0) cout<<sum/j<<" "<< metroPSI.getEnergy()<<" "<<metroPSI.getPos()<<endl;
         outXInstant<<metroPSI.getPos()<<endl;

      }

      E=(sum/L+E*(i))/(i+1);

      E2=((sum/L)*(sum/L)+E2*(i))/(i+1);
      //cout<<E<<" "<<error_prog(E, E2,i)<<endl;
      cout<<"Acceptance Rate: "<<metroPSI.getAccRate()<<endl;

      outEnergyOPT<<E<<" "<<error_prog(E, E2,i)<<endl;

   }






   return 0;
}
