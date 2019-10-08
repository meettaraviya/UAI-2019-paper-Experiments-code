#include "utils.h"

vector< vector<double> > getTransitionMatrix(MDP *m, Policy *pi){

  vector< vector<double> > T;
  T.resize(m->getS());
  for(unsigned int s = 0; s < m->getS(); s++){
    T[s].resize(m->getS());
    for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){
      T[s][sPrime] = m->getT(s, pi->getAction(s), sPrime);
    }
  }

  return T;
}

vector<double> getRewardVector(MDP *m, Policy *pi){

  vector<double> R;
  R.resize(m->getS());
  for(unsigned int s = 0; s < m->getS(); s++){
    R[s] = 0;
    for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){
      R[s] += m->getT(s, pi->getAction(s), sPrime) * m->getR(s, pi->getAction(s), sPrime);
    }
  }
  
  return R;
}

vector< vector<unsigned int> > getReachableStates(MDP *m, Policy *pi){

  vector< vector<double> > T = getTransitionMatrix(m, pi);

  vector< vector<double> > TPrime(m->getS());
  vector< vector<double> > TStarPrime(m->getS());

  for(unsigned int s1 = 0; s1< m->getS(); s1++){

    TPrime.push_back(vector<double>(0));
    TStarPrime.push_back(vector<double>(0));

    for(unsigned int s2= 0; s2< m->getS(); s2++){
      if(T[s1][s2] > 0){
       TPrime[s1].push_back(1.0);
       TStarPrime[s1].push_back(1.0);
     }
     else{
       TPrime[s1].push_back(0);
       TStarPrime[s1].push_back(0);
     }
   }
 }

 for(unsigned int s = 0; s < m->getS(); s++){

  vector< vector<double> > next = matrixMultiply(TStarPrime, TPrime, m->getS(), m->getS(), m->getS());

  for(unsigned int s1 = 0; s1 < m->getS(); s1++){
    for(unsigned int s2 = 0; s2 < m->getS(); s2++){
     if(next[s1][s2] > 0){
       TStarPrime[s1][s2] = 1.0;
     }
   }
 }
}

vector< vector<unsigned int> > reach(0);
for(unsigned int s = 0; s < m->getS(); s++){
    //    cout << "reach of " << s << ": ";
  reach.push_back(vector<unsigned int>(0));
  for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){
    if(TStarPrime[s][sPrime] > 0){
     reach[s].push_back(sPrime);
	//	cout << sPrime << " ";
   }
 }
    //    cout << "\n";
}

return reach;
}

vector<double> evaluate_backups(MDP *m, Policy *pi){

  vector<double> v;
  v.resize(m->getS(), 0);
  
  vector<double> vNew;
  vNew.resize(m->getS(), 0);
  
  bool converged = false;

  //  unsigned int sweep = 0;

  vector< vector<double> > T = getTransitionMatrix(m, pi);
  vector<double> R = getRewardVector(m, pi);

  while(!converged){

    //    cout << "sweep " << sweep++ << "\n";

    converged = true;

    vector<double> v1 = scalarVectorMultiply(m->getGamma(), v, m->getS());
    vector<double> v2 = matrixVectorMultiply(T, v1, m->getS(), m->getS());
    vNew = vectorAdd(R, v2, m->getS());

    if(vectorMaxDiff(vNew, v, m->getS()) > PRECISION){
      converged = false;
    }

    v = vectorCopy(vNew, m->getS());
    
  }

  return v;
}

