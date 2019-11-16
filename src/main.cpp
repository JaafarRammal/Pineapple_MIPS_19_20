#include <iostream>
#include <string>
#include <cstdint>

#include "mips_all.hpp"

using namespace std;

int main(int argc, char* argv[]){

	// check for binary input
	if(argc < 2){
		std::cerr << "Error: Expected binary file input" << std::endl;
		return 2; // what exit code should we use here?
	}

	// create and initialize a mips
	MIPS mips;
	init_mips(mips);
	importBitFile(mips, argv[1]);

	if(argc > 2){
		std::string flag = argv[2];
		if(flag == "debug"){
			mips.debugFlag = true;
		}
	}
	
	while(true){
		bool executed = false;
		checkAddress(mips);
		if(mips.debugFlag){
			std::cerr<<std::bitset<32>(mips.memory[mips.pc])<<std::endl;
			std::cerr<<"PC: "<<mips.pc<<std::endl;
			std::cerr<<"Next PC: "<<mips.npc<<std::endl;
		}
		int next_pc = mips.npc;
		r_type(mips, executed);
		i_type(mips, executed);
		j_type(mips, executed);
		if(!executed){
			std::cerr<<"Invalid instruction"<<std::endl;
			std::exit(Exception::INSTRUCTION);
		}	
		if(mips.debugFlag){
			std::cerr<<"Registers after execution: ";
			for(int i=0; i<32; i++){
				std::cerr<<mips.registers[i]<<" ";
			}
			std::cerr<<std::endl;
			std::cerr<<std::endl;
			std::cerr<<std::endl;
		}
		mips.pc = next_pc;
	}
}
