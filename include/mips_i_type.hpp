#ifndef MIPS_I_TYPE
#define MIPS_I_TYPE

#include "mips_init.hpp"

// Define all the I-type instructions
// These take in input by default a MIPS structure by reference that is modifiable to access common register and memory

// Define all the R-type instructions
// These take in input by default a MIPS structure by reference that is modifiable to access common register and memory

// main executor call

void i_type(MIPS& mips, bool& executed);

// r-type executions
// variables named based on the attached js helper for instructions

void addi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);
void addiu(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);
void andi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);

void beq(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset);
void bgez(MIPS& mips, uint32_t rs, int32_t offset);
void bgezal(MIPS& mips, uint32_t rs, int32_t offset);
void bgtz(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset);
void blez(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset);
void bltz(MIPS& mips, uint32_t rs, int32_t offset);
void bltzal(MIPS& mips, uint32_t rs, int32_t offset);
void bne(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset);

void lbu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lhu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lui(MIPS& mips, uint32_t rt, int32_t immediate);
void lw(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lwl(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lwr(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);

void ori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);

void slti(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);
void sltiu(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);
void sb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void sh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void sw(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);

void xori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);

// functions to check if the address is valid to read or write
void canRead(uint32_t address);
void canWrite(uint32_t address);

// functions to read and write a character
char getInput();
void printOutput(char c_out);

#endif