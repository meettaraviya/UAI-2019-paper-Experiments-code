#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "utils.h"

vector<double> value_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter);
vector<double> howards_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter);
vector<double> mansour_singh_random_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int randomSeed);
vector<double> simple_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter);
vector<double> batch_switching_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int &batchSize);

vector<double> generalized_policy_iteration(MDP *m, Policy *pi, Policy* &piOpt, unsigned int &numIter, const int &batchSize, const int randomSeed, Policy* (*selection)(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran));

Policy* greedy_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* random_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* random_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* greedy_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* batch_random_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* batch_state_greedy_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* batch_random_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* batch_state_random_action_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* random_policy_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);
Policy* batch_random_policy_selection(MDP *m, Policy* pi, const vector< vector<unsigned int> > &I, const int &batchSize, gsl_rng* ran);

#endif

