#include "mips_init.hpp"

void init_mips(MIPS& mips){

  mips.hi = 0;
  mips.lo = 0;
  mips.registers.resize(32, 0);

  mips.memory.resize(MEMORY_SIZE, 0);

  mips.pc = ADDR_INSTR_OFFSET;
  mips.npc = mips.pc + 1;

}

void checkAddress(MIPS&);