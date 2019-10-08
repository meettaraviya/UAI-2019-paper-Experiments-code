#include <stdlib.h>
#include <sstream>

#include "mdp.h"
#include "policy.h"
#include "utils.h"
#include "algorithms.h"

void options(){

  cout << "Usage:\n";

  cout << "planner\n";

  cout << "\t[--mdpFile mdpFileName]\n";

  cout << "\t[--initPolicyType file | random]\n";
  cout << "\t[--initPolicyFile initPolicyFileName]\n";
  cout << "\t[--policyRandomSeed policyRandomSeed]\n";

  cout << "\t[--algorithm valueiteration | howardPI | mansoursinghrandomPI | simplePI | BSPI]\n";
  cout << "\t[--algorithmRandomSeed algorithmRandomSeed]\n";

  cout << "\t[--batchSize batchSize]\n";

  cout << "\t[--help]\n";
}


/*
  Read command line arguments, and set the ones that are passed (the others remain default.)
*/

bool setRunParameters(int argc, char *argv[], string &mdpFileName, string &initPolicyType, string &initPolicyFileName, int &policyRandomSeed, string &algorithm, int &algorithmRandomSeed, unsigned int &batchSize){

  int ctr = 1;

  while(ctr < argc){

    // cout << string(argv[ctr]) << "\n";

    if(string(argv[ctr]) == "--help"){
      return false;//This should print options and exit.
    }
    else if(string(argv[ctr]) == "--mdpFile"){
      if(ctr == (argc - 1)){
        return false;
      }
      mdpFileName = string(argv[ctr + 1]);
      ctr++;
    }
    else if(string(argv[ctr]) == "--initPolicyType"){
      if(ctr == (argc - 1)){
        return false;
      }
      initPolicyType = string(argv[ctr + 1]);
      ctr++;
    }
    else if(string(argv[ctr]) == "--initPolicyFile"){
      if(ctr == (argc - 1)){
        return false;
      }
      initPolicyFileName = string(argv[ctr + 1]);
      ctr++;
    }
    else if(string(argv[ctr]) == "--policyRandomSeed"){
      if(ctr == (argc - 1)){
        return false;
      }
      policyRandomSeed = atoi(string(argv[ctr + 1]).c_str());
      ctr++;
    }
    else if(string(argv[ctr]) == "--algorithm"){
      if(ctr == (argc - 1)){
        return false;
      }
      algorithm = string(argv[ctr + 1]);
      ctr++;
    }
    else if(string(argv[ctr]) == "--algorithmRandomSeed"){
      if(ctr == (argc - 1)){
        return false;
      }
      algorithmRandomSeed = atoi(string(argv[ctr + 1]).c_str());
      ctr++;
    }
    else if(string(argv[ctr]) == "--batchSize"){
      if(ctr == (argc - 1)){
        return false;
      }
      batchSize = atoi(string(argv[ctr + 1]).c_str());
      ctr++;
    }
    else{
      return false;
    }

    ctr++;
  }

  return true;
}



