GXX=g++ -g

all:	drive.exe

clean:	
	rm *.o *.exe
#####################################################
drive.exe: drive.o TownList.o Town.o Town2.o
	$(GXX) drive.o TownList.o Town.o Town2.o -o drive.exe
#####################################################
drive.o: drive.cpp TownList.h Town.h Town2.h
	$(GXX) -c drive.cpp -o drive.o
	
Town2.o: Town2.cpp Town2.h
	$(GXX) -c Town2.cpp -o Town2.o	

Town.o: Town.cpp Town.h
	$(GXX) -c Town.cpp -o Town.o

TownList.o: TownList.cpp TownList.h
	$(GXX) -c TownList.cpp -o TownList.o

#####################################################
