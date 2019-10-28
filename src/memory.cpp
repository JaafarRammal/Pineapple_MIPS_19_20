#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <iostream>




// read from memory
int read_ADDR_INSTR(int index){
    return ADDR_INSTR[index];
}


uint32_t READ_MEMORY(){
// get user input by reading from this address in memory, ADDR_GETC
}

// write to data memory: takes in data and index in DATA_mem vector
void STORE_MEMORY(int data_in, int index){
    ADDR_DATA_OFFSET[index] = data_in;
}

//write instructions to INSTR memory: only used when loading binary
void Memory::load_ADDR_INSTR(int index, int number){
    // to write to executable memory
    ADDR_INSTR[index] = number;
}

