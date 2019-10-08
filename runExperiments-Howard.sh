#! /bin/bash

# for i in `seq 1 1`; do echo $i; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType file --initPolicyFile ./data/policy-F-5.txt --algorithm howardPI | grep iterations >> ./results/howardPI-F-5-SpecialInit.txt; done

# for i in `seq 1 1`; do echo $i; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType file --initPolicyFile ./data/policy-F-8.txt --algorithm howardPI | grep iterations >> ./results/howardPI-F-8-SpecialInit.txt; done

# for i in `seq 1 1`; do echo $i; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType file --initPolicyFile ./data/policy-F-10.txt --algorithm howardPI | grep iterations >> ./results/howardPI-F-10-SpecialInit.txt; done

# for i in `seq 1 1`; do echo $i; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType file --initPolicyFile ./data/policy-F-12.txt --algorithm howardPI | grep iterations >> ./results/howardPI-F-12-SpecialInit.txt; done

# for i in `seq 1 1`; do echo $i; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType file --initPolicyFile ./data/policy-F-15.txt --algorithm howardPI | grep iterations >> ./results/howardPI-F-15-SpecialInit.txt; done

# #-----------------

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType random --algorithm howardPI | grep iterations >> ./results/howardPI-F-5-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType random --algorithm howardPI | grep iterations >> ./results/howardPI-F-8-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType random --algorithm howardPI | grep iterations >> ./results/howardPI-F-10-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType random --algorithm howardPI | grep iterations >> ./results/howardPI-F-12-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType random --algorithm howardPI | grep iterations >> ./results/howardPI-F-15-RandomInit.txt; done

# #------------------

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-5-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-8-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-10-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-12-RandomInit.txt; done

# for i in `seq 1 1000`; do echo $i; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType random --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-15-RandomInit.txt; done

#------------------

for i in `seq 1 1000`; do echo "F-5, $i"; ./planner --mdpFile ./data/mdp-F-5.txt --initPolicyType file --initPolicyFile ./data/policy-F-5.txt --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-5-SpecialInit.txt; done

for i in `seq 1 1000`; do echo "F-8, $i"; ./planner --mdpFile ./data/mdp-F-8.txt --initPolicyType file --initPolicyFile ./data/policy-F-8.txt --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-8-SpecialInit.txt; done

for i in `seq 1 1000`; do echo "F-10, $i"; ./planner --mdpFile ./data/mdp-F-10.txt --initPolicyType file --initPolicyFile ./data/policy-F-10.txt --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-10-SpecialInit.txt; done

for i in `seq 1 1000`; do echo "F-12, $i"; ./planner --mdpFile ./data/mdp-F-12.txt --initPolicyType file --initPolicyFile ./data/policy-F-12.txt --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-12-SpecialInit.txt; done

for i in `seq 1 1000`; do echo "F-15, $i"; ./planner --mdpFile ./data/mdp-F-15.txt --initPolicyType file --initPolicyFile ./data/policy-F-15.txt --algorithmRandomSeed $i --algorithm interleavedguessanditeratePI | grep iterations >> ./results/IGIhowardPI-F-15-SpecialInit.txt; done

