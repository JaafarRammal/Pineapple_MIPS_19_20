#ifndef MIPS_J_TYPE
#define MIPS_J_TYPE

#include "mips_init.hpp"

// Define all the J-type instructions
// These take in input by default a MIPS structure by reference that is modifiable to access common register and memory

// Define all the R-type instructions
// These take in input by default a MIPS structure by reference that is modifiable to access common register and memory

// main executor call

void j_type(MIPS& mips, bool& executed);

// r-type executions
// variables named based on the attached js helper for instructions

void j(MIPS& mips, uint32_t target);
void jal(MIPS& mips, uint32_t target);

#endif