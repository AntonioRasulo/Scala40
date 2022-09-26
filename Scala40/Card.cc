/*Scala40: realizzare le classi in modo da permettere il gioco tra due umani (facile) oppure per far giocare un umano contro il PC usando delle semplici euristiche (+difficile).
Non e' necessario implementare l'interfacciaccia grafica ma semplicemente stampare sullo schermo attraverso caratteri le carte sul tavolo.*/
#include<iostream>
#include<memory>
#include <string>
#include "Card.h"

namespace Scala40{

Card::Card(const int& value_, const std::string& suit_, const std::string& symbol_, bool isJoker_){

	value=value_;
	suit=suit_;
	isJoker=isJoker_;
	if(isJoker){
		symbol="Joker";
	}else{
		symbol=symbol_;
	}
}

Card::Card(const Card& c){
	
	value=c.value;
	suit=c.suit;
	isJoker = c.isJoker;
	symbol=c.symbol;
	
}


int Card::getValue() const{
	
	return value;
		
}

std::string Card::getSuit() const{

	return suit;
	
}

bool Card::getIsJoker() const{

	return isJoker;

}

std::string Card::getSymbol() const{

	return symbol;

}

void Card::setValue(const int& value_){

	value=value_;
	//setSymbol();

}

void Card::setSuit(const std::string& suit_){

	suit=suit_;
	//setSymbol();
	
}

void Card::setSymbol(const std::string& symbol_){

	symbol=symbol_;

}

//To print the symbol on screen
/*void Card::printSymbol(){
	
	std::cout<<symbol<<std::endl;
	
}*/

//operator=
Card& Card::operator=(const Card& c){
	
	value=c.value;
	suit=c.suit;
	isJoker=c.isJoker;
	return *this;

}

//operator==
bool operator==(const Card& left, const Card& right){

	if(left.isJoker && right.isJoker)
		return true;
	else
		return left.symbol==right.symbol;

}

bool operator==(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right){

	if((*left).isJoker && (*right).isJoker)
		return true;
	else
		return (*left).symbol==(*right).symbol;

//	return (*left) == (*right);

}

//operator<
bool operator<(const Card& left, const Card& right){

	//If the value on the left is a number and the value on the right is J or Q or K
	if((left.symbol.back()!= 'J' && left.symbol.back()!= 'Q' && left.symbol.back()!= 'K') && (right.symbol.back()== 'J' || right.symbol.back()== 'Q' || right.symbol.back()== 'K')){
		return true;
		//else if the value on the right is a number and the value on the left is J or Q or K
	}else if((right.symbol.back()!= 'J' && right.symbol.back()!= 'Q' && right.symbol.back()!= 'K') && (left.symbol.back()== 'J' || left.symbol.back()== 'Q' || left.symbol.back()== 'K')){
		return false;
	}else if(left.symbol.back()== 'J' && (right.symbol.back()== 'Q' || right.symbol.back()== 'K')){	// J<Q J<K
		return true;
	}else if(left.symbol.back()== 'Q' && right.symbol.back() == 'J'){	//Q<J
		return false;
	}else if(left.symbol.back()== 'Q' && right.symbol.back() == 'K'){	//Q<K
		return true;
	}else if(left.symbol.back()== 'K' && (right.symbol.back()== 'J' || right.symbol.back()== 'Q')){	//K<J K<Q
		return false;
	}else{
		return left.value<right.value;
	}

}

bool operator<(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right){

	//If the value on the left is a number and the value on the right is J or Q or K
	if(((*left).symbol.back()!= 'J' && (*left).symbol.back()!= 'Q' && (*left).symbol.back()!= 'K') && ((*right).symbol.back()== 'J' || (*right).symbol.back()== 'Q' || (*right).symbol.back()== 'K')){
		return true;
	//else if the value on the right is a number and the value on the left is J or Q or K
	}else if(((*right).symbol.back()!= 'J' && (*right).symbol.back()!= 'Q' && (*right).symbol.back()!= 'K') && ((*left).symbol.back()== 'J' || (*left).symbol.back()== 'Q' || (*left).symbol.back()== 'K')){
		return false;
	}else if((*left).symbol.back()== 'J' && ((*right).symbol.back()== 'Q' || (*right).symbol.back()== 'K')){	// J<Q J<K
		return true;
	}else if((*left).symbol.back()== 'Q' && (*right).symbol.back() == 'J'){	//Q<J
		return false;
	}else if((*left).symbol.back()== 'Q' && (*right).symbol.back() == 'K'){	//Q<K
		return true;
	}else if((*left).symbol.back()== 'K' && ((*right).symbol.back()== 'J' || (*right).symbol.back()== 'Q')){	//K<J K<Q
		return false;
	}else{
		return (*left).value<(*right).value;
	}
}

}