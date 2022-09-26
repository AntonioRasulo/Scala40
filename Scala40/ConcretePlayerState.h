#ifndef CONCRETE_PLAYER_STATE_H
#define CONCRETE_PLAYER_STATE_H

namespace Scala40{

class Reset : public PlayerState{
	public:
		void enter(Player* player);
		void toggle(Player* player, std::string state="");
		//void exit(Player* player);
		static PlayerState& getInstance();
		
	private:	
		Reset(){}
		Reset(const Reset& other);
		Reset& operator=(const Reset& other);

};

class Idle : public PlayerState{
	public:
		void enter(Player* player);
		void toggle(Player* player, std::string state="");
		//void exit(Player* player);
		static PlayerState& getInstance();

	private:	
		Idle(){}
		Idle(const Idle& other);
		Idle& operator=(const Idle& other);

};

class Draw : public PlayerState{
	public:
		void enter(Player* player);
		void toggle(Player* player, std::string state="");
		//void exit(Player* player);
		static PlayerState& getInstance();

	private:	
		Draw(){}
		Draw(const Draw& other);
		Draw& operator=(const Draw& other);

};

class Processing : public PlayerState{
	public:
		void enter(Player* player);
		void toggle(Player* player, std::string state="");
		//void exit(Player* player);
		static PlayerState& getInstance();

	private:	
		Processing(){}
		Processing(const Processing& other);
		Processing& operator=(const Processing& other);

};

class Win : public PlayerState{
	public:
		void enter(Player* player);
		void toggle(Player* player, std::string state="");
		//void exit(Player* player);
		static PlayerState& getInstance();
		
	private:	
		Win(){}
		Win(const Win& other);
		Win& operator=(const Win& other);

};

}

#endif