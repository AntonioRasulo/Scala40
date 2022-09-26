#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

namespace Scala40{

class Player;

class PlayerState{
	public:
		virtual void enter(Player* player) = 0;
		virtual void toggle(Player* player, std::string state="") = 0;
		//virtual void exit(Player* player) =0;
		virtual ~PlayerState(){}
};

}


#endif