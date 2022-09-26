#ifndef DECKS_H
#define DECKS_H

namespace Scala40{

class Card;

class Decks{
	private:
		//std::stack<Card*> heel;	//tallone
		//std::stack<Card*> well;	//pozzo
		std::stack<std::shared_ptr<Card>> heel;
		std::stack<std::shared_ptr<Card>> well;
		
		//std::set<std::string> possibleSymbol;
		//Constructor
		Decks();
		//object of Decks
		static Decks* object;
		//Constructors
		Decks(const Decks& D){};
		//operator=
		Decks& operator=(const Decks& D);
		//Support method
		//void Init(const std::string& suit_);
	public:
		//To get the object istance
		static Decks* Get();
		//To push card into well
		void DiscardCard(const Card& c);
		//To draw a card from heel
		std::shared_ptr<Card> DrawCardHeel();
		//To draw a card from well
		std::shared_ptr<Card> DrawCardWell();
		//Tell if heel is empty
		bool getHeelIsEmpty();
		//To shuffle heel
		void shuffleHeel();
		//To shuffle well
		void shuffleWell();
		//To print top card of the well
		void printTopWell();
		//To swap heel and well when heel is empty
		void swapDecks();
};

}

#endif