#!/bin/bash

inputList=("3\n1 2 3\n2 3 1\n3 1 2\n" "4\n1 2 3 4\n2 1 4 3\n3 4 1 2\n4 3 2 1\n" "3\n1 2 3\n2 2 1\n3 1 2\n")

while true; do

	for input in "${inputList[@]}"; do
	echo "----------------------------"
	echo "input : $input"
	temp=$(latin-checker "$input")
	echo "output: $temp"
	sleep 1.0

	done

done
