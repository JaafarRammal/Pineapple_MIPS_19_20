#!/bin/bash

src/main
RETCODE = $?
ExpectedResult = $(<test_bench/expected/$InputBin.txt)

if [[ "$RETCODE" == "$ExpectedResult"]]; then 
    echo "Successful test $InputBin";
else 
    echo "Failed test $InputBin";
fi;