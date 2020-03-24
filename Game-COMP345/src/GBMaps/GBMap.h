#pragma once
//#ifndef _DEBUG
//#define _DEBUG
//#endif // !_DEBUG
#define _DEBUG
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
#include <vector>
#include <map>
#include <string>
//#include <iostream>
#include "../Resources/Resources.h"
#include <utility>
//#include <memory>

enum class EdgeLoc {
	Top,
	Bot,
	Left,
	Right
};
namespace GB 
{
	
	class Node 
	{
	private:
		//const std::string& name; //Replace with Tile object
		int* nodeId;
		std::string* owner; // Replace with player
		deck::Tile* tile;

		//Old implementation, remove when all adjList conversion moved to the new one
		//std::vector<Node>* adj_list;

		//New implementation, keeps track of where the adjacent node is using edge cost as location
		typedef std::pair<EdgeLoc, Node*> Vertex;
		std::vector<Vertex>* adjList;
		
	public:
		Node(int _nodeId);
		//Node(const Node& node);
		~Node();
		//Node(int _nodeId, std::string _owner) : nodeId(new int(_nodeId)), owner() { }
		int getId() { return *nodeId; }
		void insertAdj(EdgeLoc edge, Node* node);
		int getAdj(EdgeLoc edge);
		//void insertAdj(Node node);
		//int getAdjId(EdgeLoc edge); 
		void setTile(deck::Tile* _tile); // func(new Tile()) func(&tile)
		deck::Tile* getTile() const;
		void setOwner(std::string _owner) { *owner = _owner; }
		std::string getOwner() const;
		void printAdjList();
		bool isAdj(Node* adjNode);
		EdgeLoc* getEdge(Node* adjNode); // get position of adj node
		std::vector<Vertex>* getAdjList() { return adjList; }
	};

	//Unnecessary, can implement graph directly inside of GBMap
	class Graph
	{
	private:
		//typedef Node square;
		//int* numberOfNodes = new int(0);
		//const int* maxNodes;
		std::map<int, Node*>  *graph = new std::map<int, Node*>();

		
	public:

		//Graph(int* _numberOfNodes) : numberOfNodes(_numberOfNodes), graph(new std::map<int, Node>()) {}
		Graph() = default;

		//Cleanup memory
		~Graph();

		//Add vertex no edge
		void addVertex(int src);
		void addEdge(int src, int dest, EdgeLoc edgeSrc, EdgeLoc edgeDest);
		//void addEdge(int src, int dest);

		Node* getNode(int nodeId) const;
		
		
		void insertTile(int nodeId, deck::Tile* tile);
		void printGraph(); //Traveser all vertexes and list adjacents
		bool isTileExists(int loc);
	};

	class GBMap
	{

	private:
		const int* numberOfPlayers = new int(4);
		int* recentTile = new int(0); 
		Graph* graph = new Graph();
		std::vector<int>* blockedKeys = nullptr;

		void createFullBoard();
		void create5By7();
		void create5By5();
		void createGrid(int row, int col);

	public:

		GBMap() = default;
		GBMap(const int _players) : numberOfPlayers(new int(_players)), graph(new Graph()) {}
		~GBMap();
		
		//~GBMap(); // Delete all pointers
		bool buildBoard();
		void blockKeys(const std::vector<int>& badKeys);

		//Returns most-recent tile. Used for game scoring
		Node* getRecentNode() const { return graph->getNode(*recentTile); }
		int recentTileById() { return *recentTile; };
		deck::Tile* getRecentTile() { return peekTile(*recentTile); }

		void setOwner(int loc, std::string player);
		std::string getOwner(int loc) const;

		void placeTile(int loc, deck::Tile* tile);
		deck::Tile* peekTile(int loc) const;
		deck::Tile* getAdjTile(int loc, EdgeLoc adjDirection);
		

		//void printBoard();

	};

	
	class GBMapDriver {

	public:
		
		
		void run();

	};
	
}

