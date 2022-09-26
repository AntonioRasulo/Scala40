/*Scala40: realizzare le classi in modo da permettere il gioco tra due umani (facile) oppure per far giocare un umano contro il PC usando delle semplici euristiche (+difficile).
Non e' necessario implementare l'interfacciaccia grafica ma semplicemente stampare sullo schermo attraverso caratteri le carte sul tavolo.*/

#ifndef CARD_H
#define CARD_H

namespace Scala40{
	
class Card{
	private:		
		int value;
		std::string symbol;
		std::string suit;
		bool isJoker;
		
	public:
		//Constructors
		Card(const int& value_, const std::string& suit_, const std::string& symbol_, bool isJoker_=false);
		//Copy constructors
		Card(const Card& c);
		
		//Getters
		int getValue() const;
		std::string getSuit() const;
		bool getIsJoker() const;
		std::string getSymbol() const;
		
		//Setters
		void setValue(const int& value_);
		void setSuit(const std::string& suit_);
		void setIsJoker(const bool& isJoker_);
		void setSymbol(const std::string& symbol_);

		//To print the symbol on screen
		//void printSymbol();

		//operator=
		Card& operator=(const Card& D);

		//operator==
		friend bool operator==(const Card& left, const Card& right);
		//friend bool operator==(const Card* left, const Card* right);
		friend bool operator==(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right);
		
		//operator<
		friend bool operator<(const Card& left, const Card& right);
		//friend bool operator<(const Card* left, const Card* right);
		friend bool operator<(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right);
};
	
	//operator==
	bool operator==(const Card& left, const Card& right);
	//bool operator==(const Card* left, const Card* right);
	bool operator==(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right);
	
	//operator<
	bool operator<(const Card& left, const Card& right);
	//bool operator<(const Card* left, const Card* right);
	bool operator<(const std::shared_ptr<Card> left, const std::shared_ptr<Card> right);
	
}

#endif