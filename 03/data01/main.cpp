
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


double N(double x){
   return 0.5*(1+erf(x/sqrt(2)));   
}


double put_pricerice(double St, double t, double K, double r, double T, double sigma){


   double d1=(log(St/K)+(r+sigma*sigma*(T-t)/2));
   double d2=d1-sigma*sqrt(T-t);

   return St*(N(d1)-1)-K*exp(-r*(T-t))*(N(d2)-1);

}


double call_pricerice(double St, double t, double K, double r, double T, double sigma){


   double d1=(log(St/K)+(r+sigma*sigma*(T-t)/2));
   double d2=d1-sigma*sqrt(T-t);

   return St*N(d1)-K*exp(-r*(T-t))*N(d2);

}

double S(double t, double S0, double mu, double sigma, double Wt){
   
   return S0*exp((mu-0.5*sigma*sigma)*t+ sigma*Wt);
}


int main (int argc, char *argv[]){
   //-----------------------------NUMERI CASUALI INIZIALIZZAZIONE------------------
   Random rnd;
   //-----------------------------FINE INIZIALIZZAZIONE------------------
   
   
   ofstream out("data01.dat");
   int M=1000000;
   int N=100;  //numero di blocchi
   int L=M/N;
   int n_steps=100; //numero di passi per il calcolo iterativo
   double delta_t=0;
   double S0=100, T=1, K=100, r=0.1, sigma=0.25; //inserisco i dati
   double sum_put_dir, sum_call_dir;
   double put_price_dir=0, call_price_dir=0,put_price_dir2=0, call_price_dir2=0;

   double sum_put_step, sum_call_step;
   double put_price_step=0, call_price_step=0,put_price_step2=0, call_price_step2=0;

   double ST_direct, ST_steps;
   for (int i=0; i<N; i++){
      sum_call_dir=0;
      sum_put_dir=0;
      sum_call_step=0;
      sum_put_step=0;

      for (int j=0; j<L; j++){
         ST_direct=S0*exp((r-0.5*sigma*sigma)*T+ sigma*(rnd.Gauss(0,1))*sqrt(T));
         ST_steps=S0;
         for (int k=0; k<n_steps;k++){
            delta_t= (double) T/n_steps;
            ST_steps=ST_steps*exp((r-0.5*sigma*sigma)*delta_t+ sigma*(rnd.Gauss(0,1))*sqrt(delta_t));
         }
         sum_call_dir+=exp(-r*T)*max(0., ST_direct-K);
         sum_put_dir+=exp(-r*T)*max(0.,K-ST_direct);
         sum_call_step+=exp(-r*T)*max(0., ST_steps-K);
         sum_put_step+=exp(-r*T)*max(0.,K-ST_steps);


      }


      call_price_dir=(sum_call_dir/L+call_price_dir*(i))/(i+1);
      call_price_dir2=((sum_call_dir/L)*(sum_call_dir/L)+call_price_dir2*(i))/(i+1);

      put_price_dir=(sum_put_dir/L+put_price_dir*(i))/(i+1);
      put_price_dir2=((sum_put_dir/L)*(sum_put_dir/L)+put_price_dir2*(i))/(i+1);

      call_price_step=(sum_call_step/L+call_price_step*(i))/(i+1);
      call_price_step2=((sum_call_step/L)*(sum_call_step/L)+call_price_step2*(i))/(i+1);

      put_price_step=(sum_put_step/L+put_price_step*(i))/(i+1);
      put_price_step2=((sum_put_step/L)*(sum_put_step/L)+put_price_step2*(i))/(i+1);


      out<<call_price_dir<<" "<<error_prog(call_price_dir, call_price_dir2,i)<<" "<<put_price_dir<<" "<<error_prog(put_price_dir, put_price_dir2,i)<<" "<<call_price_step<<" "<<error_prog(call_price_step, call_price_step2,i)<<" "<<put_price_step<<" "<<error_prog(put_price_step, put_price_step2,i)<<endl;

   }

   return 0;
}
