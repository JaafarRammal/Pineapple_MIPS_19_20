#include "mips_init.hpp"


void init_mips(MIPS& mips){

  mips.hi = 0;
  mips.lo = 0;
  mips.registers.resize(32, 0);

  mips.memory.resize(MEMORY_SIZE, 0);

  mips.pc = ADDR_INSTR_OFFSET;
  mips.npc = mips.pc + 1;

}

void checkAddress(MIPS& mips){
  if(((mips.pc < ADDR_INSTR_OFFSET) || (mips.pc > (ADDR_INSTR_OFFSET + ADDR_INSTR_SIZE - 1))) && (mips.pc != ADDR_NULL_OFFSET)){
		// pc outside instruction memory range. Memory exception
    throw (static_cast<int>(Exception::MEMORY));
	}
	if(mips.pc == ADDR_NULL_OFFSET){
    // reached end of program at address zero
		uint32_t output = mips.registers[2] & 0x000000FF;
		std::exit(output);
	}
}

void importBitFile(MIPS& mips, std::string filename){

  std::ifstream inputFile(filename, std::ios::binary | std::ios::ate);

	if(!inputFile.is_open()){
		std::cout << "E: Could not open file" << std::endl;
		std::exit(2);
	}

  


}