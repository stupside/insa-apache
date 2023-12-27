# Directory structure
SRC_DIR := src

BUILD_DIR := .build
BUILD_DIR_OBJ := $(BUILD_DIR)/obj
BUILD_DIR_OBJ_DEBUG := $(BUILD_DIR)/obj_debug

BIN_OUTPUT := $(BUILD_DIR)/analog
BIN_OUTPUT_DEBUG := $(BUILD_DIR)/analog_debug

# Compiler and flags
CXX := g++
CXXFLAGS := -ansi -pedantic -Wall -std=c++11

MAIN := main

# Sources
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
SOURCES_MAIN := $(MAIN).cpp 

# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_OBJ)/%.o,$(SOURCES))
OBJECTS_DEBUG := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_OBJ_DEBUG)/%_debug.o,$(SOURCES))

# Build
$(BUILD_DIR_OBJ)/%.o: $(SRC_DIR)/%.cpp pre_build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build main
$(BUILD_DIR_OBJ)/$(MAIN).o: $(SOURCES_MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build for debug
$(BUILD_DIR_OBJ_DEBUG)/%_debug.o: $(SRC_DIR)/%.cpp pre_build
	$(CXX) $(CXXFLAGS) -DDEBUG -c $< -o $@

# Build main for debug
$(BUILD_DIR_OBJ_DEBUG)/$(MAIN)_debug.o: $(SOURCES_MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking
$(BIN_OUTPUT): $(OBJECTS) $(BUILD_DIR_OBJ)/$(MAIN).o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Linking for debug build
$(BIN_OUTPUT_DEBUG): $(OBJECTS_DEBUG) $(BUILD_DIR_OBJ_DEBUG)/$(MAIN)_debug.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Create build directories
pre_build:
	mkdir -p $(BUILD_DIR_OBJ)
	mkdir -p $(BUILD_DIR_OBJ_DEBUG)

# Build targets
build: $(BIN_OUTPUT)
debug: $(BIN_OUTPUT_DEBUG)

run: build
	./$(BIN_OUTPUT) ./samples/medium.log

dev: debug
	./$(BIN_OUTPUT_DEBUG) ./samples/medium.log

val: build
	valgrind --leak-check=yes ./$(BIN_OUTPUT) ./samples/medium.log

test: build
	cd tests; ./mktest.sh

clean:
	rm -rf $(BUILD_DIR)