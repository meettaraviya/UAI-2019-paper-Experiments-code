# greedyStateGreedyActionPI
# randomStateGreedyActionPI
# randomStateRandomActionPI
# greedyStateRandomActionPI
# batchStateGreedyActionPI
# batchStateRandomActionPI
# randomPolicyPI

rm -rf resultsk
mkdir resultsk
S=60
for logk in {1..10}; do 
	k=$((2**logk)); 
	for algoseed in {1..500}; do
		echo $k $algoseed
		mdpseed=$((500+algoseed))
		polseed=$((1000+algoseed))

		rm -f mdptmpfile.txt
		./data/generateMDP.py $S $k $mdpseed > mdptmpfile.txt

		for algo in greedyStateGreedyActionPI randomStateGreedyActionPI randomStateRandomActionPI greedyStateRandomActionPI randomPolicyPI; do
			./planner --mdpFile ./mdptmpfile.txt --initPolicyType random --policyRandomSeed $polseed --algorithmRandomSeed $algoseed --algorithm $algo --batchSize 5 | grep iterations >> resultsk/$algo-$S-$k.txt
		done
	done
done

rm -f res.txt
for file in $(ls resultsk); do
	printf "$file\n"
	printf "$file " >> res.txt
	cat resultsk/$file | cut -f 2 | python avg.py >> res.txt
done