all:
	g++ -I ./include/ ./src/main.cpp ./src/mips_init.cpp ./src/mips_i_type.cpp ./src/mips_r_type.cpp ./src/mips_j_type.cpp -o ./bin/simulator

instructions:
	perl -ne 'print pack("B32", $_)' < instructions.txt > instructions.bin
