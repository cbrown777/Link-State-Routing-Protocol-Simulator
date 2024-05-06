#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <iostream>

#include "Topology.h"

using namespace std;




// Re-factor to loop later on 
void checkFilesStatus(const ifstream& topofileStream, const ifstream& messagefileStream, const ifstream& changesfileStream){

    cout << "Checking File opening status..." << endl;

    if (!topofileStream.is_open()) {
        std::cerr << "Error: Unable to open topofile." << std::endl;
        exit(1);
    }
    if (!messagefileStream.is_open()) {
        std::cerr << "Error: Unable to open messagefile." << std::endl;
        exit(1);
    }
    if (!changesfileStream.is_open()) {
        std::cerr << "Error: Unable to open changesfile." << std::endl;
        exit(1);
    }

    cout << "All files openend successfully! \n" << endl;
}








int main(int argc, char** argv) {
    //printf("Number of arguments: %d", argc);
    if (argc != 4) {
        printf("Usage: ./linkstate topofile messagefile changesfile\n");
        return -1;
    }


    // initialize ifstream objects for the 3 input files
    ifstream topofileStream;
    ifstream messagefileStream;
    ifstream changesfileStream;

    // initialize ofstream object to write to
    ofstream fileStreamOut;


    // open ifstream files: topofile, messagefile, changesfile
    topofileStream.open(argv[1]);
    messagefileStream.open(argv[2]);
    changesfileStream.open(argv[3]);

    // open ofstream files
    fileStreamOut.open("output.txt");



    // Check if files were opened successfully 
    checkFilesStatus(topofileStream, messagefileStream, changesfileStream);



// _____________________________________________________________________________________
    // // Generate Topology
    // Topology top_1;
    // top_1.updateNodes(topofileStream);
    // //top_1.printNodesAndEdges();

    // cout << "Just completed printNodesAndEdges(), now let's add the changesfile to see if that correctly modifies the Nodes... \n\n" << endl;


    // // add links for 2-4 and then delete, delete links b/w 6-5, 6-12
    // top_1.updateNodes(changesfileStream);



    // cout << "Let's generate shortest paths from every Node... \n\n" << endl;


    // top_1.computeShortestPaths();


    // cout << "Now printing all dist maps and predecessors maps..." << endl;
    // cout << "____________________________________________________\n\n" << endl;

    // top_1.printDistAndPredecessorsForEveryNode();


    // // Generate Forwarding Tables for Nodes after shortest paths have been computed
    // top_1.generateNodeForwardingTables();




    // top_1.writeOutForwardingTablesForAllNodes(fileStreamOut);


    // top_1.writeOutMessages(fileStreamOut, messagefileStream);
// _____________________________________________________________________________________





    // Generate Topology
    Topology top_1;
    top_1.generateTopology(topofileStream);

    // compute paths, print forwarding tables, print messages
    top_1.computeShortestPaths();
    top_1.generateNodeForwardingTables();
    top_1.writeOutForwardingTablesForAllNodes(fileStreamOut);
    top_1.writeOutMessages(fileStreamOut, messagefileStream);



    string lineFromFile;
    // apply changes to topology, one line at a time, before calling above functions
    while(!changesfileStream.eof()){
        getline(changesfileStream, lineFromFile);

        if (lineFromFile.empty()) {
            continue;
        }

        top_1.applyChangesFile(lineFromFile);

        // DO WORK
        top_1.computeShortestPaths();
        top_1.generateNodeForwardingTables();
        top_1.writeOutForwardingTablesForAllNodes(fileStreamOut);
        top_1.writeOutMessages(fileStreamOut, messagefileStream);
    }






    // close input files
    topofileStream.close();
    messagefileStream.close();
    changesfileStream.close();

    // close output files
    fileStreamOut.close();


    return 0;
}




// (A)
// intake topology
    // generate graph / adjacency matrix to represent the topology
    // Format:
        // <node_1> <node_2> <cost>

// (B) Converge Tables
// 1) run Djykstra's Alg for EACH node on the network to generate the BEST PATH from that node to EVERY other node on the network
    // if a current-best-known path and newly found path are equal in cost -> choose the path whose last node before the destination has the smaller ID**
// 2) pull the (1. next hop) and (2. path cost) from each path to generate the forwarding table for each node  
    // Format:
        // <destination> <nexthop> <pathcost>
    // forwarding table entries should be sorted by DESTINATION
    // Each node’s entry for itself should list the nexthop as itself, and the cost as 0
        // Ex for Node 2:
        //  1 5 6 
        //  2 2 0 
        //  3 3 3 
        //  4 5 5 
        //  5 5 4

// (C) Print Forwarding Tables for Each Node 
    // print SORTED by node_ID
        // node_1 Table, then node_2 Table
    // ** If a destination in a table is NOT REACHABLE, DO NOT PRINT IT'S ENTRY!


// (D) Print Messages 
    // print SORTED by how they are in messagefile
    // When a message is to be sent 
	// print: 
	    // 	1. the source
	    // 	2. destination
	    // 	3. path cost
	    // 	4. path taken (including the source, but NOT the destination node)
	    // 	5. message contents

	// “from <x> to <y> cost <path_cost> hops <hop1> <hop2> <...> message <message>” 
        // ex: 
	    // “from 2 to 1 cost 6 hops 2 5 4 message here is a message from 2 to 1” 

	// If the destination is not reachable
	    // please say:
	        // “from <x> to <y> cost infinite hops unreachable message <message>” 

// (E) Apply Changes to Topology
    // Format:
        // <node_1> <node_2> <cost>






// (A) Intake Topology

// while (reached end of changes file){
//     (B)
//     (C)
//     (D)
//     (E)
// }
