# Compiler
CXX = g++

# Executable name
TARGET = Tetris

# Compiler flags:
CPPFLAGS = -g -Wall -std=c++11 $(shell pkg-config --cflags sdl2)

# Linker flags and libraries:
# $(shell ...): Runs a shell command to get SDL2's required library paths and names (like -lSDL2)
LDLIBS = $(shell pkg-config --libs sdl2)

# Source files (.cpp)
SRCS = Main.cpp Game.cpp Board.cpp Pieces.cpp Graphics.cpp Timer.cpp

# Object files (.o), automatically generated from the source file list
OBJS = $(SRCS:.cpp=.o)

# --- Build Rules ---

# The default rule, 'all', is the first one.
# It depends on the target executable.
.PHONY: all
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDLIBS)
	@echo "Build complete. Run with ./$(TARGET)"

# Pattern rule to compile a .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# Rule to clean up build files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)