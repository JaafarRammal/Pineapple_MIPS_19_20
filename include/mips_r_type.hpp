#ifndef MIPS_R_TYPE
#define MIPS_R_TYPE

#include "mips_init.hpp"

// Define all the R-type instructions
// These take in input by default a MIPS structure by reference that is modifiable to access common register and memory

// main executor call

void r_type(MIPS& mips, bool& executed);

// r-type executions
// variables named based on the attached js helper for instructions

void add(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void addu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void And(MIPS& mips,uint32_t rs,uint32_t rt, uint32_t rd);

void div(MIPS& mips, uint32_t rs, uint32_t rt);
void divu(MIPS& mips, uint32_t rs, uint32_t rt);

void jalr(MIPS& mips, uint32_t rs, uint32_t rd);
void jr(MIPS& mips, uint32_t rt);

void mfhi(MIPS& mips, uint32_t rd);
void mflo(MIPS& mips, uint32_t rd);
void mthi(MIPS& mips, uint32_t rt);
void mtlo(MIPS& mips, uint32_t rt);
void mult(MIPS& mips, uint32_t rs,uint32_t rt);
void multu(MIPS& mips, uint32_t rs, uint32_t rt);

void Or(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);

void slt(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void sltu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void sll(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa);
void sllv(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void srl(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa);
void sra(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa);
void srav(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void srlv(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void sub(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);
void subu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd);

void Xor(MIPS& mips,  uint32_t rs, uint32_t rt, uint32_t rd);


#endif