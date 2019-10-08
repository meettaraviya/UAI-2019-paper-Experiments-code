S=60
for logk in {1..10}; do 
	k=$((2**logk)); 
	for algoseed in {1..500}; do
		echo $k $algoseed
		mdpseed=$((500+algoseed))
		polseed=$((1000+algoseed))

		for algo in greedyStateGreedyActionPI randomStateGreedyActionPI randomStateRandomActionPI greedyStateRandomActionPI randomPolicyPI; do
			cat resultsk/$algo-$algoseed-$S-$k.txt >> resultskk/$algo-$S-$k.txt
		done
	done
done