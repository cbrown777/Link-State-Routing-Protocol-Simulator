#ifndef NODE_H
#define NODE_H

#include "Edge.h"

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>


using namespace std;

#define INF numeric_limits<int>::max()


// Class to represent a Node in the graph
class Node {


    private:
        int _id; 
        vector<Edge> edges;


        // Within a Struct/Object for Computing Shortest Paths
            // // Create a priority queue to store vertices and their distances
            // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

            // // P[v]
            // unordered_map<int, int> predecessors;



            // // Create a map of int id -> dist to store distances from source to all vertices
                // Generate V from the # of keys of the map id -> Node
                // Map each key to INF
            // unordered_map<int, int> dist(V, INF);



        // Within a Forwarding Table Struct/Object
            // Several Forwarding Table Entries (One for each destination)
                // Forwarding Table Entry
                    // destination
                    // path cost
                    // next hop (derived from Path)
                    // Path 


    public: 
        Node(int id);
        vector<Edge>& getEdges();
        void addEdge(const Edge& newEdge);

};




#endif