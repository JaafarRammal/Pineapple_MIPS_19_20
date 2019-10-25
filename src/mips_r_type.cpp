#include "mips_r_type.hpp"

using namespace std;

// main executor call

void r_type(MIPS& mips, bool& executed);

// r-type executions

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