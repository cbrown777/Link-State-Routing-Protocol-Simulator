#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include "ForwardingTableEntry.h"

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

#include <map>



using namespace std;

#define INF numeric_limits<int>::max()


// Class to represent a Node in the graph
class Node {


    private:
        int _id; 
        vector<Edge> edges;


        // // P[v]
            // node #, predecessor
        unordered_map<int, int> predecessors;


        // // Create a map of int id -> dist to store distances from source to all vertices
            // Generate V from the # of keys of the map id -> Node
            // Map each key to INF
        unordered_map<int, int> dist;


        map<int, ForwardingTableEntry> forwardingTable;


        // Within a Forwarding Table Struct/Object
            // Several Forwarding Table Entries (One for each destination)
                // Forwarding Table Entry
                    // destination
                    // path cost
                    // next hop (derived from Path)
                    // Path 

        void emptyForwardingTable();

        void generateForwardingTableKeys();
        string generateBestPathToDestination(int destination);
        void generateAllPaths();
        void printAllPaths();
        void generateNextHops();
        int getSecondNumber(const string& path);
        string extractNumbersExceptLast(const string& path);



    public: 
        Node(int id);
        vector<Edge>& getEdges();
        void addEdge(const Edge& newEdge);
        void assignDist(unordered_map<int, int> dist);
        void assignPredecessors(unordered_map<int, int> predecessors);
        int getID();

        void printDist();
        void printPredecessors();
        void generateForwardingTable();
        void writeOutForwardingTable(ofstream& fileStreamOut);
        void writeOutMessage(int dest_node, string& message, ofstream& fileStreamOut);


};




#endif