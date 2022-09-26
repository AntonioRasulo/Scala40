#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <set>
#include<map>
#include<vector>
#include "Card.h"
#include "Decks.h"
#include "Player.h"
#include "PlayerState.h"
#include "ConcretePlayerState.h"


int main(){

/*	Scala40::Card c(1,"spades", "spadesA");
	Scala40::Card c1(1,"diamonds", "diamondsA");
	Scala40::Card c2(1,"diamonds", "diamondsA");
	
	if(c==c1)
		std::cout<<"c==c1\n";
	else
		std::cout<<"c!=c1\n";
	
	if(c2==c1)
		std::cout<<"c2==c1\n";
	else
		std::cout<<"c2!=c1\n";*/

	//enum identifier {START, GAME};

	//enum identifier state = START;
	
	//while(1){
		//switch(state){
			//case(START):
				std::string name_player1;
				std::cout<<"Type the name of the first player:\n";
				std::cin>>name_player1;
				std::string name_player2;
				std::cout<<"Type the name of the second player:\n";
				std::cin>>name_player2;
				int val;
				do{
					while(std::cout<<"Type 1 if "<< name_player1<<" has to start\nType 2 if "<<name_player2<<" has to start\n" && (!(std::cin>>val) || (val!=1 && val!=2) ) ){
						std::cin.clear();	//clear bad input flag
						std::cin.ignore();	//discard input
						std::cout<<"Invalid input; please re-enter\n";
					}
				}
				while(val!=1 && val!=2);
				if(val==1){
					Scala40::Player p1(name_player1,false,true);
					Scala40::Player p2(name_player2,false,false);
					p1.setOpponent(&p2);
					p2.setOpponent(&p1);
					p2.toggle();
					p1.toggle();
				}else if(val==2){
					Scala40::Player p1(name_player1,false,false);
					Scala40::Player p2(name_player2,false,true);
					p1.setOpponent(&p2);
					p2.setOpponent(&p1);
					p1.toggle();
					p2.toggle();
				}
				//state=GAME;
				//break;
			//case(GAME):
		
		//}
	//}

}