vector<unsigned int> getZeroStates(MDP *m, Policy *pi){

  vector<unsigned int> zeroIndex(0);

  vector<bool> isZero(m->getS(), true);

  for(unsigned int s = 0; s < m->getS(); s++){
    double expectedReward = 0;
    for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){
      expectedReward += m->getT(s, pi->getAction(s), sPrime) * m->getR(s, pi->getAction(s), sPrime);
      if(m->getT(s, pi->getAction(s), sPrime) * m->getR(s, pi->getAction(s), sPrime) != 0){
	     //      if(m->getR(s, pi->getAction(s), sPrime) != 0){
	     //	isZero[s] = false;
      }
    }
    if(expectedReward != 0){
      isZero[s] = false;
    }
  }

  for(unsigned int trial = 0; trial < m->getS(); trial++){
    for(unsigned int s = 0; s < m->getS(); s++){
      if(isZero[s]){
       for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){
         if((!isZero[sPrime]) && (m->getT(s, pi->getAction(s), sPrime) > 0)){
           isZero[s] = false;
         }
       }
     }
   }
 }

  /*
  cout << "*****************\n";
  for(unsigned int s = 0; s < m->getS(); s++){
    if(isZero[s]){
      zeroIndex.push_back(s);
      cout << "zero: " << s << "\t";
    }
  }
  cout << "\n";
  cout << "*****************\n";
  */

 return zeroIndex;
}

vector<unsigned int> getAbsorbingStates(MDP *m, Policy *pi){

  vector<unsigned int> absorbingIndex(0);

  vector<bool> isAbsorbing(m->getS(), false);

  for(unsigned int s = 0; s < m->getS(); s++){
    if(m->getT(s, pi->getAction(s), s) == 1.0){
	// cout << s << "->" << s << " has prob. " << m->getT(s, pi->getAction(s), s) << "\n";
     isAbsorbing[s] = true;
     break;
   }
 }

  // cout << "*****************\n";
 for(unsigned int s = 0; s < m->getS(); s++){
  if(isAbsorbing[s]){
    absorbingIndex.push_back(s);
      //  cout << "zero: " << s << "\t";
  }
}
  //cout << "\n";
  //cout << "*****************\n";

return absorbingIndex;
}



// vector<double> evaluate_solve(MDP *m, Policy *pi){

//   vector< vector<double> > T = scalarMatrixMultiply(m->getGamma(), getTransitionMatrix(m, pi), m->getS(), m->getS());
//   vector<double> R = getRewardVector(m, pi);

//   /*
//   vector<unsigned int> zeroIndex = getZeroStates(m, pi);

//   for(int z = zeroIndex.size() - 1; z >= 0; z--){

//     for(unsigned int s = zeroIndex[z]; s < R.size() - 1; s++){
//       R[s] = R[s + 1];
//     }
//     R.pop_back();

//     for(unsigned int row = zeroIndex[z]; row < T.size() - 1; row++){
//       for(unsigned int col = 0; col < T.size(); col++){
// 	T[row][col] = T[row + 1][col];
//       }
//     }

//     for(unsigned int col = zeroIndex[z]; col < T.size() - 1; col++){
//       for(unsigned int row = 0; row < T.size(); row++){
// 	T[row][col] = T[row][col + 1];
//       }
//     }

//     for(unsigned int s = 0; s < T.size(); s++){
//       T[s].pop_back();
//     }
//     T.pop_back();
//   }
// */


//   const unsigned int numStates = T.size();

//   vector< vector<double> > I = identityMatrix(numStates);

//   vector< vector<double> > A1 = scalarMatrixMultiply(-1.0, T, numStates, numStates);
//   vector< vector<double> > A = matrixAdd(I, A1, numStates, numStates);

//   double* A_array;
//   A_array = new double[numStates * numStates];

//   unsigned int ctr = 0;
//   for(unsigned int s = 0; s < numStates; s++){
//     for(unsigned int sPrime = 0; sPrime < numStates; sPrime++){
//       A_array[ctr++] = A[s][sPrime];
//     }
//   }

//   double* B_array;
//   B_array = new double[numStates];

//   for(unsigned int s = 0; s < numStates; s++){
//     B_array[s] = R[s];
//   }


//   gsl_matrix_view m_solve = gsl_matrix_view_array(A_array, numStates, numStates);
//   gsl_vector_view b_solve = gsl_vector_view_array(B_array, numStates);

//   gsl_vector *x = gsl_vector_alloc(numStates);


//   int ss;

//   gsl_permutation *p = gsl_permutation_alloc (numStates);

//   gsl_linalg_LU_decomp (&m_solve.matrix, p, &ss);

//   gsl_linalg_LU_solve (&m_solve.matrix, p, &b_solve.vector, x);

