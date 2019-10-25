#include "mips_r_type.hpp"

using namespace std;

// main executor call

void r_type(MIPS& mips, bool& executed);

// r-type executions

void add(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // use signed integers
  int32_t a = mips.registers[rs];
  int32_t b = mips.registers[rt];
  int32_t r = a + b;

  /*
   Check if result overflows. This occurs if:
   - A<0 and B<0 and R>0
   - A>0 and B>0 and R<0
  */

  if( (a<0) && (b<0) && (r>0) | (a>0) && (b>0) && (r<0)){
    // overflow
    // [ARITHMATIC EXCEPTION]
  }else{
    // no overflow
    mips.registers[rd] = r;
    mips.npc += 1;
  }
}

void addu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
	mips.registers[rd] = (mips.registers[rs] + mips.registers[rt]) ;
	mips.npc += 1;
}

void And(MIPS& mips,uint32_t rs,uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rs] & mips.registers[rt]);
  mips.npc += 1;
}

void div(MIPS& mips, uint32_t rs, uint32_t rt){
  // check if dividing by zero
  if(mips.registers[rt] == 0){
    // arithmetic error dividng by zero
    // [ARITHMATIC EXCEPTION]
  }else{
    // load unsigned operands
    uint32_t rs_unsigned = mips.registers[rs];
    uint32_t rt_unsigned = mips.registers[rt];
    // insert quotient in Lo and reminder in Hi
    mips.hi = rs_unsigned % rt_unsigned;
    mips.lo = rs_unsigned / rt_unsigned;
    mips.npc += 1;
  }
}

void divu(MIPS& mips, uint32_t rs, uint32_t rt){
  // check if dividing by zero
  if(mips.registers[rt] == 0){
    // arithmetic error dividng by zero
    // [ARITHMATIC EXCEPTION]
  }else{
    // load signed operands
    int32_t rs_signed = mips.registers[rs];
    int32_t rt_signed = mips.registers[rt];
    // insert quotient in Lo and reminder in Hi
    mips.hi = rs_signed % rt_signed;
    mips.lo = rs_signed / rt_signed;
    mips.npc += 1;
  }
}

void jalr(MIPS& mips, uint32_t rs, uint32_t rd);
void jr(MIPS& mips, uint32_t rt);

void mfhi(MIPS& mips, uint32_t rd){
  mips.registers[rd] = mips.hi;
  mips.npc += 1;
}

void mflo(MIPS& mips, uint32_t rd){
  mips.registers[rd] = mips.lo;
  mips.npc += 1;
}

void mthi(MIPS& mips, uint32_t rt){
  mips.hi = mips.registers[rt];
  mips.npc += 1;
}

void mtlo(MIPS& mips, uint32_t rt){
  mips.lo = mips.registers[rt];
  mips.npc += 1;
}

void mult(MIPS& mips, uint32_t rs,uint32_t rt);
void multu(MIPS& mips, uint32_t rs, uint32_t rt);

void Or(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rs] | mips.registers[rt]);
  mips.npc += 1;
}

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

void Xor(MIPS& mips,  uint32_t rs, uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rs] ^ mips.registers[rt]);
  mips.npc += 1;
}