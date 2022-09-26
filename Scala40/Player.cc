#include<vector>
#include<map>
#include<algorithm>
#include<memory>
#include<stack>
#include<set>
#include<iostream>
#include<iterator>
#include "Card.h"
#include "Decks.h"
#include "Player.h"
#include "PlayerState.h"
#include "ConcretePlayerState.h"

namespace Scala40{
	
Player::Player(const std::string& name_, const bool& IsComputer_, const bool& start_){

	name=name_;
	IsComputer = IsComputer_;
	OpenedTheGame = false;
	start=start_;
	played_value=0;
	setState(Reset::getInstance());
}

void Player::setOpenedTheGame(){

	OpenedTheGame = true;

}

PlayerState* Player::getCurrentState() const{

	return currentState;

}

std::string Player::getName() const{
	
	return name;
	
}

void Player::toggle(std::string state){

	if(state=="Win"|| state=="Idle")
		currentState->toggle(this,state);
	else
		currentState->toggle(this);

}

void Player::setState(PlayerState& newState){
	
	//currentState->exit(this);
	currentState = &newState;
	currentState->enter(this);
	
}

//Set opponent
void Player::setOpponent(Player* opponent_){
	opponent = opponent_;
}

//To play a game on the table
void Player::playGame(){
	
	int choose;
	printHandCard();
	//PlayedCardType tmpMap;
	//std::set<std::shared_ptr<Card>> tmpSet;
	std::multiset<std::shared_ptr<Card>> tmpSet;
	bool goodGame=false;
	bool exit=false;
	bool checkValue = false;
	do{
		std::string symbol;
		std::cout<<"Type 1 to choose a card to play.\n";
		std::cout<<"Type 2 to stop to choose cards.\n";
		std::cout<<"Type 3 to remove a card you have chosen\n";
		std::cout<<"Type 4 to print on screen the cards you have chosen\n";
		std::cout<<"Type: \n";
		std::cin>>choose;
		
		switch(choose){
			
			case 1:
				std::cout<<"Which card you want to play?\n";
				std::cout<<"Index: Symbol"<<std::endl;
				for(int i=0; i<HandCardVec.size(); i++){
					if(HandCardVec[i]->getIsJoker())
						std::cout<<i<<": Joker"<<std::endl;
					else
						std::cout<<i<<": "<<HandCardVec[i]->getSymbol()<<std::endl;
				}
				int index;
				std::cout<<"Type index:\n";
				std::cin>>index;
				
				if(index < HandCardVec.size() && index >=0){
					//If the player choose a Joker
					IfPlayerChooseJoker(index);
				
					std::set<std::shared_ptr<Card>>::iterator it = tmpSet.begin();
				
					if(tmpSet.empty()){	//If is empty insert
						//Add the card in the temporary set
						tmpSet.emplace(std::make_shared<Card> (*(HandCardVec[index])));
						HandCardIter iterTmpHand = HandCardVec.begin();
						//Erase the card from the hand of the player
						HandCardVec.erase(iterTmpHand+index);
					}else{
						//if((tmpSet.find(HandCardVec[index]))==(tmpSet.end())){	//if the card is not already present
						if(std::find(tmpSet.begin(), tmpSet.end(), HandCardVec[index]) == tmpSet.end()){
							std::cout<<"Entrato primo if\n";
							if((*it)->getSuit() == HandCardVec[index]->getSuit()){	//If have the same suit of the first element
								std::cout<<"Entrato secondo if\n";
								//Add the card in the temporary set
								tmpSet.emplace(std::make_shared<Card> (*(HandCardVec[index])));
								//if((tmpSet.emplace(std::make_shared<Card> (*(HandCardVec[index])))).second == false)
								//	std::cout<<"Element not inserted\n";
								HandCardIter iterTmpHand = HandCardVec.begin();
								//Erase the card from the hand of the player
								HandCardVec.erase(iterTmpHand+index);
								checkValue=true;
							}else if(!checkValue){
								std::cout<<"Entrato terzo if\n";
								if((((*it)->getValue() == HandCardVec[index]->getValue()) || (((*it)->getValue() ==11) && HandCardVec[index]->getValue() ==1) ) && ((*it)->getSuit() != HandCardVec[index]->getSuit())){	//If have not the same suit but have the same value
								std::cout<<"Entrato quarto if\n";
									//If it's an Ace
									if(HandCardVec[index]->getValue() == 1){
										HandCardVec[index]->setValue(11);
										if(tmpSet.size()==1){	//so set the value of the first inserted ACE at 11
											
											std::multiset<std::shared_ptr<Card>>::iterator it = tmpSet.begin();
											(*it)->setValue(11);
											
										}
									}
									//Add the card in the temporary set
									tmpSet.emplace(std::make_shared<Card> (*(HandCardVec[index])));
									//if(tmpSet.emplace(std::make_shared<Card> (*(HandCardVec[index]))).second==false)
									//	std::cout<<"Elemento non inserito\n";
									//else
									//	std::cout<<"elemento inserito\n";
									HandCardIter iterTmpHand = HandCardVec.begin();
									//Erase the card from the hand of the player
									HandCardVec.erase(iterTmpHand+index);
								}else{
									std::cout<<"It's not possible to insert this card\n";
								}
							}
						}else{
							std::cout<<"You cannot play the same card in one game\n";
							std::cout<<"Symbol of the card you played: "<<HandCardVec[index]->getSymbol()<<std::endl;
							std::cout<<"Symbol of the card finded at line 114: "<<(*(tmpSet.find(HandCardVec[index])))->getSymbol()<<std::endl;
							if(HandCardVec[index] == *(tmpSet.find(HandCardVec[index])))
								std::cout<<"They are equals\n";
							else
								std::cout<<"They are differents\n";
						}
					}
				}else{
					std::cout<<"Typed not valid index: "<<index<<std::endl;
				}
				
				break;
			case 2:
					goodGame=true;
					exit=true;
					if(tmpSet.size()<3){
						std::cout<<"You can't play less than 3 cards\n";
						goodGame=false;
					}else if(tmpSet.size()>14){
						std::cout<<"You can't play more than 14 cards\n";
						goodGame=false;
					}else if(checkValue){

						int expected=0;
						int calculated=0;

						if(tmpSet.size()==14){	//in case Joker A 2 3 4 5 6 7 8 9 10 J Q K
							expected = 96;
							std::set<std::shared_ptr<Card>>::reverse_iterator rev_iter = tmpSet.rbegin();
							
							if(!((*rev_iter)->getIsJoker())){	//If the last element is different from Joker means that the player had choose Joker as Ace

								std::set<std::shared_ptr<Card>>::iterator fe = tmpSet.begin();
								if((*fe)->getIsJoker()){
									fe++;
								} //If the first element is Joker, means that the second element is Ace. Otherwise if the first element is not Joker means that is Ace

								(*fe)->setValue(11);

							}

						}else{

							std::set<std::shared_ptr<Card>>::const_reverse_iterator last_el = tmpSet.crbegin();
							std::set<std::shared_ptr<Card>>::iterator first_el = tmpSet.begin();
							if(((*last_el)->getSymbol()).back()=='K' && ((*first_el)->getSymbol()).back() == 'A'){	//If AJQK for example
								(*first_el)->setValue(11);
							}
							
							int tmpValue = (*first_el)->getValue();	//Acquire value of the first element
							
							std::cout<<"Last element: "<<(*last_el)->getSymbol()<<std::endl;
							
							if(tmpSet.size()<=4 && (((*last_el)->getSymbol()).back() == 'A')  ){
								switch(tmpSet.size()){
									case 4:
										expected = 41;
										break;
										
									case 3:
										expected = 31;
										break;
									
									default:
										std::cout<<"Error\n";
										break;
								}
							}else{
								for(int i=0; i<tmpSet.size(); i++){
									if((tmpValue+i) == 11 || (tmpValue+i) == 12 || (tmpValue+i)==13){
										expected+=10;
									}else if((tmpValue+i) == 14){
										expected+=11;
									}else{
										expected+=tmpValue+i;
									}
								}
							}
						}

						std::set<std::shared_ptr<Card>>::iterator iterbegin = tmpSet.begin();

						for(; iterbegin!=tmpSet.end(); iterbegin++)
							calculated+=(*iterbegin)->getValue();

						if(calculated!=expected){
							std::cout<<"You can't play this set of cards\n";
							std::cout<<"calculated: "<<calculated<<std::endl;
							std::cout<<"expected: "<<expected<<std::endl;
							goodGame=false;
						}

						/*std::set<std::shared_ptr<Card>>::iterator iter = tmpSet.begin();
						int expected = 0;
						int calculated = 0;
						int tmpValue = (*iter)->getValue();
						
						for(int i=0; i<tmpSet.size(); i++){
							if((tmpValue+i) == 11 || (tmpValue+i) == 12 || (tmpValue+i)==13){
								expected+=10;
							}else if((tmpValue+i) == 14){
								expected+=11;
							}else{
								expected+=tmpValue+i;
							}
						}

						//The set is ordered by value, and initially the Ace has value "1"
						//So if the game is for example JQKA, at this point the Set contains
						//AJQK, so the value of A must be changed.
						if(tmpSet.size()==14){	//in case Joker(value=1) Joker 2 3 4 5 6 7 8 9 10 J Q K A
							
							std::set<std::shared_ptr<Card>>::iterator fe = tmpSet.begin();
							
							if((*fe)->getIsJoker()){
								fe++;
							}
							
							(*fe)->setValue(11);
							
						}else{	//If AJQK for example
							std::set<std::shared_ptr<Card>>::const_reverse_iterator last_el = tmpSet.crbegin();
							std::set<std::shared_ptr<Card>>::iterator first_el = tmpSet.begin();
							if(((*last_el)->getSymbol()).back()=='K' && ((*first_el)->getSymbol()).back() == 'A'){
								(*first_el)->setValue(11);
							}
						}
						
						for(; iter!=tmpSet.end(); iter++)
							calculated+=(*iter)->getValue();

						if(calculated!=expected){
							std::cout<<"You can't play this set of cards\n";
							goodGame=false;
						}*/
					}else if(HandCardVec.empty()){
						goodGame=false;
						std::cout<<"The player cannot remain without card in the hand\n";
						//Re-insert the card in the hand
						std::set<std::shared_ptr<Card>>::iterator iter=tmpSet.begin();
						for(; iter!=tmpSet.end(); iter++){

							if((*iter)->getIsJoker()){	//The card is a Joker
								HandCardVec.emplace_back(std::make_shared<Card> (25,"","Joker",true));
							}else if((*iter)->getValue()==11){	//The card is an Ace with value == 11
								HandCardVec.emplace_back(std::make_shared<Card> (1,(*iter)->getSuit(),(*iter)->getSymbol(),false));
							}else{	//All the other cases
								HandCardVec.emplace_back(std::make_shared<Card> (*(*iter)));
							}
							sort(HandCardVec.begin(), HandCardVec.end());
						}
						tmpSet.clear();
					}
					
					//If the player had not opened the game (and if the combination/sequence of card he played are good)
					//check if the value of the card he played are >40
					//if(goodGame && !OpenedTheGame){
					if(goodGame){
						int calc=0;
						
						std::set<std::shared_ptr<Card>>::const_iterator i = tmpSet.cbegin();
						for(; i != tmpSet.cend(); i++){
							calc+=(*i)->getValue();
						}
						
						played_value+=calc;	//Increase played_value
						
						std::cout<<"played_value increased: "<<played_value<<std::endl;
						
						if(played_value>=40 && !OpenedTheGame)
							OpenedTheGame=true;
						
						//if(calc>=40)
						//if(calc>=40 && !OpenedTheGame)
						//	OpenedTheGame = true;
						//else{
						//	std::cout<<"The value of the card you played are less then 40 and you still haven't opened the game\n";
						//	goodGame=false;
						//}
					}
					
				break;
				
			case 3:{
				std::cout<<"Which card you want to remove?\n";
				std::cout<<"Index: Symbol"<<std::endl;
				std::set<std::shared_ptr<Card>>::iterator iter=tmpSet.begin();
				for(int i=0; iter!=tmpSet.end(); i++, iter++){
					if((*iter)->getIsJoker())
						std::cout<<i<<": Joker"<<std::endl;
					else
						std::cout<<i<<": "<< (*iter)->getSymbol() <<std::endl;
				}
				std::cout<<"Type index:\n";
				std::cin>>index;
				
				if(!(index<0 || index>=tmpSet.size())){
				
					iter=tmpSet.begin();
					std::advance(iter, index);	//Increase the iterator of index position
					
					if((*iter)->getIsJoker()){	//The card is a Joker
						HandCardVec.emplace_back(std::make_shared<Card> (25,"","Joker",true));
					}else if((*iter)->getValue()==11){	//The card is an Ace with value == 11
						HandCardVec.emplace_back(std::make_shared<Card> (1,(*iter)->getSuit(),(*iter)->getSymbol(),false));
					}else{	//All the other cases
						HandCardVec.emplace_back(std::make_shared<Card> (*(*iter)));
					}
					sort(HandCardVec.begin(), HandCardVec.end());
					tmpSet.erase(iter);
				}else{
					
					std::cout<<"Typed not valid choice\n";
					
				}
				
				break;
			}
			case 4:{
				if(tmpSet.size()==0){
					
					std::cout<<"You haven't choose any card\n";
					
				}else{
				
					std::set<std::shared_ptr<Card>>::iterator iter4=tmpSet.begin();
					for(; iter4!=tmpSet.end(); iter4++){
						if((*iter4)->getIsJoker())
							std::cout<<"Joker"<<std::endl;
						else
							std::cout<<(*iter4)->getSymbol()<<std::endl;
					}
				}
				
				break;
			}
			default:
				std::cout<<"No valid choice\n";
				break;
		}
		
	}while(!exit);
	
	//If the player have choosen cards that are not valid but exit
	//re-insert the choosen card in the hand
	if(!goodGame){

		std::set<std::shared_ptr<Card>>::iterator iter=tmpSet.begin();
		for(; iter!=tmpSet.end(); iter++){

			if((*iter)->getIsJoker()){	//The card is a Joker
				HandCardVec.emplace_back(std::make_shared<Card> (25,"","Joker",true));
			}else if((*iter)->getValue()==11){	//The card is an Ace with value == 11
				HandCardVec.emplace_back(std::make_shared<Card> (1,(*iter)->getSuit(),(*iter)->getSymbol(),false));
			}else{	//All the other cases
				HandCardVec.emplace_back(std::make_shared<Card> (*(*iter)));
			}
		}
		sort(HandCardVec.begin(), HandCardVec.end());
		tmpSet.clear();
		
		//Put the game on the table
	}else if(goodGame){
		
		PlayedCardMap[PlayedCardMap.size()] = tmpSet;

		tmpSet.clear();

	}
	
}

//To print the HandCardVec on screen
void Player::printHandCard(){

	std::cout<<"Card in your hand"<<std::endl;
	HandCardConstIter iter= HandCardVec.begin();
	for(; iter!= HandCardVec.end(); iter++){

		if((*iter)->getIsJoker())
			std::cout<<"Joker"<<std::endl;
		else
			std::cout<<(*iter)->getSymbol()<<std::endl;

	}
}

//To print PlayedCardMap
void Player::printPlayedCardMap(){

	std::cout<<"Game on the table"<<std::endl;
	std::cout<<"Index: Symbols"<<std::endl;
	PlayedCardConstIterType iter = PlayedCardMap.cbegin();
	for(; iter!=PlayedCardMap.cend(); iter++){
		std::set<std::shared_ptr<Card>>::const_iterator iterSet = (iter->second).cbegin();
		std::cout<<iter->first<<": ";
		for(; iterSet != (iter->second).cend(); iterSet++){
			if((*iterSet)->getIsJoker()){			
			//	std::set<std::shared_ptr<Card>>::iterator it= std::find_if((iter->second).begin(),(iter->second).end(), [](std::shared_ptr<Card> c){return c->getSymbol()!="Joker";});
			//	std::cout<<"Joker->("<<(*iterSet)->getSuit()<<(*it)->getValue()<<") ";
				std::cout<<"Joker->("<<(*iterSet)->getSymbol()<<") ";
			}else
				std::cout<<(*iterSet)->getSymbol()<<" ";
		}
		std::cout<<std::endl;
	}
}

//To insert a card on a game on the table
void Player::playSingleCard(){

	printPlayedCardMap();
	std::cout<<"Which card you want to insert in a game?\n";
	std::cout<<"Index: Symbol"<<std::endl;
	for(int i=0; i<HandCardVec.size(); i++){
		if(HandCardVec[i]->getIsJoker())
			std::cout<<i<<": Joker"<<std::endl;
		else
			std::cout<<i<<": "<<HandCardVec[i]->getSymbol()<<std::endl;
	}
	
	int index;
	std::cout<<"Type index of the card:\n";
	std::cin>>index;
	printPlayedCardMap();
	int set_index;
	std::cout<<"In which combination/sequence you want to insert the card?\n";
	std::cin>>set_index;
	
	if(index < HandCardVec.size() && index >=0 && set_index < PlayedCardMap.size() && set_index>=0){
		IfPlayerChooseJoker(index);
		
		std::set<std::shared_ptr<Card>>::iterator iterSet = PlayedCardMap[set_index].begin();
		
		if((*iterSet)->getValue() == (*(std::next(iterSet,1)))->getValue() &&
			(*iterSet)->getValue() == HandCardVec[index]->getValue() &&
			PlayedCardMap[set_index].size()==3){	//Add card to a combination

			bool check=true;
			for(; iterSet!=PlayedCardMap[set_index].end(); iterSet++){	//Check if the suit of the chosed card is already in the game
				if((*iterSet)->getSuit()==HandCardVec[index]->getSuit()){
					check=false;
					break;
				}
			}

			if(check){

				PlayedCardMap[set_index].emplace(std::make_shared<Card> (*(HandCardVec[index])));	//Insert the card in the game
				HandCardVec.erase(HandCardVec.begin()+index);	//Remove the card from the hand
			}
		}else if(HandCardVec[index]->getValue() == ((*iterSet)->getValue()-1)){	//If the card is part of the sequence

			PlayedCardMap[set_index].emplace(std::make_shared<Card> (*(HandCardVec[index])));	//Insert the card in the game
			HandCardVec.erase(HandCardVec.begin()+index);	//Remove the card from the and
		}else if((*(PlayedCardMap[set_index].crbegin()))->getValue()+1 == HandCardVec[index]->getValue()){	//If the card is part of the sequence

			PlayedCardMap[set_index].emplace(std::make_shared<Card> (*(HandCardVec[index])));	//Insert the card in the game
			HandCardVec.erase(HandCardVec.begin()+index);	//Remove the card from the and
		}else if((*iterSet)->getValue() == (*(std::next(iterSet,1)))->getValue() &&	//In the case of ACE
				(*iterSet)->getValue() == HandCardVec[index]->getValue()+10 &&
				PlayedCardMap[set_index].size()==3){

			bool check=true;
			for(; iterSet!=PlayedCardMap[set_index].end(); iterSet++){	//Check if the suit of the chosed card is already in the game
				if((*iterSet)->getSuit()==HandCardVec[index]->getSuit()){
					check=false;
					break;
				}
			}

			if(check){
				(*(HandCardVec.begin()+index))->setValue(11);	//Set the value of the inserted ACE to 11
				PlayedCardMap[set_index].emplace(std::make_shared<Card> (*(HandCardVec[index])));	//Insert the card in the game
				HandCardVec.erase(HandCardVec.begin()+index);	//Remove the card from the hand
			}

		}else{
			std::cout<<"The choiced card cannot be inserted in the choiced game\n"<<std::endl;
		}
	}else{
		std::cout<<"Typed not valid index"<<std::endl;
	}
	
}

bool Player::discardCard(){
	
	std::cout<<"Which card you want to discard?\n";
	std::cout<<"Index: Symbol"<<std::endl;
	for(int i=0; i<HandCardVec.size(); i++){
		if(HandCardVec[i]->getIsJoker())
			std::cout<<i<<": Joker"<<std::endl;
		else
			std::cout<<i<<": "<<HandCardVec[i]->getSymbol()<<std::endl;
	}
	
	int index;
	std::cout<<"Type index of the card:\n";
	std::cin>>index;

	if(index>=0 && index<HandCardVec.size()){
		
		Decks::Get()->DiscardCard(*HandCardVec[index]);	//push the card in the well
		HandCardVec.erase(HandCardVec.begin()+index);		//erase card from the hand
		return true;
		
	}else{
		
		std::cout<<"Typed not valid index"<<std::endl;
		return false;
		
	}

}

//Return true if HandCardVec if empty, false otherwise
bool Player::getHandCardVecEmpty(){

	return HandCardVec.empty();

}

void Player::IfPlayerChooseJoker(const int& index){

	if(HandCardVec[index]->getIsJoker()){
		bool valid=false;
		std::string suit;
		do{
			std::cout<<"Choose the suit of the Joker (hearts, clubs, diamonds, spades):\n";
			std::cin>>suit;
			if(suit!="hearts" && suit !="clubs" && suit!="diamonds" && suit!= "spades")
				std::cout<<"Invalid suit: "<<suit<<std::endl;
							
		}while(suit!="hearts" && suit !="clubs" && suit!="diamonds" && suit!= "spades");
						
		do{
			std::string value;
			do{
				while(std::cout<<"Choose the value of the Joker(1-10,J,Q,K,11):\n" && ( !(std::cin>>value) || value!="1" && value!="2" && value!="3" && value!="4" && value!="5" && value!="6" && value!="7" && value!="8" && value!="9" && value!="10" && value!="J" && value!="Q" && value!="K" && value!="11" )){
					std::cin.clear();	//clear bad input flag
					std::cin.ignore();	//discard input
					std::cout<<"Invalid input; please re-enter\n";
				}
			}while(value!="1" && value!="2" && value!="3" && value!="4" && value!="5" && value!="6" && value!="7" && value!="8" && value!="9" && value!="10" && value!="J" && value!="Q" && value!="K" && value!="11");
			//std::cout<<"Choose the value of the Joker(1-10,J,Q,K,11):\n";
			//std::cin>>value;
			int associated_integer = ObtainInteger(value);
			switch(associated_integer){
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
					HandCardVec[index]->setSuit(suit);
					HandCardVec[index]->setValue(associated_integer);
					if(value == "11" || value == "1")
						HandCardVec[index]->setSymbol(suit+"A");
					else
						HandCardVec[index]->setSymbol(suit+value);
					valid=true;
					break;
				case 12:	//J
				case 13:	//Q
				case 14:	//K
					HandCardVec[index]->setSuit(suit);
					HandCardVec[index]->setValue(10);
					HandCardVec[index]->setSymbol(suit+value);
					valid=true;
					break;
				default:
					std::cout<<"Joker cannot assume this value: "<<value<<std::endl;
					break;
			}
		}while(!valid);
	}
	
}

int ObtainInteger(const std::string& value){

	if(value =="J")
		return 12;
	else if (value=="Q")
		return 13;
	else if(value=="K")
		return 14;
	else if(std::stoi(value)>=1 && std::stoi(value)<=11)
		return std::stoi(value);
	else
		return -1;

}

void Player::getJoker(){
	printPlayedCardMap();
	int set_index;
	std::cout<<"From which combination/sequence you want to take the Joker?\n";
	std::cin>>set_index;
	
	if(set_index < PlayedCardMap.size() && set_index>=0){

		std::set<std::shared_ptr<Card>>::iterator iterSet = PlayedCardMap[set_index].begin();
		
		while(iterSet!=PlayedCardMap[set_index].end() && !((*iterSet)->getIsJoker())){
			iterSet++;
		}
		
		if(iterSet!=PlayedCardMap[set_index].end()){
			//Create a non Joker card with same value, and suit of the founded Joker to check if the player has the specific card in the hand
			std::shared_ptr<Card> tmpCard = std::make_shared<Card> ((*iterSet)->getValue(), (*iterSet)->getSuit(), (*iterSet)->getSymbol());
			HandCardIter iter = find(HandCardVec.begin(), HandCardVec.end(), tmpCard);
			if(iter != HandCardVec.end()){
				HandCardVec.erase(iter);												//Delete Card pointed by iter from the hand
				HandCardVec.emplace_back(std::make_shared<Card> (25,"","Joker",true));	//Insert Joker in the hand
				PlayedCardMap[set_index].erase(iterSet);								//Delete the Joker from the set	
				PlayedCardMap[set_index].emplace(tmpCard);	//Insert tmpCard in the set
				sort(HandCardVec.begin(), HandCardVec.end());
			}else{
				std::cout<<"You can't replace the Joker from the game"<<std::endl;
			}
		}else{
			std::cout<<"Joker not present in the selected set"<<std::endl;
		}
	}else{
		std::cout<<"Typed not valid index"<<std::endl;
	}
	
}

//To insert a card into HandCardVec
void Player::DrawCard(const std::shared_ptr<Card>& c){

	HandCardVec.emplace_back(c);
	sort(HandCardVec.begin(), HandCardVec.end());

}

//Return OpenedTheGame
bool Player::getOpenedTheGame(){
	
	return OpenedTheGame;
	
}

//Return start
bool Player::getStart(){

	return start;

}

//Return opponent
Player* Player::getOpponent(){

	return opponent;

}

//Notify the opponent
void Player::Notify(const std::string& state){

	/*if(state == "Win"){
		
	}else if(state=="Idle"){
		
		
	}*/
	opponent->toggle(state);

}

void Player::resetPlayedValue(){
	
	played_value=0;
	
}

//return played_value
int Player::getPlayedValue(){

	return played_value;

}

//Return true if PlayedCardMap is empty, else false
bool Player::isPlayedCardMapEmpty(){
	
	return PlayedCardMap.empty();
	
}

//To return the card from table to hand
void Player::fromTableToHand(){
	
	//PlayedCardType::reverse_iterator rev_iter=PlayedCardMap.rbegin();
	
	while(played_value!=0){

		PlayedCardType::reverse_iterator rev_iter=PlayedCardMap.rbegin();
		//std::set<std::shared_ptr<Card>> SetToRemove = rev_iter->second;
		std::multiset<std::shared_ptr<Card>> SetToRemove = rev_iter->second;
		std::set<std::shared_ptr<Card>>::iterator set_iter = SetToRemove.begin();

		for(; set_iter!=SetToRemove.end(); set_iter++){
			
			DrawCard(*set_iter);
			played_value-=((*set_iter)->getValue());
			
			
		}

		PlayedCardMap.erase(rev_iter->first);

	}
}

PlayedCardType Player::PlayedCardMap;

}