//   vector<double> V(numStates);
//   for(unsigned int s = 0; s < numStates; s++){
//     V[s] = gsl_vector_get(x, s);
//   }

//   delete A_array;
//   delete B_array;
//   gsl_permutation_free (p);
//   gsl_vector_free (x);

//   return V;
// }



vector<double> evaluate_solve(MDP *m, Policy *pi){

  vector< vector<double> > T = scalarMatrixMultiply(m->getGamma(), getTransitionMatrix(m, pi), m->getS(), m->getS());
  vector<double> R = getRewardVector(m, pi);

  const unsigned long int numStates = m->getS();

  vector< vector<double> > I = identityMatrix(numStates);
  vector< vector<double> > A1 = scalarMatrixMultiply(-1.0, T, numStates, numStates);
  vector< vector<double> > A = matrixAdd(I, A1, numStates, numStates);

  vector< vector<double> > ATranspose;
  vector< vector<double> > APrime;
  vector<double> RPrime;

  if(m->getGamma() < 1.0){
    APrime = A;
    RPrime = R;    
  }
  else{
    vector<unsigned int> absorbingIndex = getAbsorbingStates(m, pi);
    
    /*  
	cout << "absorbing states: ";
	for(unsigned int z = 0; z < absorbingIndex.size(); z++){
	cout << absorbingIndex[z] << " ";
	}
	cout << "\n";
    */
    
    for(unsigned int z = 0; z < absorbingIndex.size(); z++){
      A.push_back(vector<double>(m->getS(), 0));
      A[A.size() - 1][absorbingIndex[z]] = 1.0;      
      R.push_back(0);
    }
    
    ATranspose = matrixTranspose(A, A.size(), A[0].size());
    APrime = matrixMultiply(ATranspose, A, ATranspose.size(), ATranspose[0].size(), A[0].size());
    RPrime = matrixVectorMultiply(ATranspose, R, ATranspose.size(), ATranspose[0].size());
  }
  
  double* A_array;
  A_array = new double[numStates * numStates];
  
  unsigned int ctr = 0;
  for(unsigned int s = 0; s < numStates; s++){
    for(unsigned int sPrime = 0; sPrime < numStates; sPrime++){
      A_array[ctr++] = APrime[s][sPrime];
    }
  }
  
  double* B_array;
  B_array = new double[numStates];
  for(unsigned int s = 0; s < numStates; s++){
    B_array[s] = RPrime[s];
  }
  
  gsl_matrix_view m_solve = gsl_matrix_view_array(A_array, numStates, numStates);
  gsl_vector_view b_solve = gsl_vector_view_array(B_array, numStates);

  gsl_vector *x = gsl_vector_alloc(numStates);
  
  int ss;
  

  gsl_permutation *p = gsl_permutation_alloc (numStates);
  gsl_linalg_LU_decomp (&m_solve.matrix, p, &ss);
  gsl_linalg_LU_solve (&m_solve.matrix, p, &b_solve.vector, x);
  vector<double> V(numStates);
  for(unsigned int s = 0; s < numStates; s++){
    V[s] = gsl_vector_get(x, s);
  }
  
  delete A_array;
  delete B_array;
  gsl_permutation_free (p);
  gsl_vector_free (x);
  
  return V;
}



double policyValue(MDP *m, Policy *pi){

  vector<double> val = evaluate_solve(m, pi);
  double sum = 0;
  for(unsigned int s = 0; s < m->getS(); s++){
    sum += val[s];
  }
  return sum;
}

bool lexicoPrecedes(Policy *pi1, Policy *pi2, const unsigned int &numStates){

  for(unsigned int s = 0; s < numStates; s++){
    if(pi1->getAction(s) < pi2->getAction(s)){
      return true;
    }
    else if(pi1->getAction(s) > pi2->getAction(s)){
      return false;
    }
  }
  return false;
}

