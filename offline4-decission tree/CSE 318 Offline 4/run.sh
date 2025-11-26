#!/bin/bash

# Output CSV file
OUTFILE="results_iris.csv"
echo "criterion,depth,accuracy,nodes" > $OUTFILE

# Compile if needed
g++ main.cpp -o decision_tree

# Run for all criteria and depths
for criterion in IG IGR NWIG; do
  for depth in {0..3}; do
    echo "Running: $criterion with depth $depth"

    # Capture the output
    output=$(./decision_tree $criterion $depth)

    # Extract the last printed accuracy and node count
    accuracy=$(echo "$output" | grep "Average Accuracy:" | awk '{print $3}')
    nodes=$(echo "$output" | grep "#Nodes:" | tail -n 1 | awk '{print $2}')

    echo "$criterion,$depth,$accuracy,$nodes" >> $OUTFILE
  done
done

echo "All results saved to $OUTFILE"
