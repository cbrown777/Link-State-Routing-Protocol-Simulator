#ifndef FORWARDINGTABLEENTRY_H
#define FORWARDINGTABLEENTRY_H

#include <string>

using std::string;

// Structure to represent a Forwarding Table Entry
struct ForwardingTableEntry{
    int dest; 
    int cost;
    int nextHop;
    string path;
};

#endif