#pragma once

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "../Player/Player.h"
#include "../Observer/GameObservers.h"

namespace maingame
{
	class TurnSequence
	{
	private:
	public:
		TurnSequence() {}
		void playTurn(player::Player* player, player::Player** others, int numberOfPlayers, obs::Observable* subject);
	};


	class TurnSequenceDriver
	{
	public:
		void run();
	};

}

