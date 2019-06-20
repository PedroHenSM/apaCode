#!/bin/bash

totalMethods=4 # Pivoting Methods
methods=(1 2 3 4)

totalSeeds=30
seeds=(1 2 3 4 5 6 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30)

totalDimensions=8 # Maybe 7 is enough | for 100000000 took 35674691 microseconds approx
dimensions=(10 100 1000 10000 100000 1000000 10000000 100000000)

totalShuffle=3
shuffles=(0.1 0.3 0.5)

n=0
while(($n<$totalDimensions))
do
	s=0
	while(($s<$totalSeeds))
	do
		sh=0
		while(($sh<$totalShuffle))
		do
			./bin/Debug/apaCode -s ${seeds[s]} -n ${dimensions[n]} -p ${shuffles[sh]}
			sh=$((sh+1))
		done
		s=$((s+1))
	done
	n=$((n+1))
done
