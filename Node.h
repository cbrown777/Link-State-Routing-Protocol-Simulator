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
        int id; 
        vector<Edge*> edges;

        // // Create a priority queue to store vertices and their distances
        // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // // P[v]
        // unordered_map<int, int> predecessors;



        // // Create a map of int id -> dist to store distances from source to all vertices
            // Generate V from the # of keys of the map id -> Node
            // Map each key to INF
        // unordered_map<int> dist(V, INF);




        // Will need string Path for each other dest Node
        // Map: Node (struct or id) -> Path (string) 


    public: 
        Node(int id);
        vector<Edge*> getEdges() const;
        void addEdge(Edge* newEdge);

};




#endif