#include "mdp.h"

MDP::MDP(const string &fileName){

  ifstream file;
  file.open(fileName.c_str());

  file >> this->S;
  file >> this->A;

  this->R.resize(S);
  for(unsigned int s = 0; s < S; s++){
    
    this->R[s].resize(A);
    for(unsigned int a = 0; a < A; a++){
      
      this->R[s][a].resize(S);
      for(unsigned int sPrime = 0; sPrime < S; sPrime++){
	
	file >> R[s][a][sPrime];

      }
    }
  }

  this->T.resize(S);
  for(unsigned int s = 0; s < S; s++){
    
    this->T[s].resize(A);
    for(unsigned int a = 0; a < A; a++){
      
      this->T[s][a].resize(S);
      for(unsigned int sPrime = 0; sPrime < S; sPrime++){
	
	file >> T[s][a][sPrime];

      }
    }
  }

  file >> this->gamma;

  file.close();

}

MDP::~MDP(){
}

unsigned int MDP::getS(){
  return S;
}

unsigned int MDP::getA(){
  return A;
}

double MDP::getR(const unsigned int &s, const unsigned int &a, const unsigned int &sPrime){
  return R[s][a][sPrime];
}

double MDP::getT(const unsigned int &s, const unsigned int &a, const unsigned int &sPrime){

  return T[s][a][sPrime];
}

double MDP::getGamma(){
  return gamma;
}

void MDP::display(){

  cout << "S = " << S << "\n";
  cout << "A = " << A << "\n";
 
  for(unsigned int s = 0; s < S; s++){
    for(unsigned int a = 0; a < A; a++){
      for(unsigned int sPrime = 0; sPrime < S; sPrime++){

	cout << "R(" << s << ", " << a << ", " << sPrime << ") = " << R[s][a][sPrime] << "\t";
	cout << "T(" << s << ", " << a << ", " << sPrime << ") = " << T[s][a][sPrime] << "\n";

      }
    }
  }

  cout << "gamma = " << gamma << "\n";

}

