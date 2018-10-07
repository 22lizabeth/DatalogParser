#include "Graph.h"

int Graph::getSize()
{
  return graph.size();
}

Node Graph::getNode(int nodeID)
{
  return graph[nodeID];
}

vector<int> Graph::getSCC()
{
  return scc;
}

vector<int> Graph::getPostorderNodes()
{
  return postorderNodes;
}

map<int, Node> Graph::getGraph()
{
  return graph;
}

void Graph::changePostorderNodes(vector<int> newPostorderNodes)
{
  postorderNodes = newPostorderNodes;
}

void Graph::addNode(int nodeID)
{
  Node n;
  graph[nodeID] = n;
}

void Graph::addEdge(int nodeID, int edgeNodeID)
{
  graph[nodeID].addEdge(edgeNodeID);
}

void Graph::clearSCC()
{
  scc.clear();
}

void Graph::DFS1(int nodeID)
{
    //Mark node as visited
    bool visited = graph[nodeID].checkIfVisited();
    if(!visited)
    {
      set<int> nodeEdges = graph[nodeID].getEdges();
      for(set<int>::iterator it2 = nodeEdges.begin(); it2 != nodeEdges.end(); it2++)
      {
        DFS1(*it2);
      }
      //'Assign' postorder num
      postorderNodes.push_back(nodeID);
    }
}

void Graph::DFS2(int nodeID)
{
    //Mark node as visited
    bool visited = graph[nodeID].checkIfVisited();
    if(!visited)
    {
      //Add current node to the current SCC
      scc.push_back(nodeID);

      //Remove the current node from the postorder nodes to check
      vector<int>::iterator it = find(postorderNodes.begin(), postorderNodes.end(), nodeID);
      if(it != postorderNodes.end())
      {
        postorderNodes.erase(it);
      }

      //Call DFS on all edges/adjacent nodes
      set<int> nodeEdges = graph[nodeID].getEdges();
      for(set<int>::iterator it2 = nodeEdges.begin(); it2 != nodeEdges.end(); it2++)
      {
        DFS2(*it2);
      }
    }
}

void Graph::printSCC()
{
  cout << "R" << scc[0];
  for(unsigned int i = 1; i < scc.size(); i++)
  {
    cout << ",R" << scc[i];
  }
}

void Graph::printGraph()
{
  cout << "Dependency Graph";
  for(map<int, Node>::iterator it = graph.begin(); it != graph.end(); it++)
  {
    cout << endl;
    cout << "R" << it->first << ":";
    it->second.printEdges();
  }
}
