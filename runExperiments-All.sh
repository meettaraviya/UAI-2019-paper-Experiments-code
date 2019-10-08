# greedyStateGreedyActionPI
# randomStateGreedyActionPI
# randomStateRandomActionPI
# greedyStateRandomActionPI
# batchStateGreedyActionPI
# batchStateRandomActionPI
# randomPolicyPI

rm -rf results/*
# touch results/logfile.txt

for dir in $(ls data/mdps); do
	# for algo in greedyStateGreedyActionPI randomStateGreedyActionPI randomStateRandomActionPI greedyStateRandomActionPI batchStateGreedyActionPI batchStateRandomActionPI randomPolicyPI; do
	for algo in greedyStateGreedyActionPI randomStateGreedyActionPI randomStateRandomActionPI greedyStateRandomActionPI batchStateGreedyActionPI batchStateRandomActionPI randomPolicyPI batchRandomStateGreedyActionPI batchRandomStateRandomActionPI batchRandomPolicyPI; do
	# for algo in batchRandomStateGreedyActionPI batchRandomStateRandomActionPI batchRandomPolicyPI; do
		touch results/$algo-$dir.txt
		for infile in $(ls data/mdps/$dir); do
			echo $dir $algo $infile
			for algoseed in {1..20}; do
				./planner --mdpFile ./data/mdps/$dir/$infile --initPolicyType random --algorithmRandomSeed $algoseed --algorithm $algo --batchSize 5 | grep iterations >> results/$algo-$dir.txt
			done
		done
	done
done

rm -f res.txt
for file in $(ls results); do
	printf "$file\n"
	printf "$file " >> res.txt
	cat results/$file | cut -f 2 | python avg.py >> res.txt
done