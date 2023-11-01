# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 #-Wall -Wextra -pedantic -g

# SFML include and library directories
SFML_INCLUDE := -I "C:\Users\Digitify\Downloads\SFML-2.6.0\include"
SFML_LIB := -L "C:\Users\Digitify\Downloads\SFML-2.6.0\build\lib"

# SFML libraries (static versions)
# SFML_LIBS := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-system-s -lsfml-audio-s
SFML_LIBS := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype -lopengl32 -lwinmm -lgdi32 -lsfml-system-s -lsfml-audio-s


# Source file
SOURCE := main.cpp

# Executable name
TARGET := main

# Default target
all: $(TARGET)

# Compile and link the program
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -o $(TARGET) $(SOURCE) $(SFML_LIB) $(SFML_LIBS) -DSFML_STATIC

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up object files and the executable
clean:
	rm -f $(TARGET)

.PHONY: all run clean
.PHONY: rebuild
rebuild: clean all

# Debug target
debug: CXXFLAGS += -DDEBUG -g
debug: rebuild