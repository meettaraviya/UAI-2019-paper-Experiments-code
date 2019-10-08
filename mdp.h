#ifndef MDP_H
#define MDP_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class MDP{

private:
  
  unsigned int S;
  unsigned int A;
  vector< vector< vector<double> > > R;
  vector< vector< vector<double> > > T;
  double gamma;

public:

  MDP(const string &fileName);
  ~MDP();

  unsigned int getS();
  unsigned int getA();
  double getR(const unsigned int &s, const unsigned int &a, const unsigned int &sPrime);
  double getT(const unsigned int &s, const unsigned int &a, const unsigned int &sPrime);
  double getGamma();

  void display();

};

#endif

