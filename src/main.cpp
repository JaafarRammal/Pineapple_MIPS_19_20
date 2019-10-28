#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <mips_init.hpp>

int main(int argc, char* argv[]){

	// initialise mips
	// this function should initialise registers
	// as well as the memory and pc
	MIPS TmpMips;
	init_mips(TmpMips);


    //load binary into ADDR_INSTR
    // (most of this is taken from last lecture)
    int inputword;
    std::fstream inputfile;
    inputfile.open(argv[1], std::ios::in | std::ios::binary);
    int nb_instr = 0;

    while(true){
        file.seekg(0, std::ios::cur);
        file.read(reinterpret_cast<char*>(&word), 4);
        // load  bitstream in MEM_INST
        // for every instruction
            // decode (r,i,j type)
            //execute
            // MIPS = next MIPS
    }
    file.close();
	
}


  
