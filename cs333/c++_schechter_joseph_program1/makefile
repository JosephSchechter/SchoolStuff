# Specifiy the target
all: risort llmergesort

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
risort: risort.o
	g++  risort.o  -o risort.exe
	
	
llmergesort: llmergesort.o List.o
	g++  llmergesort.o List.o -o llmergesort.exe

# Specify how the object files should be created from source files
risort.o: risort.cpp
	g++ -c risort.cpp

	
llmergesort.o: llmergesort.cpp List.h
	g++ -c llmergesort.cpp
	
	
# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o risort.exe
	rm -f *.o llmergesort.exe

