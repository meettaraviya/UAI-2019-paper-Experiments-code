rm -f res5.txt

for file in $(ls results5 | grep -v batchStateGreedyAction); do
	printf "$file\n"; printf "$file " >> res5.txt
	cat results5/$file | grep iterations | cut -f 2 | python avg.py >> res5.txt
done

for file in $(ls results5 | grep batchStateGreedyAction); do
	printf "$file\n"; printf "$file " >> res5.txt
	cat results5/$file | grep iterations | cut -f 2 | python avg-k.py >> res5.txt
done