#include "mips_j_type.hpp"

// j-type executions
// variables named based on the attached js helper for instructions

void j(MIPS& mips, uint32_t target){
  mips.npc = ((mips.pc & 0x3F000000) | target);
}

void jal(MIPS& mips, uint32_t target){
  mips.registers[31] = (mips.npc) * 4 + 4;
	mips.npc = ((mips.pc & 0x3F000000) | target);
}