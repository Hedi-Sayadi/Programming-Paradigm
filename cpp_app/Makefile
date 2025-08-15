# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Basic version source files
BASIC_SOURCES = main.cpp patient.cpp patient_manager.cpp diagnosis.cpp
BASIC_OBJECTS = $(BASIC_SOURCES:%.cpp=$(OBJ_DIR)/%.o)
BASIC_TARGET = $(BIN_DIR)/medicheck_basic

# Enhanced version source files
ENHANCED_SOURCES = enhanced_main.cpp enhanced_patient.cpp patient_manager.cpp diagnosis.cpp
ENHANCED_OBJECTS = $(ENHANCED_SOURCES:%.cpp=$(OBJ_DIR)/%.o)
ENHANCED_TARGET = $(BIN_DIR)/medicheck_enhanced

# Default target - build enhanced version
all: enhanced

# Basic version
basic: $(BASIC_TARGET)

# Enhanced version (default)
enhanced: $(ENHANCED_TARGET)

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link basic executable
$(BASIC_TARGET): $(BASIC_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(BASIC_OBJECTS) -o $@
	@echo "Basic MediCheck built successfully!"

# Link enhanced executable
$(ENHANCED_TARGET): $(ENHANCED_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(ENHANCED_OBJECTS) -o $@
	@echo "Enhanced MediCheck built successfully!"

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the basic application
run-basic: basic
	./$(BASIC_TARGET)

# Run the enhanced application
run: enhanced
	./$(ENHANCED_TARGET)

run-enhanced: enhanced
	./$(ENHANCED_TARGET)

# Debug builds
debug-basic: CXXFLAGS += -g -DDEBUG
debug-basic: basic

debug-enhanced: CXXFLAGS += -g -DDEBUG
debug-enhanced: enhanced

debug: debug-enhanced

# Install enhanced version (copy to a system directory)
install: enhanced
	cp $(ENHANCED_TARGET) /usr/local/bin/medicheck
	@echo "MediCheck Enhanced installed to /usr/local/bin/medicheck"

# Uninstall
uninstall:
	rm -f /usr/local/bin/medicheck

# Build both versions
both: basic enhanced

# Help target
help:
	@echo "MediCheck Build System"
	@echo "====================="
	@echo "Targets:"
	@echo "  enhanced (default) - Build enhanced version with advanced features"
	@echo "  basic              - Build basic version"
	@echo "  both               - Build both versions"
	@echo "  run                - Build and run enhanced version"
	@echo "  run-enhanced       - Build and run enhanced version"
	@echo "  run-basic          - Build and run basic version"
	@echo "  debug              - Build enhanced version with debug info"
	@echo "  debug-enhanced     - Build enhanced version with debug info"
	@echo "  debug-basic        - Build basic version with debug info"
	@echo "  install            - Install enhanced version system-wide"
	@echo "  clean              - Remove all build files"
	@echo "  help               - Show this help message"

.PHONY: all basic enhanced clean run run-basic run-enhanced debug debug-basic debug-enhanced install uninstall both help
