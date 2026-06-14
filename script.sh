#!/bin/bash
let score_good=0
let total_good=0

let score_syn=0
let total_syn=0

let score_sem=0
let total_sem=0

let score_warn=0
let total_warn=0

for file in test/good/*.tpc
	do
		./bin/tpcc < "$file"
		result=$?
		if [ $result -eq 0 ]
			then let score_good=score_good+1
			echo "[BON] $file"
		fi
		let total_good=total_good+1
	done

for file in test/syn-err/*.tpc 
	do
		./bin/tpcc < "$file" > /dev/null 2> /dev/null
		result=$?
		if [ $result -eq 1 ]
			then let score_syn=score_syn+1
			echo "[BON] $file"
		fi
		let total_syn=total_syn+1
	done

for file in test/sem-err/*.tpc
	do
		./bin/tpcc < "$file" > /dev/null 2> /dev/null
		result=$?
		if [ $result -eq 2 ]
			then let score_sem=score_sem+1
			echo "[BON] $file"
		else
			echo "[FAIL] $file -> retour $result"
		fi
		let total_sem=total_sem+1
	done

for file in test/warn/*.tpc
	do
		./bin/tpcc < "$file" 
		result=$?
		if [ $result -eq 0 ]
			then let score_warn=score_warn+1
			echo "[BON] $file"
		
		else
			echo "[FAIL] $file -> retour $result"
		fi
		let total_warn=total_warn+1
		
	done

let score_total=score_good+score_syn+score_sem+score_warn
let total_all=total_good+total_syn+total_sem+total_warn

echo "Good : $score_good / $total_good"
echo "Syn-err: $score_syn / $total_syn"
echo "Sem-err : $score_sem / $total_sem"
echo "Warn : $score_warn / $total_warn"
echo "score total : $score_total / $total_all"
