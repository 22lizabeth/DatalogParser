#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Rule.h"
#include<map>

class Graph
{
  private:
    map<int, Node> graph;
    vector<int> scc;
    vector<int> postorderNodes;
  public:
    Graph(){};
    int getSize();
    Node getNode(int nodeID);
    vector<int> getSCC();
    vector<int> getPostorderNodes();
    map<int, Node> getGraph();
    void changePostorderNodes(vector<int> newPostorderNodes);
    void addNode(int nodeID);
    void addEdge(int nodeID, int edgeNodeID);
    void clearSCC();
    void DFS1(int nodeID);
    void DFS2(int nodeID);
    void printSCC();
    void printGraph();
};

#endif
