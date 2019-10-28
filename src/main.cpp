#include <iostream>
#include <fstream>
#include <cmaths>
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
    file.open(argv[1], std::ios::in | std::ios::binary);
    int nb_instr = 0;

    while(true){
        file.seekg(0, std::ios::cur);
        file.read(reinterpret_cast<char*>(&word), 4);
        if(nb_instr >= 4194304) break;
        mips.memory = load_ADDR_INSTR(nb_instr, ntohl(word)); // need to define this function
        nb_instr++;
    }
    file.close();
	// will add more functions 



	// assume bitstream loaded from pc , named bitstream

	//decode opcode to know type

	// switch statement for r-types
}


  
