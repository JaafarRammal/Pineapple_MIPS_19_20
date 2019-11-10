#!/bin/bash
#only converts cpp functions into mips format and put it into BIN folder
#will have to be tested on lab computers 


for i = c_code_Single_functions/*.cpp ; do
echo $i

mips-linux-gnu-gcc -static -nostdlib -03 $i -o jr_1.mips.elf
mips-linux-gnu-objcopy  -o binary -j .text jr_1.mips.elf  test_bench/bin/jr_1.mips.bin