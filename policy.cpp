#include "policy.h"

Policy::Policy(const string &fileName){

  ifstream file;
  file.open(fileName.c_str());

  file >> this->S;
  file >> this->A;

  this->action.resize(S);
  for(unsigned int s = 0; s < S; s++){
    
	file >> this->action[s];
	
  }

  file.close();
}

Policy::Policy(const unsigned int &S, const unsigned int &A, const int &randomSeed){

  this->S = S;
  this->A = A;

  gsl_rng *ran = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(ran, randomSeed);
                    
  action.resize(S);
  for(unsigned int s = 0; s < S; s++){
    action[s] = gsl_rng_uniform_int(ran, A);
  }



  delete ran;
}

Policy::Policy(Policy *pi){

  this->S = pi->S;
  this->A = pi->A;

  this->action.resize(this->S);

  for(unsigned int s = 0; s < this->S; s++){
    this->action[s] = pi->getAction(s);
  }

}

Policy::~Policy(){
}

void Policy::setAction(const unsigned int &s, const unsigned int &a){
  
  this->action[s] = a;
}

unsigned int Policy::getAction(const unsigned int &s){

  return action[s];
}


void Policy::display(){

  // cout << "S = " << S << "\n";
  // cout << "A = " << A << "\n";
 
  for(unsigned int s = 0; s < S; s++){

  cout << action[s] << " ";
	// cout << "action(" << s << ") = " << action[s] << "; ";
  }
  cout << "\n";

}

