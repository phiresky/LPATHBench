#include <ctime>
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct route{
  int dest, cost;
};

struct node {
  vector<route> neighbours;
};

vector<node> readPlaces(){
  ifstream text("agraph");
  int numNodes; text >> numNodes;
  vector<node> nodes(numNodes);
  int node, neighbour, cost;
  while (text >> node >> neighbour >> cost){
    nodes[node].neighbours.push_back(route{neighbour, cost});
  }
  return nodes;
}

int getLongestPath(const vector<node> &nodes, const int nodeID, vector<size_t>& visited){
  visited[nodeID] = true;
  int max=0;
  for(const route &neighbour: nodes[nodeID].neighbours){
    if (visited[neighbour.dest] == false){
      const int dist = neighbour.cost + getLongestPath(nodes, neighbour.dest, visited);
      if (dist > max){
        max = dist;
      }
    }
  }
  visited[nodeID] = false;
  return max;
}

int getLongestPath(const vector<node> &nodes)
{
  vector<size_t> visited(nodes.size());
  return getLongestPath(nodes, 0, visited);
}

int main(int argc, char** argv){
  auto nodes = readPlaces();
  auto start = high_resolution_clock::now();
  int len = getLongestPath(nodes);
  auto end = high_resolution_clock::now();
  auto duration = (int)(0.001 * duration_cast<microseconds>(end - start).count());
  cout << len << " LANGUAGE C++ " << duration << std::endl;
}
