# Specifiy the target
all: huffman

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
huffman: huffman.o
	g++  huffman.o -o huffman

# Specify how the object files should be created from source files
huffman.o: huffman.cpp
	g++ -c huffman.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o huffman

