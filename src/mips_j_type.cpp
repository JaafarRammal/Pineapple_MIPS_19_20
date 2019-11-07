#include "mips_j_type.hpp"

// main executor call

void j_type(MIPS& mips, bool& executed){
	if(!executed){
		int32_t instruction = mips.memory[mips.pc];
		int32_t address = instruction & 0x03FFFFFF;
		int32_t opcode = (instruction & 0xFC000000) >> 26;
		if(mips.debugFlag){
			std::cerr<<"Opcode is "<<std::bitset<6>(opcode)<<std::endl;
			std::cerr<<"Address is "<<std::bitset<26>(address)<<std::endl;
		}
		

	
		switch(opcode) {
			case 0x2:
				j(mips, address);
				executed = true;
				return;
			case 0x3:
				jal(mips, address);
				executed = true;
				return;
			default:
				executed = false;
				return;
		}
	}
}

// j-type executions
// variables named based on the attached js helper for instructions

void j(MIPS& mips, uint32_t target){
  mips.npc = ((mips.pc & 0x3F000000) | target);
}

void jal(MIPS& mips, uint32_t target){
  mips.registers[31] = (mips.npc) * 4 + 4;
	mips.npc = ((mips.pc & 0x3F000000) | target);
}