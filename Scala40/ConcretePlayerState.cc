#include <iostream>
#include<map>
#include<vector>
#include<set>
#include<memory>
#include<stack>
#include "Card.h"
#include "Decks.h"
#include "Player.h"
#include "PlayerState.h"
#include "ConcretePlayerState.h"

namespace Scala40{

void Draw::enter(Player* player){
	
	std::cout<<"It's "<<player->getName()<<" turn\n";
	
	if(player->getOpenedTheGame()){	//choose if draw from heel or well
		int choice;
		do{
			std::cout<<"Press 1 to draw a card from heel\n";
			std::cout<<"Press 2 to draw a card from well\n";
			std::cout<<"Press 3 to see the top card of well\n";
			std::cout<<"Press 4 to show your cards\n";
			std::cout<<"Press 5 to see the cards on the table\n";
			std::cin>>choice;
			switch(choice){
				case 1:
					player->DrawCard(Decks::Get()->DrawCardHeel());
					
					if(Decks::Get()->getHeelIsEmpty()){	//If draw last card of the heel
						Decks::Get()->shuffleWell();	//Shuffle the well
						Decks::Get()->swapDecks();		//Swap hell and well
					}
						
					break;
				case 2:
					player->DrawCard(Decks::Get()->DrawCardWell());
					break;	
				case 3:
					Decks::Get()->printTopWell();
					break;
				case 4:
					player->printHandCard();
					break;
				case 5:
					if (Player::isPlayedCardMapEmpty())
						std::cout<<"There are no card on the table\n";
					else
						Player::printPlayedCardMap();
					break;
				default:
					std::cout<<"Not valid choice typed\n";
					break;
			}
		}while(choice!=1 && choice != 2);
	}else{	//draw from heel
		player->DrawCard(Decks::Get()->DrawCardHeel());
	}
	player->toggle();
}

void Draw::toggle(Player* player, std::string state){

	player->setState(Processing::getInstance());

}

PlayerState& Draw::getInstance(){
	
	static Draw singleton;
	return singleton;
	
}

void Processing::enter(Player* player){
	int choice;
	bool exit=false;
	player->resetPlayedValue();
	do{
		std::cout<<"Press 1 to put a game on the table\n";
		std::cout<<"Press 2 to add a card to a game on the table\n";
		std::cout<<"Press 3 to take a Joker from a game on the table\n";
		std::cout<<"Press 4 to discard a card and end your turn\n";
		std::cout<<"Press 5 to show your cards\n";
		std::cout<<"Press 6 to show the cards on the table\n";
		std::cin>>choice;
		switch(choice){
			case 1:
				player->playGame();
				break;
			case 2:
				if(player->getOpenedTheGame()){
					if (Player::isPlayedCardMapEmpty())
						std::cout<<"There are no card on the table\n";
					else
						player->playSingleCard();
				}else{
					
					std::cout<<"You can't add card in a game on the table if you haven't opened the game\n";
					
				}
				break;
			case 3:
				player->getJoker();
				break;
			case 4:
				if(!(player->getOpenedTheGame()) && player->getPlayedValue()>0 && player->getPlayedValue()<40){
				//if(!(player->getOpenedTheGame())){
					std::cout<<"The sum of the cards you played are less than 40\n";
					std::cout<<"getPlayedValue: "<<player->getPlayedValue()<<std::endl;
					while(std::cout<<"Press 1 to remove the cards you played from the table\nPress 2 to choose other cards\n" && (!(std::cin>>choice) || (choice!=1 && choice!=2) ) ){
						std::cin.clear();	//clear bad input flag
						std::cin.ignore();	//discard input
						std::cout<<"Invalid input; please re-enter\n";
					}
					switch(choice){
						case 1:
							//Chiamare metodo che rimuove gli ultimi set inseriti dalle carte sul tavolo e reinserire le carte in mano al giocatore
							//Per ogni carta (set) che viene messo in mano decrementare player_value
							player->fromTableToHand();
							break;
						
						case 2:
							//Nothing to do
							break;
							
						default:
							std::cout<<"Not available value\n";
							break;
					}
				}else
					exit=player->discardCard();
				break;
			case 5:
				player->printHandCard();
				break;
			case 6:
				if (Player::isPlayedCardMapEmpty())
					std::cout<<"There are no card on the table\n";
				else
					Player::printPlayedCardMap();
				break;
			default:
				std::cout<<"Not valid choice typed\n";
				break;
		}
		
	}while(!exit);
	player->toggle();
}

void Processing::toggle(Player* player, std::string state){
	
	if(player->getHandCardVecEmpty())
		player->setState(Win::getInstance());
	else{
		player->setState(Idle::getInstance());
		player->Notify("Idle");	//Notify to the opponent to start the turn
	}
}

PlayerState& Processing::getInstance(){
	
	static Processing singleton;
	return singleton;

}

void Idle::enter(Player* player){

	//player->Notify("Idle");	//Notify to the opponent to start the turn

}

void Idle::toggle(Player* player, std::string state){

	if(state=="Idle")
		player->setState(Draw::getInstance());
	else if(state=="Win")
		player->setState(Reset::getInstance());
}

PlayerState& Idle::getInstance(){
	
	static Idle singleton;
	return singleton;

}

void Win::enter(Player* player){

	std::cout<<"Player "<<player->getName()<<" won\n";
	std::cout<<"Player "<<(player->getOpponent())->getName()<<" lost\n";
	player->Notify("Win");	//Notify to the opponent that he lost
}

void Win::toggle(Player* player, std::string state){

	player->setState(Reset::getInstance());

}

PlayerState& Win::getInstance(){

	static Win singleton;
	return singleton;

}

void Reset::enter(Player* player){

	for(int i=0; i<13; i++)
		player->DrawCard(Decks::Get()->DrawCardHeel());	//At the beginning, the player draw 13 cards
	
	player->printHandCard();

}

void Reset::toggle(Player* player, std::string state){

	if(player->getStart())
		player->setState(Draw::getInstance());
	else
		player->setState(Idle::getInstance());

}

PlayerState& Reset::getInstance(){

	static Reset singleton;
	return singleton;

}

}