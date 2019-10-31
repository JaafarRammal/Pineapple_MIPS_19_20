#!/bin/bash

src/main


for InputBin in (test_bench/bin)
do 
    ./bin/simulator ./test_bench/bin/$InputBin
    RETCODE = $?
    ExpectedResult = $(<test_bench/expected/$InputBin.txt)

    if [[ "$RETCODE" == "$ExpectedResult"]]; then 
        echo "Successful test $InputBin";
    else 
        echo "Failed test $InputBin";
fi;