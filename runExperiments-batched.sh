# greedyStateGreedyActionPI
# randomStateGreedyActionPI
# randomStateRandomActionPI
# greedyStateRandomActionPI
# batchStateGreedyActionPI
# batchStateRandomActionPI
# randomPolicyPI

rm -rf resultsb
mkdir resultsb
polseed=1000
algoseed=2000
for dir in $(ls data/mdpsb); do
	for infile in $(ls data/mdpsb/$dir); do
		polseed=$((polseed+1))
		for batchSize in {2..60}; do
			echo $dir $infile $batchSize
			algoseed=$((algoseed+1))
			for algo in batchStateGreedyActionPI batchRandomPolicyPI; do
				./planner --mdpFile ./data/mdpsb/$dir/$infile --initPolicyType random --policyRandomSeed $polseed --algorithmRandomSeed $algoseed --algorithm $algo --batchSize $batchSize | grep iterations >> resultsb/$algo-$dir-$batchSize.txt
				# echo $cmd
			done
			# done
		done
	done
done

rm -f resb.txt
for file in $(ls resultsb); do
	printf "$file " >> resb.txt
	cat resultsb/$file | cut -f 2 | python3 avg.py >> resb.txt
done