#!/bin/bash

TESTBATCH=testDataA1

for i in ./testData/$TESTBATCH/*.c-; do
    echo $i
    j=${i::-3}
    j=$j.out
    diff -rs <(sort <(./src/c- -P $i)) <(sort $j) | grep -E '^Files .+ and .+ are identical$' | awk -F '(Files | and | are identical)' '{print "MATCH"}'
done