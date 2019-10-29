#ifndef MIPS_INIT
#define MIPS_INIT

#include <vector>

// we will run this file at the beginning to initialize the MIPS
// the different MIPS elements are defined below to "construct" te MIPS

// define the memory map constants as per the coursework guidelines
// these will be used for relevant offset mapping from the target dynamic memory
// divide offsets by 4 as all variables are 32 bits longs and values are orignally given in 8 bits

/*
Offset     |  Length     | Name       | R | W | X |
-----------|-------------|------------|---|---|---|--------------------------------------------------------------------
0x00000000 |        0x4  | ADDR_NULL  |   |   | Y | Jumping to this address means the Binary has finished execution.
0x00000004 |  0xFFFFFFC  | ....       |   |   |   |
0x10000000 |  0x1000000  | ADDR_INSTR | Y |   | Y | Executable memory. The Binary should be loaded here.
0x11000000 |  0xF000000  | ....       |   |   |   |
0x20000000 |  0x4000000  | ADDR_DATA  | Y | Y |   | Read-write data area. Should be zero-initialised.
0x24000000 |  0xC000000  | ....       |   |   |   |
0x30000000 |        0x4  | ADDR_GETC  | Y |   |   | Location of memory mapped input. Read-only.
0x30000004 |        0x4  | ADDR_PUTC  |   | Y |   | Location of memory mapped output. Write-only.
0x30000008 | 0xCFFFFFF8  | ....       |   |   |   |
-----------|-------------|------------|---|---|---|--------------------------------------------------------------------
*/

/*
// 1 byte values

#define ADDR_NULL_OFFSET 0x00000000
#define ADDR_INSTR_OFFSET 0x10000000
#define ADDR_DATA_OFFSET 0x20000000
#define ADDR_GETC_OFFSET 0x30000000
#define ADDR_PUTC_OFFSET 0x30000004

#define ADDR_NULL_SIZE 0x4
#define ADDR_INSTR_SIZE 0x1000000
#define ADDR_DATA_SIZE 0x4000000
#define ADDR_GETC_SIZE 0x4
#define ADDR_PUTC_SIZE 0x4
*/

// 4 bytes values

#define ADDR_NULL_OFFSET 0x00000000
#define ADDR_INSTR_OFFSET 0x04000000
#define ADDR_DATA_OFFSET 0x08000000
#define ADDR_GETC_OFFSET 0x0C000000
#define ADDR_PUTC_OFFSET 0x0C000001

#define ADDR_NULL_SIZE 0x00000001
#define ADDR_INSTR_SIZE 0x00400000
#define ADDR_DATA_SIZE 0x01000000
#define ADDR_GETC_SIZE 0x00000001
#define ADDR_PUTC_SIZE 0x00000001

/*
Structure MIPS will contain the different cpu universal elements that are modifiable(registers, memory, PC, nPC)
Instruction executors will take in input the decoded instruction as well as a MIPS structure by reference which
they will be able to use and modify (for example, read a register, write to memory, etc...)
*/

struct MIPS{

  std::vector<int32_t> memory;
	std::vector<int32_t> registers;
  
  uint32_t pc;
	uint32_t npc;
	
  int32_t Hi;
	int32_t Lo;

};

/*
Initializer function. Type void. Will execute all initialisation protocols
including setting a new MIPS structure with registers to zero and vectors with
correct size
*/

void init_mips(MIPS& mips);

// check if current PC address is okay or should return
void checkAddress(MIPS&);



#endif