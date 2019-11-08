
all: simulator

bin/simulator:
	mkdir -p bin
	g++ -std=c++11 -I ./include/ ./src/main.cpp ./src/mips_init.cpp ./src/mips_i_type.cpp ./src/mips_r_type.cpp ./src/mips_j_type.cpp -o ./bin/mips_simulator



instructions:
	perl -ne 'print pack("B32", $_)' < instructions.txt > instructions.bin

run:
	./bin/simulator ./bin/instructions.bin