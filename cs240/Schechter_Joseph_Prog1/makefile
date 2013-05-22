
# Specifiy the target
all: Hoops

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
Hoops: Conference.o Player.o Team.o Hoops.o
	g++  Conference.o Player.o Team.o Hoops.o -o Hoops.exe

# Specify how the object files should be created from source files
Conference.o: Conference.cpp Conference.h
	g++ -c Conference.cpp
	
Player.o: Player.cpp Player.h
	g++ -c Player.cpp

Team.o: Team.cpp Team.h
	g++ -c Team.cpp

Hoops.o: Hoops.cpp Player.h Team.h Conference.h
	g++ -c Hoops.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o Hoops.exe
