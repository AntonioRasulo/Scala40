CC=g++ -g #compiler
LD=g++ -g #linker

#Compile object
Card.o:	Card.cc Card.h
				${CC} -c Card.cc

Decks.o:	Decks.cc Decks.h
				${CC} -c Decks.cc

Player.o:	Player.cc Player.h
				${CC} -c Player.cc

ConcretePlayerState.o:	ConcretePlayerState.cc ConcretePlayerState.h
				${CC} -c ConcretePlayerState.cc

main.o:	main.cpp
		${CC} -c main.cpp
		
#Project linking
main:	Card.o Decks.o Player.o ConcretePlayerState.o main.o
		${LD} -o main Card.o Decks.o Player.o ConcretePlayerState.o main.o
		
#delete all the compiled file
clean:
		rm -f *.o main