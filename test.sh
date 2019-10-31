#!/bin/bash

for InputTxt in test_bench/bin/*.txt
do 
    file=$(echo "$InputTxt" | cut -f 1 -d '.')
    file="${file}.bin"
    perl -ne 'print pack("B32", $_)' < $InputTxt > $file
done

for InputBin in test_bench/bin/*.bin
do 
    ./bin/simulator $InputBin
    simOut=$?
    result=$( basename "$InputBin" | cut -f 1 -d '.')
    expectedResult=$(<test_bench/expected/$result.txt)

    if [ "$simOut" == "$expectedResult" ]
    then 
        echo "Successful test $result"
    else 
        echo "Failed test $result. Expected $expectedResult but got $simOut"
    fi
done
