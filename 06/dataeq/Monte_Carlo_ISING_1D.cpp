/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <string>

#include "Monte_Carlo_ISING_1D.h"



using namespace std;



int main(int argc,char* argv[])
{ 

  if (stoi(argv[1])!=0 and stoi(argv[1])!=1) return 0; // Input non accettabile
  metro=stoi(argv[1]);
  

  if (metro) ismetro="metropolis/";
  else ismetro="gibbs/";

  for (int j=0; j<11;j++){
    temp=0.5+j*0.15;
    beta = 1.0/temp;
    cout << "Temperature = " << temp << endl;
  
    Input(); //Inizialization


    for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
    {
      Reset(iblk);   //Reset block averages

      for(int istep=1; istep <= nstep; ++istep)
      {
        Move(metro);
        Measure();
        Accumulate(); //Update block averages
      }
      Averages(iblk);   //Print results for current block
      if (iblk==nblk) PrintLast(iblk);   //Print results for current block

    }
    ConfFinal(); //Write final configuration

  }
  return 0;
}


void Input(void)
{
  ifstream ReadInput, ReadConf;

  cout << "Classic 1D Ising model             " << endl;
  cout << "Monte Carlo simulation             " << endl << endl;
  cout << "Nearest neighbour interaction      " << endl << endl;
  cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
  cout << "The program uses k_B=1 and mu_B=1 units " << endl;

  
//Read input informations
  ReadInput.open(ismetro+"input.dat");


  ReadInput >> nspin;
  cout << "Number of spins = " << nspin << endl;

  ReadInput >> J;
  cout << "Exchange interaction = " << J << endl;

  ReadInput >> h;
  cout << "External field = " << h << endl << endl;
  hstring=to_string(h);  


  ReadInput >> metro; // if=1 Metropolis else Gibbs

  ReadInput >> restart; // if=1 Metropolis else Gibbs


  ReadInput >> nblk;

  ReadInput >> nstep;

  if(metro==1) cout << "The program perform Metropolis moves" << endl;
  else cout << "The program perform Gibbs moves" << endl;
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close();


//Prepare arrays for measurements
  iu = 0; //Energy
  ic = 1; //Heat capacity
  im = 2; //Magnetization
  ix = 3; //Magnetic susceptibility
 
  n_props = 4; //Number of observables

//initial configuration
  if (restart){
    ReadConf.open("../dataeq/"+ismetro+"conf_final/"+to_string(temp)+"_config.final");

    for (int i=0; i<nspin; ++i)
    {
      ReadConf>>s[i];
    }
    ReadConf.close();

  }else{

    for (int i=0; i<nspin; ++i)
    {
      if(rnd.Rannyu() >= 0.5) s[i] = 1;
      else s[i] = -1;
    }
  }

  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iu]/(double)nspin << endl;
}


void Move(int metro)
{
  int o,snew;
  double p, energy_old, energy_new, sm,deltaE;
  double energy_up, energy_down;

  for(int i=0; i<nspin; ++i)
  {
  //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin);

    if(metro==1) //Metropolis
    {
      snew=-s[o];

      deltaE=2*Boltzmann(snew, o);

      if (deltaE<0){
          s[o]=snew;     
          accepted++;   
      }else{
          if (rnd.Rannyu()<exp(-deltaE*beta)){
              s[o]=snew;      
              accepted++;  
          }
      }
      //cout<<"eccomi"<<endl;
      attempted++;
    }
    else //Gibbs sampling
    {

      deltaE=-2*Boltzmann(1, o);
      if(rnd.Rannyu() < 1.0/(1.0+exp(-beta*deltaE))){
        s[o]=1;
        accepted++;
      }else{
        s[o]=-1;

      }
      attempted++;
   
    }
  }
}

double Boltzmann(int sm, int ip)
{
  double ene = -J * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
  return ene;
}

