# This README File is to let you know a couple of things.

### Note: The Question 2 (Radiix Sort) is done for both numbers and alphabets (using string), that is why there are 2 files for Question 2.

### Note: The README File along with the devalopment environment and the Static SFML Libaries are given in Releases (only for Question 1).

__The MakeFile is as follows:__
```
# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 #-Wall -Wextra -pedantic -g

# SFML include and library directories
SFML_INCLUDE := -I "Add your own path here is comments"
SFML_LIB := -L "Add your own path here in comments"

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
```
