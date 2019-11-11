#!/bin/bash

for i in *.cpp
do
    echo $i
    mips-linux-gnu-gcc -static -nostdlib $i -o binary_test/$i.mips.elf
    mips-linux-gnu-objcopy  -O binary -j .text binary_test/$i.mips.elf  binary_test/$i.mips.bin
done