void Measure()
{
  int bin;
  double u = 0.0, m = 0.0;
  double c=0., x, H=0.;

//cycle over spins
  for (int i=0; i<nspin; ++i)
  {
    H= -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);

    u += H;
    c+= H*H;
    m += s[i];
  }

  walker[iu] = u;
  walker[ic] = u*u;
  //cout<<walker[ic]<<endl;
  walker[im] = m;
  walker[ix] = beta*m*m;


}


void Reset(int iblk) //Reset block averages
{
   
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0;
}


void Averages(int iblk) //Print results for current block
{
    
   ofstream Ene, Heat, Mag, Chi;

    //cout << "Block number " << iblk << endl;
    //cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
    Ene.open(ismetro+"outputs/"+to_string(temp)+"output.ene."+hstring,ios::app);
    stima_u = blk_av[iu]/blk_norm/(double)nspin; //Energy
    glob_av[iu]  += stima_u;
    glob_av2[iu] += stima_u*stima_u;
    err_u=Error(glob_av[iu],glob_av2[iu],iblk);
    Ene << iblk <<  " " << stima_u << " " << glob_av[iu]/(double)iblk <<  " " << err_u << endl;
    Ene.close(); 


    Heat.open(ismetro+"outputs/"+to_string(temp)+"output.heat."+hstring,ios::app);
    stima_c = beta*beta * (blk_av[ic]/blk_norm - pow(blk_av[iu]/blk_norm, 2))/(double)nspin;//Heat
    glob_av[ic]  += stima_c;
    glob_av2[ic] += stima_c*stima_c;
    err_c=Error(glob_av[ic],glob_av2[ic],iblk);
    Heat << iblk <<  " " << stima_c << " " << glob_av[ic]/(double)iblk <<  " " << err_c << endl;
    Heat.close(); 

    Mag.open(ismetro+"outputs/"+to_string(temp)+"output.mag."+hstring,ios::app);
    stima_m = blk_av[im]/blk_norm/(double)nspin; //Magnetization
    glob_av[im]  += stima_m;
    glob_av2[im] += stima_m*stima_m;
    err_m=Error(glob_av[im],glob_av2[im],iblk);
    Mag << iblk <<  " " << stima_m << " " << glob_av[im]/(double)iblk <<  " " << err_m << endl;
    Mag.close(); 

    Chi.open(ismetro+"outputs/"+to_string(temp)+"output.chi."+hstring,ios::app);
    stima_x = blk_av[ix]/blk_norm/(double)nspin; //Magnetic susceptibility
    glob_av[ix]  += stima_x;
    glob_av2[ix] += stima_x*stima_x;
    err_x=Error(glob_av[ix],glob_av2[ix],iblk);
    Chi << iblk <<  " " << stima_x << " " << glob_av[ix]/(double)iblk <<  " " << err_x << endl;
    Chi.close(); 


    //cout << "----------------------------" << endl << endl;
}


void PrintLast(int iblk) //Print results for current block
{
    
   ofstream Ene, Heat, Mag, Chi;

    cout << "Block number " << iblk << endl;
    cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
    Ene.open(ismetro+"last_output.ene."+hstring,ios::app);
    Ene << iblk <<  " " << stima_u << " " << glob_av[iu]/(double)iblk <<  " " << err_u << endl;
    Ene.close(); 


    Heat.open(ismetro+"last_output.heat."+hstring,ios::app);
    Heat << iblk <<  " " << stima_c << " " << glob_av[ic]/(double)iblk <<  " " << err_c << endl;
    Heat.close(); 

    Mag.open(ismetro+"last_output.mag."+hstring,ios::app);
    Mag << iblk <<  " " << stima_m << " " << glob_av[im]/(double)iblk <<  " " << err_m << endl;
    Mag.close(); 

    Chi.open(ismetro+"last_output.chi."+hstring,ios::app);
    Chi << iblk <<  " " << stima_x << " " << glob_av[ix]/(double)iblk <<  " " << err_x << endl;
    Chi.close(); 


    cout << "----------------------------" << endl << endl;
}


void ConfFinal(void)
{
  ofstream WriteConf;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open(ismetro+"conf_final/"+to_string(temp)+"_config.final");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  rnd.SaveSeed();
}

int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
