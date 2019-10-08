#include "algorithms.h"

vector<double> value_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter){

  vector<double> v;
  v.resize(m->getS(), 0);
  
  vector<double> vNew;
  vNew.resize(m->getS(), 0);
  
  bool converged = false;

  numIter = 0;


  while(!converged){

    converged = true;

    Policy *pi = greedyPolicy(m, v);

    vector< vector<double> > T = getTransitionMatrix(m, pi);
    vector<double> R = getRewardVector(m, pi);

    numIter++;

    delete pi;

    vector<double> v1 = scalarVectorMultiply(m->getGamma(), v, m->getS());
    vector<double> v2 = matrixVectorMultiply(T, v1, m->getS(), m->getS());
    vNew = vectorAdd(R, v2, m->getS());

    if(vectorMaxDiff(vNew, v, m->getS()) > PRECISION){
      converged = false;
    }

    v = vectorCopy(vNew, m->getS());

  }

  piOpt = greedyPolicy(m, v);

  return v;
}

vector<double> howards_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter){

  vector<double> v(m->getS(), 0);

  Policy *pi1 = new Policy(pi);
  Policy *pi2 = NULL;

  bool converged = false;
  numIter = 0;

  while(!converged){

    converged = true;

    v = evaluate_solve(m, pi1);
    //    v = evaluate_backups(m, pi1);
    double x = sumOfElements(v, m->getS());

    cout << numIter++ << ", " << x << "\n";

    //v = evaluate_backups(m, pi1);
    pi2 = greedyPolicy(m, v);

    if(!isEqualPolicies(pi1, pi2, m->getS())){

      converged = false;
      delete pi1;
      pi1 = pi2;
      pi2 = NULL;
    }
    
  }

  piOpt = pi1;

  return v;
}

vector<double> mansour_singh_random_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int randomSeed){

  vector<double> v(m->getS(), 0);

  Policy *pi1 = new Policy(pi);
  Policy *pi2 = NULL;

  gsl_rng *ran = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(ran, randomSeed);
  
  bool converged = false;
  numIter = 0;

  while(!converged){

    converged = true;

    v = evaluate_solve(m, pi1);
    //    v = evaluate_backups(m, pi1);
    double x = sumOfElements(v, m->getS());

    cout << numIter++ << ", " << x << "\n";

    //v = evaluate_backups(m, pi1);
    // pi2 = msGreedyPolicy(m, v, pi1);


    //-------------------------------------------- BEGIN compute pi2 = msGreedyPolicy(m, v, pi1);

    Policy *piGreedy = greedyPolicy(m, v);
    Policy *piNext = new Policy(pi1);
    
    bool AtLeastOneStateImproved = false;
    unsigned int ctr = 0;
    
    do{
      ctr = 0;
      for(unsigned int s = 0; s < m->getS(); s++){
       if(piNext->getAction(s) != piGreedy->getAction(s)){
         ctr++;
         double u = gsl_rng_uniform(ran);
         if(u > 0.5){
           piNext->setAction(s, piGreedy->getAction(s));
           AtLeastOneStateImproved = true;
         }
       }
     }
   } while(!AtLeastOneStateImproved && (ctr > 0));

   delete piGreedy;
   pi2 = piNext;

    //-------------------------------------------- END compute pi2 = msGreedyPolicy(m, v, pi1);

   if(!isEqualPolicies(pi1, pi2, m->getS())){

    converged = false;
    delete pi1;
    pi1 = pi2;
    pi2 = NULL;
  }

}

piOpt = pi1;
gsl_rng_free(ran);

return v;
}



vector<double> simple_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter){

  vector<double> v(m->getS(), 0);

  Policy *pi1 = new Policy(pi);
  Policy *pi2 = NULL;

  bool converged = false;
  numIter = 0;

  while(!converged){

    converged = true;

    cout << numIter++ << "\n";
    v = evaluate_solve(m, pi1);

    pi2 = simpleGreedyPolicy(m, v, pi1);

    if(!isEqualPolicies(pi1, pi2, m->getS())){

      converged = false;
      delete pi1;
      pi1 = pi2;
      pi2 = NULL;
    }
    
  }

  piOpt = pi1;

  return v;
}


vector<double> batch_switching_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int &batchSize){

  vector<double> v(m->getS(), 0);

  Policy *pi1 = new Policy(pi);
  Policy *pi2 = NULL;

  bool converged = false;
  numIter = 0;

  while(!converged){

    converged = true;

    cout << numIter++ << "\n";
    v = evaluate_solve(m, pi1);

    //    pi2 = simpleGreedyPolicy(m, v, pi1);
    pi2 = batchGreedyPolicy(m, v, pi1, batchSize);

    if(!isEqualPolicies(pi1, pi2, m->getS())){

      converged = false;
      delete pi1;
      pi1 = pi2;
      pi2 = NULL;
    }
  }

  piOpt = pi1;

  return v;
}

