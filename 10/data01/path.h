#include <fstream>
#include <string>

#include "../../rangen/random.h"

using namespace std;

#ifndef __Town__
#define __Town__

class Town {

private:
    double X, Y;
    int ID;

    Town* Next;
    Town* Previous;
  
protected:

public:
  // constructors
  Town();
  // destructor
  ~Town();
  // methods
  double DistanceFrom(Town*);
  void SetX(double);
  void SetY(double);
  void SetID(int i){ID=i;};

  double GetX(){return X;};
  double GetY(){return Y;};
  double GetID(){return ID;};

  void SetNext(Town* t) {Next=t;};
  void SetPrevious(Town* t){Previous =t;};
  Town* GetNext() {return Next;};
  Town* GetPrevious(){return Previous;};
  void print();
  void shortPrint();

};

#endif //__Town__



#ifndef __Path__
#define __Path__

class Path {

private:
  Town *start;
  int dim;
  double len;
protected:

public:



  // constructors
  Path(int);
  Path();

  // destructor
  ~Path();
  // methods
    void IsCorrect();
    void Append(double, double,int);
    Town* GetLastTown();
    void Dispose();
    void MeasureLen();
    void setDim(int n){dim=n;};
    void setLen(double n){len=n;};
    double GetLen(){return len;};
    int GetDim(){return dim;};    
    Town* GetStart(){return start;};
    void print();
    void shortPrint();    
    void Swap(int, int, int);
    void Invert(int,int);
    void Shift(int, int,int);
    void Crossover(Path, int, int);
    void Fix();





};

#endif // __Path__

#ifndef __Manager__
#define __Manager__

class Manager {

private:
  double* Xregion;
  double* Yregion;
  Random rnd;
  int dim, npaths;
  Path** paths;
  int shape;
  string dir;

protected:

public:
  // constructors
  Manager(int);
  // destructor
  ~Manager();
  // methods
  void SetNPaths(int n ){npaths=n;}
  void CreateRegion(); 
  void SetShape(int); //0 Circ, 1 Square
  void LoadMap(string);
  void SetRandomComb(int n) {rnd.SetPrimesComb(n);};
  void ExtendDir(string s){dir=dir+s+"/";};

  void CreateRegionCirc();
  void CreateRegionSquare();
  Path* CreateRandomPath();
  void CreatePopulation();
  void TestPopulation();
  void RankPopulation();
  void mergesort(Path **v, int low, int high);
  void merge(Path **v, int low, int mid, int high);
  void print();
  void shortPrint();
  void shortPrint(int);

  void Try();
  Path* copyPath(Path);

  void Mutate();
  void SaveBest(int);
  void SaveBestCoord();
  void SaveAll();
  void SaveRegion();

};

#endif //




