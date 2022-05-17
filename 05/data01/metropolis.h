#ifndef __Metropolis__
#define __Metropolis__
#include "../../rangen/random.h"

class Metropolis {

private:
  double* pos;
  Random rnd;
  int dim;
  double step;
  int tentate, accettate;
protected:

public:
  // constructors
  Metropolis(int dime);
  // destructor
  ~Metropolis();
  // methods
  double* getPos();
  double getR();
  double getAccRate();  
  void setPos(double* Posi);
  void setStep(double step);
  void resetAccRate();
  void step_PSI100(int option);//0 Unif distribution, 1 Gauss distribution
  void step_PSI210(int option);//0 Unif distribution, 1 Gauss distribution
};

#endif // __Metropolis__
