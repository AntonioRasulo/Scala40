#ifndef PLAYER_H
#define PLAYER_H

namespace Scala40{

//typedef std::map<int, std::set<Card*>> PlayedCardType;
//typedef std::map<int, std::set<Card*>>::const_iterator PlayedCardConstIterType;
//typedef std::vector<Card*> HandCardType;	//multiset??
//typedef std::vector<Card*>::iterator HandCardIter;
//typedef std::vector<Card*>::const_iterator HandCardConstIter;

//typedef std::map<int, std::set<std::shared_ptr<Card>>> PlayedCardType;
//typedef std::map<int, std::set<std::shared_ptr<Card>>>::const_iterator PlayedCardConstIterType;
typedef std::map<int, std::multiset<std::shared_ptr<Card>>> PlayedCardType;
typedef std::map<int, std::multiset<std::shared_ptr<Card>>>::const_iterator PlayedCardConstIterType;
typedef std::vector<std::shared_ptr<Card>> HandCardType;	//multiset??
typedef std::vector<std::shared_ptr<Card>>::iterator HandCardIter;
typedef std::vector<std::shared_ptr<Card>>::const_iterator HandCardConstIter;

class PlayerState;

class Player{
	private:
		static PlayedCardType PlayedCardMap;	//Static because is common to all the instance of the class Player
		HandCardType HandCardVec;
		bool IsComputer;
		bool OpenedTheGame;
		PlayerState* currentState;
		std::string name;
		Player* opponent;	//Pointer to the opponent
		bool start;
		int played_value;
		
	public:
		Player(const std::string& name_, const bool& IsComputer_, const bool& start_);

		PlayerState* getCurrentState() const;
		std::string getName() const;
		//static PlayedCardType getPlayedCardMap() const;	//Static getter to access PlayedCardMap
		
		void toggle(std::string state="");
		
		void setState(PlayerState& newState);
		void setOpenedTheGame();
		
		//Set opponent
		void setOpponent(Player* opponent_);

		//To play a game on the table
		void playGame();
		//To insert a card on a game on the table
		void playSingleCard();
		//To get a Joker from a game on the table
		void getJoker();
		//Card* getJoker();
		
		//Return true if HandCardVec if empty, false otherwise
		bool getHandCardVecEmpty();

		//return played_value
		int getPlayedValue();

		//To insert a card into HandCardVec
		void DrawCard(const std::shared_ptr<Card>& c);

		//To discard a Card
		//Return true if discard the card, otherwise false
		bool discardCard();

		//To print PlayedCardMap
		static void printPlayedCardMap();

		//To print the HandCardVec on screen
		void printHandCard();

		//Return OpenedTheGame
		bool getOpenedTheGame();
		
		//Return start
		bool getStart();
		
		//Return opponent
		Player* getOpponent();
		
		//Return true if PlayedCardMap is empty, else false
		static bool isPlayedCardMapEmpty();

		//Notify the opponent
		void Notify(const std::string& state);
		
		//To reset played_value
		void resetPlayedValue();
		
		//To return the card from table to hand
		void fromTableToHand();

		void IfPlayerChooseJoker(const int& index);
};

int ObtainInteger(const std::string& value);

}

#endif