#pragma once

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "../GBMaps/GBMap.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "../Resources/Resources.h"
#include <string>

namespace counter
{
	//Sub Resource Mapping. 
	enum class SubNode
	{
		TopLeft,
		TopRight,
		BotRight,
		BotLeft
	};

	class ResourceNode {
	private:
		std::pair<int, SubNode>* nodeId; 
		Resource* resource;
		//bool* visited;
		typedef std::vector<std::pair<EdgeLoc, ResourceNode*>> AdjNodes;
		std::vector<std::pair<EdgeLoc, ResourceNode*>>* adjResources = new AdjNodes();

	public:

		ResourceNode(std::pair<int, SubNode> _nodeId, Resource _resource) : resource(new Resource(_resource)), nodeId(new std::pair<int, SubNode>(_nodeId)){}
		~ResourceNode();
		int getTileId() { return nodeId->first;  } // Gets the tile this resource resides in. (See GBMap)
		AdjNodes* getAdjResources();
		void setAdjResource(EdgeLoc edgeDir, ResourceNode* adjNode);
		ResourceNode* getAdj(EdgeLoc dir);
		void setResource(Resource newResource) { *resource = newResource; }
		Resource* getResource() { return resource; }
		std::pair<int, SubNode> getNodeId() { return *nodeId; };
		void display();
		void displayLoc();
	};


	class SubGraph {
	private:
		//typedef Node square;
		//int* numberOfNodes = new int(0);
		//const int* maxNodes;
		//Key: <NodeId of the whole tile, SubNodeId>
		typedef std::pair<int, SubNode> SubTile;
		std::map<SubTile, ResourceNode*>* graph = new std::map<SubTile, ResourceNode*>();
		std::vector<int>* nodeIds = new std::vector<int>();
		

	public:

		//Graph(int* _numberOfNodes) : numberOfNodes(_numberOfNodes), graph(new std::map<int, Node>()) {}
		SubGraph() = default;

		//Cleanup memory
		~SubGraph();

		//Add vertex no edge
		std::map<SubTile, ResourceNode*>* getGraph() { return graph; }
		void addVertex(SubTile nodeLoc, Resource resource);
		void addEdge(SubTile src, SubTile dest, EdgeLoc edgeSrc, EdgeLoc edgeDest);

		//Read resource at this vertex
		ResourceNode* getResource(SubTile nodeLoc) const;
		ResourceNode* getAdj(SubTile nodeLoc, EdgeLoc edgeDir);
		void dfs(SubTile root, std::map<SubTile, bool>& visited, Resource target, int* count);

		//void buildGraph();
		void printGraph(); //Travese all vertexes and list adjacents
		int size() { return graph->size(); };
	};

	/*
	1. Player Places a Tile
	2. For each resource in just placed harvest tile
		create sub-graph of adjacent resources, use current resource as root
		increment count of chained resources
	
	*/
	class ResourceCounter
	{
	private:
		typedef std::map<Resource, int> ResourceScores;
		//ResourceScores* counter;
		int resourceCounter[4] = {0, 0, 0, 0};
		//int harvestCount[] = new int[4];
		//Holds the state of the gameboard
		SubGraph* harvestGraph;
		std::vector<int>* placedTiles = new std::vector<int>();
		
		//traverse node

		
		void connectAdjTiles(int recentId, int adjId, EdgeLoc dir);
		
		//A little thicc on space, need to optimize later
	public:
		ResourceCounter();
		~ResourceCounter();
		void display() { harvestGraph->printGraph(); }
		std::map<Resource, int> harvestCount(GB::Node* recentNode); //Keeps state of graph
		//void displayScores();
	};


	class ResourceCounterDriver
	{
	public:
		void run();
	};

}


