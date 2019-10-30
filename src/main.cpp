#include <iostream>
#include <string>
#include <cstdint>

#include "mips_all.hpp"

using namespace std;

int main(int argc, char* argv[]){

	// check for binary input
	if(argc < 2){
		std::cerr << "Error: Expected binary file input" << std::endl;
		return 2; // what exit code should we use here?
	}

	// create and initialize a mips
	MIPS mips;
	init_mips(mips);
	importBitFile(mips, argv[1]);

	return 0;

}
