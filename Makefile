CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude

SRC    = src/main.cpp src/Graph.cpp src/BFS.cpp src/Dijkstra.cpp
OBJ    = $(SRC:.cpp=.o)
TARGET = metro_planner.exe

# Build target depends on clean first, so .o files are always removed before recompile
.PHONY: all clean rebuild run

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	@echo ">>> Build complete: $(TARGET)"

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(TARGET)
	@echo ">>> Cleaned old object files and binary"

rebuild: clean all

run: all
	./$(TARGET) tests/metro_network.csv