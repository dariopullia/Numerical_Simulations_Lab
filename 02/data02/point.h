#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "../../rangen/random.h"


#ifndef __Point__
#define __Point__

using namespace std;

class Point {

private:
  double x, y, z;
  Random rnd;

protected:

public:
  // constructors
  Point();
  // destructor
  ~Point();
  // methods
  void DiscreteRandomStep(double r);
  void ContinuumRandomStep(double r);
  double GetR2();
  void ResetToZero();
};




#endif