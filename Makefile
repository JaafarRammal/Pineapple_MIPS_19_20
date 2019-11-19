SRC_DIR = ./src
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
BIN_DIR = ./bin
TEST_DIR = ./test_bench

SIM_NAME = mips_simulator
TB_NAME = mips_testbench
SIM_OUT = $(BIN_DIR)/$(SIM_NAME)

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -O3 -mavx

simulator: $(SIM_OUT)
	 rm -rf $(OBJ_DIR)

$(SIM_OUT): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -I $(INCLUDE_DIR) $(CXXFLAGS) -c -o $@ $<

testbench:
	mkdir -p $(BIN_DIR)
	cp $(TEST_DIR)/$(TB_NAME).sh $(BIN_DIR)
	mv $(BIN_DIR)/$(TB_NAME).sh $(BIN_DIR)/$(TB_NAME)


clean:
	rm -rf $(BIN_DIR)