# Specifiy the target
all: ssort

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
ssort: ssort.o
	g++  ssort.o -o ssort

# Specify how the object files should be created from source files
ssort.o: ssort.cpp
	g++ -c ssort.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o ssort

