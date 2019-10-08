rm -f res.txt

for file in $(ls results | grep -v greedyStateGreedyAction); do
	printf "$file\n"; printf "$file " >> res.txt
	cat results/$file | cut -f 2 | python avg.py >> res.txt
done

for file in $(ls results | grep greedyStateGreedyAction); do
	printf "$file\n"; printf "$file " >> res.txt
	cat results/$file | cut -f 2 | python avg-k.py >> res.txt
done