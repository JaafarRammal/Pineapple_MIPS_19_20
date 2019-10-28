#include "mips_r_type.hpp"

using namespace std;

// main executor call

void r_type(MIPS& mips, bool& executed){
  //26 right shift to get instruction type
  uint32_t opcode = mips.memory[ADDR_INSTR_OFFSET] && 0x0000003F; // 6 LSB
  uint32_t rs = mips.memory[ADDR_INSTR_OFFSET] >> 21;
  rs = rs - (opcode << 5);
  uint32_t rt = mips.memory[ADDR_INSTR_OFFSET] >> 16;
  rt = rt - (opcode << 11) - (rs << 5);
  uint32_t immediate = mips.memory[ADDR_INSTR_OFFSET];
  immediate = immediate - (opcode << 26) - (rs << 21) - (rt << 16);

  switch(opcode){
    // case "001000":
    //   addi(mips, rs, rt, immediate);
    //   executed = true; return;\nreturn;
    default:
      0;
  }
}

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
	mips.registers[rd] = static_cast<uint32_t>((static_cast<uint32_t>(mips.registers[rs]) + static_cast<uint32_t>(mips.registers[rt])));
	mips.npc += 1;
}

void And(MIPS& mips,uint32_t rs,uint32_t rt, uint32_t rd){
  mips.registers[rd] = (mips.registers[rs] & mips.registers[rt]);
  mips.npc += 1;
}

void divu(MIPS& mips, uint32_t rs, uint32_t rt){
  // check if dividing by zero
  if(mips.registers[rt] == 0){
    // arithmetic error dividng by zero
    // [UNDEFINED BEHAVIOR]
  }else{
    // load unsigned operands
    uint32_t rs_unsigned = static_cast<uint32_t>(mips.registers[rs]);
    uint32_t rt_unsigned = static_cast<uint32_t>(mips.registers[rt]);
    // insert quotient in Lo and reminder in Hi
    mips.hi = static_cast<uint32_t>(rs_unsigned % rt_unsigned);
    mips.lo = static_cast<uint32_t>(rs_unsigned / rt_unsigned);
    mips.npc += 1;
  }
}

void div(MIPS& mips, uint32_t rs, uint32_t rt){
  // check if dividing by zero
  if(mips.registers[rt] == 0){
    // arithmetic error dividng by zero
    // [UNDEFINED BEHAVIOR]
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
void jr(MIPS& mips, uint32_t rt){
  if(mips.registers[rt] % 4 != 0){
		// unvalid address
    // [MEMORY EXCEPTION]
	}
	else{
		mips.npc = mips.registers[rt] / 4;
	}
}

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

void mult(MIPS& mips, uint32_t rs,uint32_t rt){
  // load signed operands
  // use 64 bits
  int64_t rs_signed = mips.registers[rs];
	int64_t rt_signed = mips.registers[rt];

  // hi <- (63:32)p & lo <- (31:0)p
	int64_t product  = rs_signed * rt_signed;
	mips.hi = (product >> 32);
	mips.lo = (product << 32) >> 32;
	mips.npc += 1;
}
void multu(MIPS& mips, uint32_t rs, uint32_t rt){
  // load unsigned operands
  // use 64 bits
  uint64_t rs_unsigned = mips.registers[rs];
	uint64_t rt_unsigned = mips.registers[rt];

  // hi <- (63:32)p & lo <- (31:0)p
	uint64_t product  = rs_unsigned * rt_unsigned;
	mips.hi = (product >> 32);
	mips.lo = (product << 32) >> 32;
	mips.npc += 1;
}

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
  uint32_t rs_unsigned = static_cast<uint32_t>(mips.registers[rs]);
  uint32_t rt_unsigned = static_cast<uint32_t>(mips.registers[rt]);
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
  uint32_t rt_unsigned = static_cast<uint32_t>(mips.registers[rt]);
  mips.registers[rd] = static_cast<uint32_t>((rt_unsigned >> sa));
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
  uint32_t rt_unsigned = static_cast<uint32_t>(mips.registers[rt]);
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
  uint32_t rs_signed = static_cast<uint32_t>(mips.registers[rs]);
  uint32_t rt_signed = static_cast<uint32_t>(mips.registers[rt]);
  uint32_t difference = static_cast<uint32_t>(rs_signed - rt_signed);
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