int main(int argc, char *argv[]){

  // Run Parameter defaults.
  string mdpFileName = "";
  string initPolicyType = "random";
  string initPolicyFileName = "";
  int policyRandomSeed = 1;
  string algorithm = "howard";
  int algorithmRandomSeed = 1;
  unsigned int batchSize = 1;

  //Set from command line, if any.

  if(!(setRunParameters(argc, argv, mdpFileName, initPolicyType, initPolicyFileName, policyRandomSeed, algorithm, algorithmRandomSeed, batchSize))){

    //Error parsing command line.
    options();
    return 1;
  }


  cout << "MDP File: " << mdpFileName << "\n";
  cout << "Init policy type: " << initPolicyType << "\n";
  cout << "Init policy file name: " << initPolicyFileName << "\n";
  cout << "Policy random seed: " << policyRandomSeed << "\n";
  cout << "Algorithm: " << algorithm << "\n";
  cout << "Algorithm random seed: " << algorithmRandomSeed << "\n";
  cout << "Batch Size: " << batchSize << "\n";




  //Initialise MDP.
  MDP *m = new MDP(mdpFileName.c_str());
  //  M1->display();

  //Initialise policy.
  Policy *pi = NULL;
  if(initPolicyType == "file"){
    pi = new Policy(initPolicyFileName.c_str());
  }
  else if(initPolicyType == "random"){
    pi = new Policy(m->getS(), m->getA(), policyRandomSeed);
  }
  else{
    options();
    return 1;
  }

  //Initialise algorithm.
  Policy *piOpt = NULL;
  unsigned int numIter = 0;
  vector<double> vStar;

  if(algorithm == "valueiteration"){
    vStar = value_iteration(m, pi, piOpt, numIter);
  }
  else if(algorithm == "howardPI"){
    vStar = howards_policy_iteration(m, pi, piOpt, numIter);
  }
  else if(algorithm == "simplePI"){
    vStar = simple_policy_iteration(m, pi, piOpt, numIter);
  }
  else if(algorithm == "mansoursinghrandomPI"){
    vStar = mansour_singh_random_policy_iteration(m, pi, piOpt, numIter, algorithmRandomSeed);
  }
  else if(algorithm == "BSPI"){
    vStar = batch_switching_policy_iteration(m, pi, piOpt, numIter, batchSize);
  }
  else if(algorithm == "greedyStateGreedyActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, greedy_state_greedy_action_selection);
  }
  else if(algorithm == "randomStateGreedyActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, random_state_greedy_action_selection);
  }
  else if(algorithm == "randomStateRandomActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, random_state_random_action_selection);
  }
  else if(algorithm == "greedyStateRandomActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, greedy_state_random_action_selection);
  }
  else if(algorithm == "batchStateGreedyActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, batch_state_greedy_action_selection);
  }
  else if(algorithm == "batchStateRandomActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, batch_state_random_action_selection);
  }
  else if(algorithm == "batchRandomStateGreedyActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, batch_random_state_greedy_action_selection);
  }
  else if(algorithm == "batchRandomStateRandomActionPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, batch_random_state_random_action_selection);
  }
  else if(algorithm == "batchRandomPolicyPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, batch_random_policy_selection);
  }
  else if(algorithm == "randomPolicyPI"){
    vStar = generalized_policy_iteration(m, pi, piOpt, numIter, batchSize, algorithmRandomSeed, random_policy_selection);
  }
  else if(algorithm == "policyEvaluation"){
    for(unsigned int s = 0; s < m->getS(); s++){
      pi -> setAction(s, 0);
    }
    string actionString[] = {
      "\\textcolor{red}{0}",
      "\\textcolor{blue}{1}",
      "\\textcolor{green}{2}",
    };
    printf("$\\pi$ & ");
    for(unsigned int s = 0; s < m->getS(); s++){
      printf("$V^\\pi(s_%u)$ ", s);
      if(s+1 < m->getS()){
        printf("& ");
      }
      else{
        printf("& $T^\\pi$ \\\\ \\hline\n");
      }
    }
    unsigned int leadingZeros = 0;
    while(leadingZeros != m->getS()){

      vector<double> val = evaluate_solve(m, pi);
      vector< vector<unsigned int> > I = improvingActions(m, pi, val);

      // printf("$\\pi$ && ");
      for(unsigned int s = 0; s < m->getS(); s++){
        printf("%s", actionString[pi->getAction(s)].data());
      }
      printf(" & ");
      for(unsigned int s = 0; s < m->getS(); s++){
        printf("%.2f ", val[s]);
          printf("& ");
        // }
        // else{
        //   printf("\\\\ \\hline\n");
        // }
      }
      printf("$\\{");
      bool start = true;
      for(unsigned int s = 0; s < m->getS(); s++){
        for(unsigned int ai=1; ai<I[s].size(); ai++){
          if(!start){
            printf(", ");
          }
          printf("(s_%u, %s)", s, actionString[I[s][ai]].data());
          start = false;
        }
      }
      printf("\\}$ \\\\ \\hline\n");

      // cout << "-------------------" << endl;
      // for(unsigned int s = 0; s < m->getS(); s++){
      //   cout << s << " : " << pi->getAction(s) << " : " << I[s].size() << " : " << val[s] << " : ";
      //   for(unsigned int a: I[s]){
      //     cout << a << ' ';
      //   }
      //   cout << endl;
      // }
      // cout << endl;

      unsigned int s = m->getS()-1;
      while(s < m->getS() and pi->getAction(s) == m->getA()-1){
        pi -> setAction(s, 0);
        s--;
      }
      if(s < m->getS()){
        pi -> setAction(s, pi -> getAction(s) + 1);
      }
      leadingZeros = 0;
      while(leadingZeros < m->getS() and pi->getAction(leadingZeros) == 0){
        leadingZeros++;
      }
    }
  }
  else{
    // cout << algorithm << endl;
    options();
    return 1;
  }
  
  // Write output to console.
  cout << "Optimal values and actions:\n";
  for(unsigned int s = 0; s < m->getS(); s++){
    cout << vStar[s] << "\t" << piOpt->getAction(s) << "\n";
  }
  cout << "iterations" << "\t" << numIter << "\n";

  // Free up heap.
  delete m;
  delete pi;
  delete piOpt;

  return 0;
}

