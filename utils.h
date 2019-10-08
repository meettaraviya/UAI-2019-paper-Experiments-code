#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <algorithm>
#include <assert.h>
#include <iomanip>

#include <gsl/gsl_linalg.h>

#include "mdp.h"
#include "policy.h"
#include "headers.h"
#include "matrix.h"


vector< vector<double> > getTransitionMatrix(MDP *m, Policy *pi);
vector<double> getRewardVector(MDP *m, Policy *pi);

vector< vector<unsigned int> > getReachableStates(MDP *m, Policy *pi);

vector<double> evaluate_backups(MDP *m, Policy *pi);

vector<unsigned int> getZeroStates(MDP *m, Policy *pi);

vector<unsigned int> getAbsorbingStates(MDP *m, Policy *pi);

vector<double> evaluate_solve(MDP *m, Policy *pi);

double policyValue(MDP *m, Policy *pi);

Policy* greedyPolicy(MDP *m, const vector<double> &val);//randomise for tie breaking later.
Policy* msGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy);

Policy* simpleGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy);
Policy* batchGreedyPolicy(MDP *m, const vector<double> &val, Policy *currentPolicy, const unsigned int &batchSize);

bool lexicoPrecedes(Policy *pi1, Policy *pi2, const unsigned int &numStates);

bool isEqualPolicies(Policy *pi1, Policy *pi2, const unsigned int &S);

vector< vector<unsigned int> > improvingActions(MDP *m, Policy* pi, const vector<double> &val);


#endif
