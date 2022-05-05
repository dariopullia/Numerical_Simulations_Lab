#ifndef __Metropolis__
#define __Metropolis__
#include "../../rangen/random.h"
int Pbc(int i, int ntot){  //Algorithm for periodic boundary conditions
    if(i >= ntot) i = i - ntot;
    else if(i < 0) i = i + ntot;
    return i;
}



class Metropolis {

private:
  double* pos;
  Random rnd;
  int dim;
  double h; //External magnetic field
  double T; //Temperature
  double E; //Current energy
protected:

public:
  // constructors
  Metropolis(int dime);
  // destructor
  ~Metropolis();
  // methods
  double* getPos();
  void setPos(double* Posi);
  void setH(double h);
  void spin_flip_gibbs();// Spin flip using gibbs
  void spin_flip();//Spin flip using metropolis

};

#endif // __Metropolis__
