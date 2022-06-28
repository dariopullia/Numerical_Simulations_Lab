
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "../../rangen/random.h"
#include "point.h"
using namespace std;


double error_prog_sqrt(double AV, double AV2, int n){
   if (n==0){
      return 0;
   }
   else{
      return 0.5*sqrt(AV)*sqrt((AV2-AV*AV)/n)/AV;
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
   Point Disc, Cont;
   
   ofstream out("data02.dat");
   int M=10000; //numero di punti ubriachi
   int N=100;  //numero di blocchi, non serve ma è buona prassi
   int L=M/N; //numero di punti per blocco
   double a=1; //lunghezza del passo
   int n_steps=100; //numero di passi per punto
   double RDisc[n_steps], RCont[n_steps],RDisc2[n_steps], RCont2[n_steps];
   double RDisc_prog[n_steps], RCont_prog[n_steps],RDisc2_prog[n_steps], RCont2_prog[n_steps];
   for (int i=0; i<n_steps; i++){//porto tutti i contatori a 0
      RDisc[i]=0;
      RCont[i]=0;
      RDisc2[i]=0;
      RCont2[i]=0;
      RDisc_prog[i]=0;
      RCont_prog[i]=0;
      RDisc2_prog[i]=0;
      RCont2_prog[i]=0;
   }


   for (int k=0; k<N; k++){       
      for (int j=0; j<L; j++){
         Disc.ResetToZero();
         Cont.ResetToZero();
         for (int i=0;i<n_steps;i++){
            Disc.DiscreteRandomStep(a);
            Cont.ContinuumRandomStep(a);
            RDisc[i]+=Disc.GetR2();
            RCont[i]+=Cont.GetR2();
         
         }


         }
      for (int i=0; i<n_steps; i++){
         RDisc[i]=RDisc[i]/L;
         RDisc2[i]=RDisc[i]*RDisc[i];
         RDisc_prog[i]=(RDisc[i]+RDisc_prog[i]*(k))/(k+1);
         RDisc2_prog[i]=(RDisc2[i]+RDisc2_prog[i]*(k))/(k+1);
         RCont[i]=RCont[i]/L;
         RCont2[i]=RCont[i]*RCont[i];
         RCont_prog[i]=(RCont[i]+RCont_prog[i]*(k))/(k+1);
         RCont2_prog[i]=(RCont2[i]+RCont2_prog[i]*(k))/(k+1);


      }

      //Se volessi vedere per ogni iesimo passo il miglioramento, estrarrei qui il dato. Non mi serve, vado avanti
   }
   

   out<<0<<" "<<0<<" "<<0<<" "<<0<<endl; //Aggiungo il primo punto, che è 0 al passo zeresimo
   for (int i=0; i<n_steps; i++){ //riempio il file di output
      out<<sqrt(RDisc_prog[i])<<" "<<(error_prog_sqrt(RDisc_prog[i], RDisc2_prog[i],N))<<" "<<sqrt(RCont_prog[i])<<" "<<(error_prog_sqrt(RCont_prog[i],RCont2_prog[i],N))<<endl;
      //out<<(RDisc_prog[i])<<" "<<(error_prog(RDisc_prog[i], RDisc2_prog[i],N))<<" "<<(RCont_prog[i])<<" "<<(error_prog(RCont_prog[i],RCont2_prog[i],N))<<endl;

   }

   return 0;
}
