<<<<<<< HEAD
//#include "BuildingDeck.h"
//
//
//
//buildingDeck::buildingDeck()
//{
//}
//
//buildingDeck::~buildingDeck()
//{
//}
//
//
//void buildingDeck::buildDeckOfBuilding()
//{
//
//}
=======
#include "BuildingDeck.h"
#include <cstdlib>
#include <ctime>
#include <random>

deck::BuildingDeck::~BuildingDeck()
{
	delete deck;
	deck = nullptr;
}

//This function basically ruins your fucking gacha experience
int gaben(int x)
{
	srand(time(nullptr)); 
	return std::rand() % x;
}

void deck::BuildingDeck::shuffle()
{
	
	std::random_shuffle(deck->begin(), deck->end(), gaben);
}

void deck::BuildingDeck::buildDeck()
{
	
	for (int res = Wheat; res <= Stone + 1 - 1; res++)
	{
		ResourceType resource = static_cast<ResourceType>(res);
		for (int cost = 1; cost <= 6; cost++)
		{
			for (int i = 0; i < 6; i++)
			{
				Building building { new int(cost), new ResourceType(resource)};
				deck->push_back(building);
			}

		}

	}

	this->shuffle(); 

}

//Someone fix this later
deck::Building deck::BuildingDeck::draw()
{
	
	Building top = deck->back();
	deck->pop_back();

	return top;


}

void deck::Building::printInfo()
{
	std::cout << "Cost: " << *cost << "\tResource: " << *resource << std::endl;
}

void deck::BuildingDeck::printDeck()
{
	int* count = new int(0);
	for (auto b : *deck)
	{
		b.printInfo();
		(*count)++;
	}

	std::cout << "N-word counter: " << *count << std::endl;

	draw().printInfo();
	draw().printInfo();

}

void deck::BuildingDriver::run()
{
	BuildingDeck dickTesting9inches;

	dickTesting9inches.printDeck();

}
>>>>>>> 04d97acdaf9dadf25b1dec56d2341d5a2e07d4d9
