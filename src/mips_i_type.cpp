
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
	 mips.registers[rt] = (uint8_t)LOAD_MEMORY(mips.memory[base + offset]);
	 mips.npc += 1;
}
void lb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.registers[rt] = (int8_t)LOAD_MEMORY(mips.memory[base + offset]);
	 mips.npc += 1;
}
void lhu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.registers[rt] = (uint16_t)LOAD_MEMORY(mips.memory[base + offset]);
	 mips.npc += 1;
}
void lh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.registers[rt] = (int16_t)LOAD_MEMORY(mips.memory[base + offset]);
	 mips.npc += 1;
}
void lui(MIPS& mips, uint32_t rt, int32_t immediate){
	mips.registers[rt] = immediate*pow(2,16);
	mips.npc += 1;

}
void lw(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.registers[rt] = (int32_t)LOAD_MEMORY(mips.memory[base + offset]);
	mips.npc += 1;

}

void get_16msb(int& input){
	if (input < 0){
		input = input+(input%65536);
	}
	else {
		input = input-(input%65536);
	}
}
void lwl(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	// load rt 
	int32_t rt_signed = mips.registers[rt];
	// load word from memory
	 int32_t loaded_word = LOAD_MEMORY(mips.memory[base + offset]);
	// get 16 msb from memory and shift left by 16 bits
	get_16msb(loaded_word);	
	// merge 
	mips.registers[rt] = loaded_word*pow(2,-16) + 	get_16msb(rt_signed);
	mips.npc += 1;
}

void lwr(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	// load rt 
	int32_t rt_signed = mips.registers[rt];
	// load word from memory
	int32_t loaded_word = LOAD_MEMORY(mips.memory[base + offset]);
	// get 16 lsb from memory and shift left by 16 bits & merge 
	mips.registers[rt] = loaded_word%65536 + get_16msb(rt_signed);
	mips.npc += 1;
}
void sb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	 mips.registers[rt] = (int8_t)STORE_MEMORY(mips.memory[base + offset]);
	 mips.npc += 1;
}
void sh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	mips.registers[rt] = (int16_t)STORE_MEMORY(mips.memory[base + offset]);
	mips.npc += 1;
}
void sw(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (int32_t)STORE_MEMORY(mips.memory[base + offset]);
	mips.npc += 1;
}

