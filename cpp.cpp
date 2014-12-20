#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct node;

struct route{
  node& dest;
  const int cost;
};

struct node {
  vector<route> neighbours;
  bool visited = false;
};

vector<node> readPlaces(){
  ifstream text("agraph");
  int numNodes; text >> numNodes;
  vector<node> nodes(numNodes);
  int node, neighbour, cost;
  while (text >> node >> neighbour >> cost){
    nodes[node].neighbours.push_back(route{nodes[neighbour], cost});
  }
  return nodes;
}

int getLongestPath(vector<node> &nodes, node &node){
  node.visited = true;
  int max=0;
  for(const route &neighbour: node.neighbours){
    if (!neighbour.dest.visited){
      const int dist = neighbour.cost + getLongestPath(nodes, neighbour.dest);
      if (dist > max){
        max = dist;
      }
    }
  }
  node.visited = false;
  return max;
}

int main() {
  vector<node> nodes = readPlaces();
  auto start = high_resolution_clock::now();
  int len = getLongestPath(nodes, nodes[0]);
  auto end = high_resolution_clock::now();
  auto duration = (int)(0.001 * duration_cast<microseconds>(end - start).count());
  cout << len << " LANGUAGE C++ " << duration << std::endl;
}
