#! /bin/bash

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType random --algorithmRandomSeed $i --algorithm mansoursinghrandomPI | grep iterations >> ./results/mansoursinghRPI-F-5-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType random --algorithmRandomSeed $i --algorithm mansoursinghrandomPI | grep iterations >> ./results/mansoursinghRPI-F-8-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType random --algorithmRandomSeed $i --algorithm mansoursinghrandomPI | grep iterations >> ./results/mansoursinghRPI-F-10-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType random --algorithmRandomSeed $i --algorithm mansoursinghrandomPI | grep iterations >> ./results/mansoursinghRPI-F-12-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType random --algorithmRandomSeed $i --algorithm mansoursinghrandomPI | grep iterations >> ./results/mansoursinghRPI-F-15-RandomInit.txt; done


#------------------

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratemansoursinghPI | grep iterations >> ./results/IGImsPI-F-5-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratemansoursinghPI | grep iterations >> ./results/IGImsPI-F-8-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratemansoursinghPI | grep iterations >> ./results/IGImsPI-F-10-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratemansoursinghPI | grep iterations >> ./results/IGImsPI-F-12-RandomInit.txt; done

for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratemansoursinghPI | grep iterations >> ./results/IGImsPI-F-15-RandomInit.txt; done