Policy* greedy_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      piNext->setAction(s, I[s].back());
    }
  }
  return piNext;
}

Policy* random_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    // if(I[s].size()>1 and gsl_rng_uniform(ran)>0.5){
    if(I[s].size()>1 and gsl_rng_uniform_int(ran, 2)==1){
      piNext->setAction(s, I[s].back());
    }
  }
  return piNext;
}

Policy* random_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1 and gsl_rng_uniform_int(ran, 2)==1){
    // if(I[s].size()>1 and gsl_rng_uniform(ran)>0.5){
      int ai;
      if(I[s].size()>2)
        ai = 1 + gsl_rng_uniform_int(ran, I[s].size()-1);
      else
        ai = 1;
      piNext->setAction(s, I[s][ai]);
    }
  }
  return piNext;
}

Policy* greedy_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>2){
      int ai = 1 + gsl_rng_uniform_int(ran, I[s].size()-1);
      piNext->setAction(s, I[s][ai]);
    }
    else if(I[s].size()==2){
      piNext->setAction(s, I[s].back());
    }
  }
  return piNext;
}

Policy* batch_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      unsigned int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
        if(I[s1].size()>1){
          piNext->setAction(s1, I[s1].back());
        }
      }
      break;
    }
  }
  return piNext;
}

Policy* batch_random_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      unsigned int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
        if(I[s1].size()>1 and gsl_rng_uniform_int(ran, 2) == 1){
          piNext->setAction(s1, I[s1].back());
        }
      }
      break;
    }
  }
  return piNext;
}

Policy* batch_random_policy_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      unsigned int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
        if(I[s1].size()>1){
          int ai = gsl_rng_uniform_int(ran, I[s1].size());
          piNext->setAction(s1, I[s1][ai]);
        }
      }
      break;
    }
  }
  return piNext;
}

Policy* batch_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      unsigned int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
        if(I[s1].size()>2){
          int ai = 1 + gsl_rng_uniform_int(ran, I[s1].size()-1);
          piNext->setAction(s1, I[s1][ai]);
        }
        else if(I[s1].size()==2){
          piNext->setAction(s1, I[s1].back());
        }
      }
      break;
    }
  }
  return piNext;
}

Policy* batch_random_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      unsigned int batch = s / batchSize;
      for(unsigned int s1 = batch * batchSize; s1 < (batch + 1) * batchSize && s1 < m->getS(); s1++){
        if(I[s1].size()>1 and gsl_rng_uniform_int(ran, 2)==1){
          if(I[s1].size()>2){
            int ai = 1 + gsl_rng_uniform_int(ran, I[s1].size()-1);
            piNext->setAction(s1, I[s1][ai]);
          }
          else if(I[s1].size()==2){
            piNext->setAction(s1, I[s1].back());
          }
        }
      }
      break;
    }
  }
  return piNext;
}

Policy* random_policy_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran){
  Policy* piNext = new Policy(pi);
  for(unsigned int s = 0; s < m->getS(); s++){
    if(I[s].size()>1){
      int ai = gsl_rng_uniform_int(ran, I[s].size());
      piNext->setAction(s, I[s][ai]);
    }
  }
  return piNext;
}


vector<double> generalized_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int &batchSize, const int randomSeed, Policy* (*selection)(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran)){

  vector<double> v(m->getS(), 0);

  Policy *pi1 = new Policy(pi);
  Policy *pi2 = NULL;

  gsl_rng *ran = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(ran, randomSeed);

  bool converged = false;
  vector< vector<unsigned int> > I;
  numIter = 0;

  pi1->display();

  while(!converged){

    converged = true;

    v = evaluate_solve(m, pi1);
    I = improvingActions(m, pi1, v);
    unsigned int numImprovingActions = 0;
    for(unsigned int s = 0; s < m->getS(); s++){
      numImprovingActions += I[s].size();
    }
    numIter++;


    if(numImprovingActions != m -> getS()){

      pi2 = selection(m, pi1, I, batchSize, ran);
      for(unsigned int s=0; s < m->getS(); s++){
        cout << (I[s].size()==2 ? 'X' : ' ') << ' ';
        // assert(I[s].size()>0 and I[s].size()<=2);
      }
      cout << '\n';
      for(unsigned int s=0; s < m->getS(); s++){
        cout << ((pi2 -> getAction(s)!=pi1 -> getAction(s)) ? 'O' : ' ') << ' ';
      }
      cout << '\n';
      pi2 -> display();
      converged = false;
      delete pi1;
      pi1 = pi2;
      pi2 = NULL;
    }
  }

  piOpt = pi1;

  return v;
}


