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
	
	while(true){
		bool executed = false;
		checkAddress(mips);
		std::cerr<<std::bitset<32>(mips.memory[mips.pc])<<std::endl;
		std::cerr<<"PC: "<<mips.pc<<std::endl;
		std::cerr<<"Next PC: "<<mips.npc<<std::endl;
		int next_pc = mips.npc;
		r_type(mips, executed);
		i_type(mips, executed);
		j_type(mips, executed);
		if(!executed){
			throw (static_cast<int>(Exception::INSTRUCTION));
		}	
		std::cerr<<"Registers after execution: ";
		for(int i=0; i<mips.registers.size(); i++){
			std::cerr<<mips.registers[i]<<" ";
		}
		std::cerr<<std::endl;
		mips.pc = next_pc;
		std::cerr<<std::endl;
		std::cerr<<std::endl;
	}
}
