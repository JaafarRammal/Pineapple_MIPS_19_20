# Pineapple_MIPS_19_20

## The project

We are required to build a MIPS simulator that follows the ISA specs for the MIPS I. We decided to use C++ to build the simulator and bash to build the testbench. **This project was built as part of a coursework following the guidlines in the file [guidlines.md](https://github.com/JaafarRammal/Pineapple_MIPS_19_20/blob/master/Guidlines.md)**

## The simulator

We have simplified as much as possible our simulator. We used different file imports for the different function types (R-I-J types). Inside each, the breakup of the decode of the instruction and the function call is important: this allows us to easily add new functionalities, enhance exceptions checking, or quickly spot an error in the simulator

## The testbench

Written in bash, the testbench script scans the tests folder and runs each binary on the simulator. For each test, a meta file contains the instruction type, the expected console output, the expected return, the cat input (if necessary), the author, and the test description. This allows us to build a CSV file following the coursework specs for the test results

## Used ressources

Working both on OS X, we would like to thank the authors of the open-source parser [(Link here)](https://github.com/QFSW/MIPS1-Simulator) which allowed us to convert our mips assembly tests to binary, therefore boosting the workflow
