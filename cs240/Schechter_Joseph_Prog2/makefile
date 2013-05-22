GXX=g++ -g

all: war.exe

clean:	
	rm -f *.o war.exe
#####################################################
war.exe: Player.o PlayingCard.o Game.o WordList.o WordListNode.o war.o
	$(GXX) Player.o PlayingCard.o Game.o WordList.o WordListNode.o war.o -o war.exe


######################################################

war.o: war.cpp
	$(GXX) -c war.cpp -o war.o

PlayingCard.o: PlayingCard.cpp PlayingCard.h
	$(GXX) -c PlayingCard.cpp -o PlayingCard.o

Player.o: Player.cpp Player.h
	$(GXX) -c Player.cpp -o Player.o
	
Game.o: Game.cpp Game.h
	$(GXX) -c Game.cpp -o Game.o
	
WordList.o: WordList.cpp WordList.h
	$(GXX) -c WordList.cpp -o WordList.o

WordListNode.o: WordListNode.cpp WordListNode.h
	$(GXX) -c WordListNode.cpp -o WordListNode.o

#######################################################
