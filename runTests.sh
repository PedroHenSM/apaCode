#!/bin/bash

totalMethods=4 # Pivoting Methods
methods=(1 2 3 4)

totalSeeds=30 # Independent executions
seeds=(1 2 3 4 5 6 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30)

totalDimensions=2 # 8/7 Maybe 7 is enough | for 100000000 took 35674691 microseconds approx
dimensions=(10 100 1000 10000 100000 1000000 10000000 100000000)

totalShuffle=2
shuffles=(0.05 0.35 1.1)

n=0
while(($n<$totalDimensions))
do
	s=0
	while(($s<$totalSeeds))
	do
		sh=0
		while(($sh<$totalShuffle))
		do
			m=0
			while(($m<$totalMethods))
			do
				echo "Executing method ${methods[m]} with seed ${seeds[s]} with shufflePercentage ${shuffles[sh]} and dimension ${dimensions[d]}"
				./bin/Debug/apaCode -s ${seeds[s]} -n ${dimensions[n]} -p ${shuffles[sh]} -m ${methods[m]}
				m=$((m+1))
			done
			sh=$((sh+1))
		done
		s=$((s+1))
	done
	n=$((n+1))
done
