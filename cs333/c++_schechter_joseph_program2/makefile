# Specifiy the target
all: multi-heap

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
multi-heap: multi-heap.o
	g++  multi-heap.o -o multi-heap

# Specify how the object files should be created from source files
multi-heap.o: multi-heap.cpp
	g++ -c multi-heap.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o multi-heap

