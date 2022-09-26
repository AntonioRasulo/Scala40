#include<algorithm>
#include<string>
#include<stack>
#include<set>
#include<memory>
#include<vector>
#include<iostream>
#include<random>
#include "Card.h"
#include "Decks.h"

namespace Scala40{
	
Decks::Decks(){
	
	const std::string suit_[4] = {"hearts", "clubs", "diamonds", "spades"};

	for(int l=0; l<2; l++){				//Two decks
		for(int i=0; i<4; i++){			//iterate through suit_
			for(int j=2; j<11; j++){	//iterate through 2-10
				heel.emplace(std::make_shared<Card>(j, suit_[i], suit_[i]+std::to_string(j)));	//insert the card from 2 to 10, assign value, symbol, suit, isJoker = false
			}

			heel.emplace(std::make_shared<Card> (1, suit_[i], suit_[i]+"A"));	//insert A,J
			heel.emplace(std::make_shared<Card> (10, suit_[i], suit_[i]+"J"));
			heel.emplace(std::make_shared<Card> (10, suit_[i], suit_[i]+"Q"));
			heel.emplace(std::make_shared<Card> (10, suit_[i], suit_[i]+"K"));
			
		}
		heel.emplace(std::make_shared<Card> (25,"","Joker",true));	//insert Joker
		heel.emplace(std::make_shared<Card> (25,"","Joker",true));	//insert Joker
	}
	shuffleHeel();
}

Decks& Decks::operator=(const Decks& D){
	
	return *this;
}

void Decks::swapDecks(){

	if(heel.empty())
		heel.swap(well);

}

Decks* Decks::Get(){
	if(object == nullptr) object = new Decks();
	return object;
}

void Decks::DiscardCard(const Card& c){
	
	//well.push(new Card(c));
	well.emplace(std::make_shared<Card> (c));
}

std::shared_ptr<Card> Decks::DrawCardHeel(){
	
	std::shared_ptr<Card> c = std::make_shared<Card> (*(heel.top()));
	
	heel.pop();
	
	return c;
	
	//return *(heel.pop());
	
}

//To draw a card from well
std::shared_ptr<Card> Decks::DrawCardWell(){

	std::shared_ptr<Card> c = std::make_shared<Card> (*(well.top()));
	
	well.pop();
	
	return c;

}

//Tell if heel is empty
bool Decks::getHeelIsEmpty(){
	
	return heel.empty();
	
}

void Decks::shuffleHeel(){

	std::vector<std::shared_ptr<Card>> tmpVec;
	
	while(!heel.empty()){
		tmpVec.emplace_back(std::make_shared<Card> (*(heel.top())));
		heel.pop();
	}
	
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::shuffle(tmpVec.begin(), tmpVec.end(), gen);

	while(!tmpVec.empty()){
		
		heel.emplace(std::make_shared<Card> (*(tmpVec.back())));
		tmpVec.pop_back();
	}

}

void Decks::shuffleWell(){
	
	std::vector<std::shared_ptr<Card>> tmpVec;
	
	while(!well.empty()){
		tmpVec.emplace_back(std::make_shared<Card> (*(well.top())));
		well.pop();
	}

	std::random_device rd;
	std::default_random_engine gen(rd());
	std::shuffle(tmpVec.begin(), tmpVec.end(),gen);

	while(!tmpVec.empty()){
		
		well.emplace(std::make_shared<Card> (*(tmpVec.back())));
		tmpVec.pop_back();
	}
	
}

//To print top card of the well
void Decks::printTopWell(){

	if(!well.empty())
		std::cout<<well.top()->getSymbol()<<std::endl;
	else
		std::cout<<"The well is empty\n";
}

Decks* Decks::object = nullptr;

}