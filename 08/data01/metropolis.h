#ifndef __Metropolis__
#define __Metropolis__
#include "../../rangen/random.h"

class Metropolis {

private:
  double pos;
  Random rnd;
  double step;
  double mu, sig;
  int accettato, tentato;
protected:

public:
  // constructors
  Metropolis();
  // destructor
  ~Metropolis();
  // methods
  double getPos();
  double getEnergy();
  double getAccRate();
  void resetAccRate();
  void setPos(double Posi);
  void setStep(double step);
  void setMuSig(double m, double s);
  void step_PSI();//0 Unif distribution
};

#endif // __Metropolis__
