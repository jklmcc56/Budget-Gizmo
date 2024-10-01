CPP = g++

CPPFLAGS = -Wall -Wextra -std=c++17 -Iinc

TARGET = test

SRC = $(wildcard src/*.cpp)

OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))

# Default target: clean and compile
build: clean $(TARGET)

# Compile the program
$(TARGET): $(OBJ)
	@$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJ)

# Compile each .cpp file to .o object files
obj/%.o: src/%.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
clean:
	@rm -f $(OBJ) $(TARGET)

# All rule: Clean, compile, and run the program
all: build
	@./$(TARGET)