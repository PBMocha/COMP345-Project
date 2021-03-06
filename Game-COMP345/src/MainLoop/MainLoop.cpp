#include "MainLoop.h"

#include "../GBMaps/GBMap.h"
#include "../Resources/Resources.h"
#include "TurnSequence.h"

void maingame::MainLoop::init(int numberOfPlayer)
{
	// finding number of empty tiles the board will start with
	switch (numberOfPlayer)
	{
	case 2:
		freeTiles = 5 * 5;
		break;
	case 3:
		freeTiles = 5 * 7;
		break;
	case 4:
		freeTiles = 7 * 7 - 4;
		break;
	default:
		std::cout << "ERROR: INVALID NUMBER OF PLAYERS - MAINLOOP.CPP" << std::endl;
		exit(-404);
	}

	currentPlayer = 0;
	nbPlayers = numberOfPlayer;
}

maingame::MainLoop::MainLoop(int numberOfPlayer)
{
	init(numberOfPlayer);
	queue = new std::map<int, player::Player*>();
	activePlayer = nullptr;
}

maingame::MainLoop::~MainLoop()
{
	//for (auto i : *queue)
	//{
	//	delete i.second;
	//}

	//queue->clear();
	//delete queue;
	queue = nullptr;
}

void maingame::MainLoop::setupPlayerOrder(std::vector<player::Player*>* players)
{
	int i = 0;

	for (auto& p : *players){
		queue->emplace(i, p);
	i++;
	}

	players->clear();
	delete players;
	players = nullptr;

}


void maingame::MainLoop::setupPlayerOrder(player::Player* p1, player::Player* p2, player::Player* p3, player::Player* p4)
{
	queue->emplace(0, p1);
	queue->emplace(1, p2);
	queue->emplace(2, p3);
	queue->emplace(3, p4);
	
}

void maingame::MainLoop::turnStart()
{
	activePlayer = queue->at(currentPlayer);
}

void maingame::MainLoop::turnEnd()
{
	//resetting resources back to 0
	resetResources();

	//call bDeck's refreshBoardField
	activePlayer->refreshField();

	currentPlayer = (currentPlayer + 1) % nbPlayers;
}

bool maingame::MainLoop::checkEndState()
{
	return freeTiles == 1;
}

void maingame::MainLoop::drawBuildings()
{
	int amountToDraw = activePlayer->countDrawAmount();
	if (amountToDraw != 0)
	{
		std::cout << "You can draw" << std::endl;
		activePlayer->DrawFromField();
		amountToDraw--;
	}
	else
	{
		std::cout << "You cannot draw" << std::endl;
		return;
	}

	while (amountToDraw > 0)
	{
		std::cout << "You can keep drawing" << std::endl;
		std::cout << "Draw from selection (1) or from deck(2)?" << std::endl;
		int choice;
		std::cin >> choice;
		if (choice == 1)
		{
			activePlayer->DrawFromField();
		}
		else if (choice == 2)
		{
			activePlayer->DrawBuilding();
		}
		amountToDraw--;
	}

	std::cout << "No more drawing\n" << std::endl;
	//std::cout << "Current hand is: " << std::endl;

	//activePlayer->printHand();

}

void maingame::MainLoop::setResources()
{
	activePlayer->ResourceTracker(1, 0, 2, 0);
}

void maingame::MainLoop::resetResources()
{
	std::cout << "Resetting resource counters" << std::endl;
	activePlayer->ResourceTracker(0, 0, 0, 0);
}

void maingame::MainLoop::drawHarvestTiles()
{
	
	//NEED TO TAKE INTO ACCOUNT THE SHIPMENT TILE
	int amountToDraw = activePlayer->countDrawAmountTiles();

	while (amountToDraw > 0)
	{
		activePlayer->DrawHarvestTile();
		amountToDraw--;
	}

	std::cout << "Current hand is: " << std::endl;

	activePlayer->printHand();
}

player::Player** maingame::MainLoop::getOtherPlayers()
{
	if (nbPlayers == 2)
	{
		player::Player* others[1] = {
			queue->at((currentPlayer + 1) % nbPlayers)
		};
		return others;
	}
	else if (nbPlayers == 3)
	{
		player::Player* others[2] = {
			queue->at((currentPlayer + 1) % nbPlayers),
			queue->at((currentPlayer + 2) % nbPlayers)
		};
		return others;
	}
	else if (nbPlayers == 4)
	{
		player::Player* others[3] = {
			queue->at((currentPlayer + 1) % nbPlayers),
			queue->at((currentPlayer + 2) % nbPlayers),
			queue->at((currentPlayer + 3) % nbPlayers)
		};
		return others;
	}
}





void maingame::MainLoopDriver::run()
{
	MainLoop loop(4);
	
	GB::GBMap* board = new GB::GBMap(4);
	deck::BuildingDeck* bDeck = new deck::BuildingDeck();
	deck::HarvestDeck* hDeck = new deck::HarvestDeck();

	std::string* p1 = new std::string("p1");
	std::string* p2 = new std::string("p2");
	std::string* p3 = new std::string("p3");
	std::string* p4 = new std::string("p4");

	player::Player* testPlayer = new player::Player(p1, board, hDeck, bDeck);
	player::Player* testPlayer2 = new player::Player(p2, board, hDeck, bDeck);
	player::Player* testPlayer3 = new player::Player(p3, board, hDeck, bDeck);
	player::Player* testPlayer4 = new player::Player(p4, board, hDeck, bDeck);


	counter::ResourceCounter* count = new counter::ResourceCounter();
	testPlayer->setCounterSystem(count);
	testPlayer2->setCounterSystem(count);
	testPlayer3->setCounterSystem(count);
	testPlayer4->setCounterSystem(count);


	loop.setupPlayerOrder(
		testPlayer,
		testPlayer2,
		testPlayer3,
		testPlayer4
	);
	

	for (int i = 0; i < 4; i++)
	{
		std::cout << std::endl;
		std::cout << "This is, player " << i + 1 << std::endl;

		loop.turnStart();

		//Turn Sequence
		loop.setResources();

		//Active player draws Buildings based on empty resource counters
		loop.drawBuildings();


		//Draw Harvest Tiles
		loop.drawHarvestTiles();

		//Turn's end
		loop.turnEnd();

	}

	//std::cout << loop.checkEndState() << std::endl;

	delete board;
	board = nullptr;

	delete hDeck;
	hDeck = nullptr;

	delete bDeck;
	bDeck = nullptr;

	delete count;
	count = nullptr;
}