Policy* greedyPolicy(MDP *m, const vector<double> &val){

  Policy *pi = new Policy(m->getS(), m->getA(), 0);

  vector< vector<double> > Q;

  Q.resize(m->getS());

  for(unsigned int s = 0; s < m->getS(); s++){

    Q[s].resize(m->getA());
    for(unsigned int a = 0; a < m->getA(); a++){

      Q[s][a] = 0;
      for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){

       Q[s][a] += m->getT(s, a, sPrime) * (m->getR(s, a, sPrime) + m->getGamma() * val[sPrime]);

     }
   }
 }

 for(unsigned int s = 0; s < m->getS(); s++){
  unsigned int maxIndex = 0;
  for(unsigned int a = 1; a < m->getA(); a++){
    if(Q[s][a] > Q[s][maxIndex]){
     maxIndex = a;
   }
 }
 pi->setAction(s, maxIndex);
}

return pi;

}

// randomized policy improvement operator of Mansour and Singh
Policy* msGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy){

  Policy *piGreedy = greedyPolicy(m, val);
  Policy *pi = new Policy(currentPolicy);
  

  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  
  bool AtLeastOneStateImproved = false;
  unsigned int ctr = 0;

  do{
    ctr = 0;
    for(unsigned int s = 0; s < m->getS(); s++){
      if(pi->getAction(s) != piGreedy->getAction(s)){
       ctr++;
       double u = gsl_rng_uniform (r);
       if(u > 0.5){
         pi->setAction(s, piGreedy->getAction(s));
         AtLeastOneStateImproved = true;
       }
     }
   }
 } while(!AtLeastOneStateImproved && (ctr > 0));

 delete piGreedy;
 gsl_rng_free (r);  

 return pi;
}

Policy* simpleGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy){

  Policy *piGreedy = greedyPolicy(m, val);
  
  Policy *pi = new Policy(currentPolicy);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(pi->getAction(s) != piGreedy->getAction(s)){
      pi->setAction(s, piGreedy->getAction(s));
      break;
    }
  }
  delete piGreedy;

  return pi;
}

Policy* batchGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy, const unsigned int &batchSize){

  Policy *piGreedy = greedyPolicy(m, val);
  
  Policy *pi = new Policy(currentPolicy);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(pi->getAction(s) != piGreedy->getAction(s)){

      int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
       pi->setAction(s1, piGreedy->getAction(s1));
     }
     break;
   }
 }
 delete piGreedy;

 return pi;
}


bool isEqualPolicies(Policy *pi1, Policy *pi2, const unsigned int &S){

  for(unsigned int s= 0; s < S; s++){
    if(pi1->getAction(s) != pi2->getAction(s)){
      return false;
    }
  }

  return true;
}

// bool qCompare (unsigned int i,unsigned int j, const unsigned int &s, const vector<unsigned int> &Qs) { return (Qs[i]<Qs[j]); }

vector< vector<unsigned int> > improvingActions(MDP *m, Policy* pi, const vector<double> &val){
  

  vector< vector<double> > Q;

  vector< vector<unsigned int> > I;

  Q.resize(m->getS());
  I.resize(m->getS());

  for(unsigned int s = 0; s < m->getS(); s++){

    Q[s].resize(m->getA());
    for(unsigned int a = 0; a < m->getA(); a++){

      Q[s][a] = 0;
      for(unsigned int sPrime = 0; sPrime < m->getS(); sPrime++){

       Q[s][a] += m->getT(s, a, sPrime) * (m->getR(s, a, sPrime) + m->getGamma() * val[sPrime]);

     }
   }
 }


  for(unsigned int s = 0; s < m->getS(); s++){
    // if(Q[s][pi->getAction(s)] <= val[s]){
    //     I[s].push_back(pi->getAction(s));
    // }
    for(unsigned int a = 0; a < m->getA(); a++){
      if(Q[s][a] > val[s] or a == pi->getAction(s)){
        I[s].push_back(a);
      }
    }
  }
  for(unsigned int s=0; s<m->getS(); s++){
    sort(I[s].begin(), I[s].end(), [Q, s, pi](unsigned int i, unsigned int j){return (Q[s][i]<Q[s][j]) or i == pi->getAction(s);});
    // using namespace std::placeholders;
    // sort(I[s].begin(), I[s].end(), bind(qCompare, _1, _2, Q[s]));
    assert(I[s][0] == pi->getAction(s));
  }
 return I;
}
