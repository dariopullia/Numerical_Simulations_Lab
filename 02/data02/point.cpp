#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "point.h"

using namespace std;



Point :: Point(){
    this->x=0;
    this->y=0;
    this->z=0;

}

Point :: ~Point(){}

void Point :: DiscreteRandomStep(double r){
  
  int dir=rnd.Rannyu(0,6);
    if (dir==0){
      this->x+=r;
    }
    if (dir==1){
      this->x-=r;
    }
    if (dir==2){
      this->y+=r;
    }
    if (dir==3){
      this->y-=r;
    }
    if (dir==4){
      this->z+=r;
    }
    if (dir==5){
      this->z-=r;
    }
  return;
}

void Point :: ContinuumRandomStep(double r){

    double theta, phi;
    theta=rnd.Rannyu(0,M_PI);
    phi=rnd.Rannyu(0,2*M_PI);

    this->x+=r*sin(theta)*cos(phi) ;
    this->y+=r*sin(theta)*sin(phi) ;
    this->z+=r*cos(theta);

  return;
}

void Point :: ResetToZero(){
  this->x=0;
  this->y=0;
  this->z=0;

  return;
}

double Point::GetR2(){
    return (this->x*this->x+this->y*this->y+this->z*this->z);
}



