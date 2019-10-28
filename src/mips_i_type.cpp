
#include "mips_i_type.hpp"
#include <cmath> 

using namespace std;

// main executor call

void i_type(MIPS& mips, bool& executed);


// i-type executions
// variables named based on the attached js helper for instructions


void addi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
//rt <- rs + immediate
 // load signed operands
  int32_t rs_signed = mips.registers[rs];
  int32_t sum = rs_signed + immediate;
 
  if( (immediate<0) && (rt_signed<0) && (sum>=0) || (immediate>0) && (rt_signed>0) && (sum<=0)){
    // overflow
    // [ARITHMETIC EXCEPTION]
  }
  else{
    // no overflow
    mips.registers[rt] = sum;
    mips.npc += 1;
  }
}

void addiu(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (immediate + mips.registers[rs]) ;
	mips.npc += 1;
}
void andi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (immediate & mips.registers[rs]);
 	mips.npc += 1;
}

void beq(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] == mips.registers[rt]){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}

void bgez(MIPS& mips, uint32_t rs, int32_t offset){
	if (mips.registers[rs] >= 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}
void bgezal(MIPS& mips, uint32_t rs, int32_t offset){
	if (mips.registers[rs] >= 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
		// how to put this in mips object ? 
		mips.gpr31 = mips.npc + 4;
	}
}
void bgtz(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] > 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}
void blez(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] <= 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}
void bltz(MIPS& mips, uint32_t rs, int32_t offset)	{
	if (mips.registers[rs] < 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}
void bltzal(MIPS& mips, uint32_t rs, int32_t offset){
		if (mips.registers[rs] < 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
		// how to put this in mips object ? 
		mips.gpr31 = mips.npc + 4;
	}
}
void bne(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] != 0){
		int32_t tgt_offset = mips.registers[offset]; 
		// lsl #2 
		tgt_offset = tgt_offset*pow(2, 4);
		// add to pc 
		mips.npc = mips.npc + tgt_offset;
	}
}

void ori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
 mips.registers[rt] = (mips.registers[rs] | immediate);
  mips.npc += 1;
}

void slti(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	int32_t rs_signed = mips.registers[rs];

	// rd <- (rs < immediate)
	mips.registers[rd] = rs_signed < immediate ? 1 : 0;
	mips.npc += 1;
}
void sltiu(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
  uint32_t rs_unsigned = mips.registers[rs];

  // rd <- (0||rs < 0||immediate)
  mips.registers[rd] = (0 || rs_unsigned) < (0 || immediate) ? ((0|rs_unsigned) < (0|immediate)) | 1 : 0;
  mips.npc += 1;
}

void xori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	 mips.registers[rt] = (mips.registers[rs] ^ immediate);
  	mips.npc += 1;
}

// will create memory object & initialisation for them 
void lbu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.memory = (uint32_t)mips.memory[base + offset];
}
void lb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.memory = (int32_t)mips.memory[base + offset];
}
void lhu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.memory = (uint16_t)mips.memory[base + offset];
}
void lh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.memory = (int16_t)mips.memory[base + offset];
}
void lui(MIPS& mips, uint32_t rt, int32_t immediate){
	immediate = immediate*pow(2,16);

}
void lw(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lwl(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void lwr(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void sb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void sh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset);
void sw(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate);

