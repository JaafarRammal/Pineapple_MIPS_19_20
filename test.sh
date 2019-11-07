#!/bin/bash

rm test_bench/results.txt
rm -r ./test_bench/debuggerOutput
mkdir ./test_bench/debuggerOutput

for InputTxt in test_bench/bin/*.txt
do 
    file=$(echo "$InputTxt" | cut -f 1 -d '.')
    file="${file}.bin"
    perl -ne 'print pack("B32", $_)' < $InputTxt > $file
done

s=0
f=0

for InputBin in test_bench/bin/*.bin
do 
    result=$( basename "$InputBin" | cut -f 1 -d '.')
    echo -n "Currently testing $result"
    ./bin/mips_simulator $InputBin &> "./test_bench/debuggerOutput/$result.txt"
    simOut=$?
    expectedResult=$(<test_bench/expected/$result.txt)

    if [ "$simOut" == "$expectedResult" ]
    then 
        let "s=s+1"
        echo " (Successful)"
        echo "Successful test $result" >> "./test_bench/results.txt"
    else 
        let "f=f+1"
        echo " (Failed)"
        echo "Failed test $result. Expected $expectedResult but got $simOut" >> "./test_bench/results.txt"
    fi

    rm $InputBin

done

echo -e "\nA total of $s successes and $f failures"