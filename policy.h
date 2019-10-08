#ifndef POLICY_H
#define POLICY_H

#include <vector>
#include <fstream>
#include <iostream>

#include "gsl/gsl_rng.h"

using namespace std;

class Policy{

private:
  
  unsigned int S;
  unsigned int A;
  vector< unsigned int > action;

public:

  Policy(const string &fileName);
  Policy(const unsigned int &S, const unsigned int &A, const int &randomSeed = 0);
  Policy(Policy *pi);

  ~Policy();

  void setAction(const unsigned int &s, const unsigned int &a);
  unsigned int getAction(const unsigned int &s);

  void display();

};

#endif

