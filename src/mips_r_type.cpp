#include "mips_r_type.hpp"

using namespace std;

// main executor call

void r_type(MIPS& mips, bool& executed);

// r-type executions

void add(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load signed operands
  int32_t rs_signed = mips.registers[rs];
  int32_t rt_signed = mips.registers[rt];
  int32_t sum = rs_signed + rt_signed;

  /*
   Check if result overflows. This occurs if:
   - A<0 and B<0 and R>0
   - A>0 and B>0 and R<0
  */

  if( (rs_signed<0) && (rt_signed<0) && (sum>=0) || (rs_signed>0) && (rt_signed>0) && (sum<=0)){
    // overflow
    // [ARITHMATIC EXCEPTION]
  }else{
    // no overflow
    mips.registers[rd] = sum;
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

void slt(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load signed operands
  int32_t rs_signed = mips.registers[rs];
  int32_t rt_signed = mips.registers[rt];

  // rd <- (rs < rt)
  mips.registers[rd] = rs_signed < rt_signed ? 1 : 0;
  mips.npc += 1;
}

void sltu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load unsigned operands
  uint32_t rs_unsigned = mips.registers[rs];
  uint32_t rt_unsigned = mips.registers[rt];
  // rd <- (0||rs < 0||rt)
  mips.registers[rd] = (0 || rs_unsigned) < (0 || rt_unsigned) ? ((0|rs_unsigned) < (0|rt_unsigned)) | 1 : 0;
  mips.npc += 1;
}

void sll(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa){
  mips.registers[rd] = (mips.registers[rt] << sa);
	mips.npc += 1;
}

void sllv(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rt] << mips.registers[rs]);   // or sll(mips, rt, rd, mips.registers[rs]) :o
	mips.npc += 1;
}

void srl(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa){
  // load unsigned operand
  uint32_t rt_unsigned = mips.registers[rt];
  mips.registers[rd] = (rt_unsigned >> sa);
	mips.npc += 1;
}

void sra(MIPS& mips, uint32_t rt, uint32_t rd, uint32_t sa){
  // load signed operand
  int32_t rt_signed = mips.registers[rt];
	mips.registers[rd] = (rt_signed >> sa);
  mips.npc += 1;
}

void srav(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load signed operand
  int32_t rt_signed = mips.registers[rt];
  mips.registers[rd] = (rt_signed >> mips.registers[rs]);
  mips.npc += 1;
}

void srlv(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load unsigned operand
  uint32_t rt_unsigned = mips.registers[rt];
  mips.registers[rd]  = (rt_unsigned >> mips.registers[rs]);
  mips.npc += 1;
}

void sub(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load signed operands
  int32_t rs_unsigned = mips.registers[rs];
  int32_t rt_unsigned = mips.registers[rt];
  int32_t difference = rs_unsigned - rt_unsigned;
  mips.registers[rd] = difference;
  mips.npc += 1;
}

void subu(MIPS& mips, uint32_t rs, uint32_t rt, uint32_t rd){
  // load unsigned operands
  uint32_t rs_signed = mips.registers[rs];
  uint32_t rt_signed = mips.registers[rt];
  uint32_t difference = rs_signed - rt_signed;
  mips.registers[rd] = difference;
  mips.npc += 1;
  /*
   Check if result overflows. This occurs if:
   - A<0 and B<0 and R>0
   - A>0 and B>0 and R<0
  */

  if( (rs_signed<0) && (rt_signed>0) && (difference>=0) || (rs_signed>0) && (rt_signed<0) && (difference<=0)){
    // overflow
    // [ARITHMATIC EXCEPTION]
  }else{
    // no overflow
    mips.registers[rd] = difference;
    mips.npc += 1;
  }
}

void Xor(MIPS& mips,  uint32_t rs, uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rs] ^ mips.registers[rt]);
  mips.npc += 1;
}