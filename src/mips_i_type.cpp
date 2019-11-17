
#include "mips_i_type.hpp"
#include <cmath> 

using namespace std;

// main executor call

void i_type(MIPS& mips, bool& executed){

	if(!executed){
	
		uint32_t instruction = mips.memory[mips.pc];
		uint32_t opcode = instruction >> 26;
		uint32_t rs = (instruction & 0x03E00000) >> 21;
		uint32_t rt= (instruction & 0x001F0000) >> 16;
		int32_t immediate = instruction & 0x0000FFFF;
		if(mips.debugFlag){
			std::cerr<<"Opcode is "<<std::bitset<6>(opcode)<<std::endl;
			std::cerr<<"RS is "<<rs<<std::endl;
			std::cerr<<"RT is "<<rt<<std::endl;
			std::cerr<<"Immediate is "<<immediate<<std::endl;
		}

		// we need a sign extended immediate in some functions

		int32_t s_immediate;

		// check MSB
		if(immediate >> 15){
			s_immediate = immediate | 0xFFFF0000;
		}
		else{
			s_immediate = immediate;
		}

		switch(opcode){
			case 0b001000:
				addi(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001001:
				addiu(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001100 : 
				andi(mips, rs, rt, immediate);
				executed = true; return;
			case 0b000100 : 
				beq(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b000001 : 
				if (rt == 0b00001){
					bgez(mips, rs, s_immediate);
				}
				else if (rt == 0b10001){
					bgezal(mips, rs, s_immediate);
				}
				else if (rt == 0b00000){
					bltz(mips, rs, s_immediate);
				}
				else if (rt == 0b10000){
					bltzal(mips, rs, s_immediate);
				}
				executed = true; return;
			case 0b000111 : 
				bgtz(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b000110 : 
				blez(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b000101 : 
				bne(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100100 : 
				lbu(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100000 : 
				lb(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100101 : 
				lhu(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100001 : 
				lh(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001111 :
				checkConstantField(rs, 0);
				lui(mips, rt, immediate);
				executed = true; return;
			case 0b100011 : 
				lw(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100010 : 
				lwl(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b100110 : 
				lwr(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001101 : 
				ori(mips, rs, rt, immediate);
				executed = true; return;
			case 0b001010 : 
				slti(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001011 : 
				sltiu(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b101000 : 
				sb(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b101001 : 
				sh(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b101011 : 
				sw(mips, rs, rt, s_immediate);
				executed = true; return;
			case 0b001110 : 
				xori(mips, rs, rt, immediate);
				executed = true; return;
			default : 
				executed = false; // make sure
				return;
		}
	}
}


// i-type executions
// variables named based on the attached js helper for instructions


void addi(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	
	//rt <- rs + immediate
 	// load signed operands
  int32_t rs_signed = mips.registers[rs]; 
  if( ((immediate<0) && (rs_signed<0) && (rs_signed + immediate>=0)) || ((immediate>0) && (rs_signed>0) && (rs_signed + immediate<=0))){
    // overflow
    // [ARITHMETIC EXCEPTION]
		std::cerr<<"Arithmetic overflow when executing "<<rs_signed<<" + "<<immediate<<std::endl;
		std::exit(Exception::ARITHMETIC);
  }
  else{
    // no overflow
    mips.registers[rt] = rs_signed + immediate;
  }
	mips.npc += 1;

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
	if(mips.registers[rs] >= 0){
		mips.npc += offset;
	}
	else{
		++mips.npc;
	}
}
void bgezal(MIPS& mips, uint32_t rs, int32_t offset){
	// set return address
	mips.registers[31] = (mips.pc * 4) + 8;
	if(mips.registers[rs] >= 0){
		mips.npc += offset;
	}
	else{
		mips.npc += 1;
	}
}
void bgtz(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if(rt != 0x00000000){
		// rt must be 0
		// [Instruction Exception]
		std::cerr<<"Invalid instruction set for bgtz with RT not null"<<std::endl;
		std::exit(Exception::INSTRUCTION);
	}
	else{
		if(mips.registers[rs] > 0){
			mips.npc += offset;
		}
		else{
			mips.npc += 1;
		}
	}
}
void blez(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if(rt != 0){
		// rt must be 0
		// [Instruction Exception]
		std::cerr<<"Invalid instruction set for blez with RT not null"<<std::endl;
		std::exit(Exception::INSTRUCTION);
	}

	else{
		if(mips.registers[rs] <= 0x00000000){
			mips.npc += offset;
		}
		else{
			mips.npc += 1;
		}
	}
}
void bltz(MIPS& mips, uint32_t rs, int32_t offset)	{
	if(mips.registers[rs] < 0){
		mips.npc += offset;
	}
	else{
		mips.npc += 1;
	}
}
void bltzal(MIPS& mips, uint32_t rs, int32_t offset){
	// set address
	mips.registers[31] = (mips.pc * 4) + 8;
	if(mips.registers[rs] < 0){
		mips.npc += offset;
	}
	else{
		mips.npc += 1;
	}
}
void bne(MIPS& mips, uint32_t rs, uint32_t rt, int32_t offset){
	if (mips.registers[rs] != mips.registers[rt]){
		// same remark
		mips.npc += offset;
	}else{
		mips.npc += 1;
	}
}

void lui(MIPS& mips, uint32_t rt, int32_t immediate){
	mips.registers[rt] = immediate << 16;
	mips.npc += 1;
}

void ori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (mips.registers[rs] | immediate);
  mips.npc += 1;
}

void slti(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	// rt <- (rs < immediate)
	mips.registers[rt] = mips.registers[rs] < immediate ? 1 : 0;
	mips.npc += 1;
}
void sltiu(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
  uint32_t immediate_unsigned = static_cast<uint32_t>(immediate);
  mips.registers[rt] = (uint32_t(mips.registers[rs]) < immediate_unsigned) ? 1 : 0;
  mips.npc += 1;
}

void xori(MIPS& mips, uint32_t rs, uint32_t rt, int32_t immediate){
	mips.registers[rt] = (mips.registers[rs] ^ immediate);
  mips.npc += 1;
}

// Memory load functions

void lbu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){

	uint32_t address = static_cast<uint32_t>(offset + mips.registers[base]);
	// check 
	canRead(static_cast<int>(address/4));

	if((address/4) == ADDR_GETC_OFFSET){
		if((address % 4) != 3){
			std::cerr<<"LBU could not read memory location at address "<<address<<std::endl;
			std::exit(Exception::MEMORY);
		}else{
			char input = getInput();
			// EOF?
			if(input == -1){
				mips.registers[rt] = 0xFFFFFFFF;
				mips.npc += 1;
				return;
			}else{
				mips.registers[rt] = input & 0x000000FF;
				mips.npc += 1;
				return;
			}	
		}
	}


	switch(address % 4){
		case 0: mips.registers[rt] = ((mips.memory[address/4] & 0xFF000000) >> 24) & 0x000000FF;
				break;
		case 1: mips.registers[rt] = (mips.memory[address/4] & 0x00FF0000) >> 16;
				break;
		case 2: mips.registers[rt] = (mips.memory[address/4] & 0x0000FF00) >> 8;
				break;
		case 3: mips.registers[rt] = (mips.memory[address/4] & 0x000000FF);
				break;
		default: break;
	}

	mips.npc += 1;
}

void lb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	
	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canRead(static_cast<int>(address/4));

	if((address/4) == ADDR_GETC_OFFSET){
		if((address % 4) != 3){
			std::cerr<<"LB could not read memory location at address "<<address<<std::endl;
			std::exit(Exception::MEMORY);
		}
		else{
			char input = getInput();
			// EOF?
			if(input == -1){
				mips.registers[rt] = 0xFFFFFFFF;
				mips.npc += 1;
				return;
			}
			else{
				mips.registers[rt] = input & 0x000000FF;
				mips.npc += 1;
				return;
			}
		}
	}	

	switch(address % 4){
		case 0: mips.registers[rt] = ((mips.memory[static_cast<int>(address/4)] & 0xFF000000) >> 24) & 0x000000FF;
				break;
		case 1: mips.registers[rt] = (mips.memory[static_cast<int>(address/4)] & 0x00FF0000) >> 16;
				break;
		case 2: mips.registers[rt] = (mips.memory[static_cast<int>(address/4)] & 0x0000FF00) >> 8;
				break;
		case 3: mips.registers[rt] = (mips.memory[static_cast<int>(address/4)] & 0x000000FF);
				break;
		default: break;
	}

	if(mips.registers[rt] >> 7 == 1){
		mips.registers[rt] = mips.registers[rt] | 0xFFFFFF00;
	}	

	mips.npc += 1;
}

void lhu(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){

	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canRead(static_cast<int>(address/4));

	if((address/4) == ADDR_GETC_OFFSET){
		if((address % 4) != 2){
			std::cerr<<"LHU could not read memory location at address "<<address<<std::endl;
			std::exit(Exception::MEMORY);
		}
		else{
			char input = getInput();
			// EOF?
			if(input == -1){
				mips.registers[rt] = 0xFFFFFFFF;
				mips.npc += 1;
				return;
			}
			else{
				mips.registers[rt] = input & 0x000000FF;
				mips.npc += 1;
				return;
			}
		}
	}

	if(address % 2 != 0){
		std::cerr<<"LHU could not read memory location at address "<<address<<std::endl;
		 std::exit(Exception::MEMORY);
	}
	else{
		switch(address % 4){
			case 0: mips.registers[rt] = ((mips.memory[static_cast<int>(address/4)] & 0xFFFF0000) >> 16) & 0x0000FFFF;
					break;
			case 2: mips.registers[rt] = (mips.memory[static_cast<int>(address/4)] & 0x0000FFFF);
					break;
		}
	}	
	mips.npc += 1;
}

void lh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){

	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canRead(static_cast<int>(address/4));

	if((address/4) == ADDR_GETC_OFFSET){
		if((address % 4) != 2){
			std::cerr<<"LH could not read memory location at address "<<address<<std::endl;
			std::exit(Exception::MEMORY);
		}
		else{
			char input = getInput();
			if(input == -1){
				mips.registers[rt] = 0xFFFFFFFF; //If we have EOF set rt to -1
				mips.npc += 1;
				return;
			}
			else{
				mips.registers[rt] = input & 0x000000FF;
				mips.npc += 1;
				return;
			}
		}
	}

	if(address % 2 != 0){
		std::cerr<<"LH could not read memory location at address "<<address<<std::endl;
		std::exit(Exception::MEMORY);
	}
	else{
		switch(address % 4){
			case 0: mips.registers[rt] = ((mips.memory[static_cast<int>(address/4)] & 0xFFFF0000) >> 16) & 0x0000FFFF;
					break;
			case 2: mips.registers[rt] = (mips.memory[static_cast<int>(address/4)] & 0x0000FFFF);
					break;
		}

		if((mips.registers[rt] >> 15) == 1){
			mips.registers[rt] = mips.registers[rt] | 0xFFFF0000;
		}
	}

	mips.npc += 1;
}

void lw(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canRead(static_cast<int>(address/4));
	if(address%4 != 0){
		std::cerr<<"LW could not read memory location at address "<<address<<std::endl;
		std::exit(Exception::MEMORY);
	}else{
		if(address / 4 == ADDR_GETC_OFFSET){
			char input = getInput();
			// EOF?
			if(input == -1){
				mips.registers[rt] = 0xFFFFFFFF;
				mips.npc += 1;
				return;
			}
			else{
				mips.registers[rt] = input & 0x000000FF;
				mips.npc += 1;
				return;
			}
		}else{
			mips.registers[rt] = mips.memory[address/4];
		}
	}
	mips.npc += 1;
}

void lwl(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	
	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canRead(address/4);

	uint32_t load(0);

	switch(address % 4){
		case 0:
				mips.registers[rt] = mips.memory[static_cast<int>(address / 4)];
				break;
		case 1:
				load = (mips.memory[static_cast<int>(address / 4)] & 0x00FFFFFF) << 8;
				mips.registers[rt] = ((mips.registers[rt] & 0x000000FF)| load);
				break;
		case 2:
				load = (mips.memory[static_cast<int>(address / 4)] & 0x0000FFFF) << 16;
				mips.registers[rt] = ((mips.registers[rt] & 0x0000FFFF)| load);
				break;
		case 3:
				load = (mips.memory[static_cast<int>(address / 4)] & 0x000000FF) << 24;
				mips.registers[rt] = ((mips.registers[rt] & 0x00FFFFFF)| load);
				break;
		default: break;
	}

	mips.npc += 1;

}

void lwr(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){

	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	uint32_t load(0);

	canRead(address/4);

	switch(address % 4){
		case 0:
				load = (((mips.memory[static_cast<int>(address/4)] & 0xFF000000) >> 24) & 0x000000FF);
				mips.registers[rt] = (mips.registers[rt] & 0xFFFFFF00) | load;
				break;
		case 1:
				load = (((mips.memory[static_cast<int>(address/4)] & 0xFFFF0000) >> 16) & 0x0000FFFF);
				mips.registers[rt] = (mips.registers[rt] & 0xFFFF0000) | load;
				break;
		case 2:
				load = (((mips.memory[static_cast<int>(address/4)] & 0xFFFFFF00) >> 8) & 0X00FFFFFF);
				mips.registers[rt] = (mips.registers[rt] & 0xFF000000) | load;
				break;
		case 3: mips.registers[rt] = mips.memory[static_cast<int>(address/4)];
				break;
		default: break;
	}

	mips.npc += 1;
}

// Memory store functions

void sb(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	
	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	uint32_t h_rt = static_cast<uint32_t>(mips.registers[rt] & 0x000000FF);
	uint32_t current_mem = mips.memory[address/4];
	canWrite(static_cast<uint32_t>(address/4));

	if((address / 4) == ADDR_PUTC_OFFSET){
		if((address % 4) != 3){
			// std::cerr<<"SB could not write memory location at address "<<address<<std::endl;
			// exit(Exception::MEMORY);
			printOutput(static_cast<char>(0x00000000));
			mips.npc += 1;
		}
		else{
			printOutput(static_cast<char>(0x000000FF & mips.registers[rt]));
			mips.npc += 1;
			return;
		}
	}

	switch(address % 4){
		case(0):
			mips.memory[address/4] = (current_mem & 0x00FFFFFF) + (h_rt << 24);
			break;
		case(1):
			mips.memory[address/4] = (current_mem & 0xFF00FFFF) + (h_rt << 16);
			break;
		case(2):
			mips.memory[address/4] = (current_mem & 0xFFFF00FF) + (h_rt << 8);
			break;
		case(3):
			mips.memory[address/4] = (current_mem & 0xFFFFFF00) + h_rt;
			break;
	}
	mips.npc += 1;

}

void sh(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){
	
	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canWrite(static_cast<uint32_t>(address/4));
	if((address/4) == ADDR_PUTC_OFFSET){
		if((address % 4) != 2){
			// std::cerr<<"SH could not write memory location at address "<<address<<std::endl;
			// std::exit(Exception::MEMORY);
			printOutput(static_cast<char>(0x00000000));
			mips.npc += 1;
		}
		else{
			printOutput(static_cast<char>(0x000000FF & mips.registers[rt]));
			mips.npc += 1;
			return;
		}
	}
	if(address % 2 != 0){
		std::cerr<<"SH could not write memory location at address "<<address<<std::endl;
		std::exit(Exception::MEMORY);
	}else{
		// address is divisible by 2. When dividing by 4, rest is either 0 (lower half) or 2 (upper half)
		// when storing, keep the other half and use half of rt
		uint32_t h_rt = static_cast<uint32_t>(mips.registers[rt] & 0x0000FFFF);
		uint32_t current_mem = mips.memory[address/4];
		switch(address % 4){
			case(0):
				mips.memory[address/4] = (current_mem & 0x0000FFFF) + (h_rt << 16);
				break;
			case(2):
				mips.memory[address/4] = (current_mem & 0xFFFF0000) + h_rt;
				break;
		}
	}
	mips.npc += 1;

}

void sw(MIPS& mips, uint32_t base, uint32_t rt, int32_t offset){

	uint32_t address = static_cast<uint32_t>(mips.registers[base] + offset);
	canWrite(static_cast<uint32_t>(address/4));
	if(address % 4 != 0){
		std::cerr<<"SW could not write memory location at address "<<address<<std::endl;
		std::exit(Exception::MEMORY);
	}
	else{
		if(address/4 == ADDR_PUTC_OFFSET){
			printOutput(static_cast<char>(0x000000FF & mips.registers[rt]));
		}else{
			mips.memory[address/4] = mips.registers[rt];
		}
		mips.memory[address/4] = mips.registers[rt];
	}

	mips.npc += 1;
	
}

// functions to check if the address is valid to read or write
void canRead(uint32_t address){
	if(((address < ADDR_INSTR_OFFSET) || (address > (ADDR_INSTR_OFFSET + ADDR_INSTR_SIZE - 1)))
		&& ((address < ADDR_DATA_OFFSET) || (address > (ADDR_DATA_OFFSET + ADDR_DATA_SIZE - 1)))
		&& (address != ADDR_GETC_OFFSET)){
			std::cerr<<"Could not read memory location at address "<<address<<std::endl;
			std::exit(Exception::MEMORY);
		}
}

void canWrite(uint32_t address){
	if(((address < ADDR_DATA_OFFSET || (address > (ADDR_DATA_OFFSET + ADDR_DATA_SIZE - 1)))) && (address != ADDR_PUTC_OFFSET)){
		std::cerr<<"Could not write memory location at address "<<address<<std::endl;
		std::exit(Exception::MEMORY);
	}
}

// functions to read and write a character
char getInput(){
	char input;
	input = std::getchar();

	// EOF case
	if(std::cin.eof()){
		return 0xFF;
	}

	// Could the console read?
	if(!std::cin.good()){
		std::cerr<<"IO could not read\n";
		std::exit(Error::IO);
	}
	return input;
}

void printOutput(char c_out){

	std::putchar(c_out);

	// Could the console write?
	if(!std::cout.good()){
		std::cerr<<"IO could not write\n";
		std::exit(Error::IO);
	}
}