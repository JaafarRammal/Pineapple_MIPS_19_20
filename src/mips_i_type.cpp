
#include "mips_i_type.hpp"
#include <cmath> 

using namespace std;

// main executor call

void i_type(MIPS& mips, bool& executed){
	//26 right shift to get instruction type
	uint32_t opcode = mips.memory[ADDR_INSTR_OFFSET] >> 26;
	uint32_t rs = mips.memory[ADDR_INSTR_OFFSET] >> 21;
	rs = rs - (opcode << 5);
	uint32_t rt = mips.memory[ADDR_INSTR_OFFSET] >> 16;
	rt = rt - (opcode << 11) - (rs << 5);
	uint32_t immediate = mips.memory[ADDR_INSTR_OFFSET];
	immediate = immediate - (opcode << 26) - (rs << 21) - (rt << 16);

	switch(opcode){
		case "0x001000":
			addi(mips, rs, rt, immediate);
			executed = true;
		case "0x001001":
			addiu(mips, rs, rt, immediate);
			executed = true;
		case "0x001100" : 
			andi(mips, rs, rt, immediate);
			executed = true;
		case "0x000100" : 
			beq(mips, rs, immediate);
			executed = true;
		case "0x000001" : 
			if (rt == "0x00001"){
				bgez(mips, rs, immediate);
			}
			else if (rt == "0x10001"){
				bgezal(mips, rs, rt, immediate);
			}
			else if (rt == "0x00000"){
				bltz(mips, rs, immediate);
			}
			else if (rt == "0x10000"){
				bltzal(mips, rs, rt, immediate);
			}
			executed = true;
		case "0x000111" : 
			bgtz(mips, rs, rt, immediate);
			executed = true;
		case "0x000110" : 
			blez(mips, rs, rt, immediate);
			executed = true;
		case "0x000101" : 
			bne(mips, rs, immediate);
			executed = true;
		case "0x100100" : 
			lbu(mips, rs, rt, immediate);
			executed = true;
		case "0x100000" : 
			lb(mips, rs, rt, immediate);
			executed = true;
		case "0x100101" : 
			lhu(mips, rs, rt, immediate);
			executed = true;
		case "0x100001" : 
			lh(mips, rs, rt, immediate);
			executed = true;
		case "0x001111" : 
			lui(mips, rt, immediate);
			executed = true;
		case "0x100011" : 
			lw(mips, rs, rt, immediate);
			executed = true;
		case "0x100010" : 
			lwl(mips, rs, rt, immediate);
			executed = true;
		case "0x100110" : 
			lwr(mips, rs, rt, immediate);
			executed = true;
		case "0x001101" : 
			ori(mips, rs, rt, immediate);
			executed = true;
		case "0x001010" : 
			slti(mips, rs, rt, immediate);
			executed = true;
		case "0x001011" : 
			sltiu(mips, rs, rt, immediate);
			executed = true;
		case "0x101000" : 
			sb(mips, rs, rt, immediate);
			executed = true;
		case "0x101001" : 
			sh(mips, rs, rt, immediate);
			executed = true;
		case "0x101011" : 
			sw(mips, rs, rt, immediate);
			executed = true;
		case "0x001110" : 
			xori(mips, rs, rt, immediate);
			executed = true;
		default : 
			executed = false; // make sure
	}
}


// i-type executions
// variables named based on the attached js helper for instructions


void addi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
//rt <- rs + immediate
 // load signed operands
  int32_t rs_signed = mips.registers[rs];
  int32_t sum = rs_signed + immediate;
 
  if( (immediate<0) && (rs_signed<0) && (sum>=0) || (immediate>0) && (rs_signed>0) && (sum<=0)){
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
	mips.registers[rt] = static_cast<uint32_t>((immediate + static_cast<uint32_t>(mips.registers[rs])));
	mips.npc += 1;
}
void andi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (immediate & mips.registers[rs]);
 	mips.npc += 1;
}

void beq(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] == mips.registers[rt]){
		// no need to shift offset since we are using 32 bits not 8 bits
		// mips.npc = mips.npc + (offset << 2)
		mips.npc = mips.npc + offset;
	}else{
		mips.npc += 1;
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
	if (mips.registers[rs] != mips.registers[rs]){
		// same remark
		mips.npc += offset;
	}else{
		mips.npc += 1;
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
// some problems here, will need to change a bit the code
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

