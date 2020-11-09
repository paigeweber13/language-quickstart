//
// Created by riley on 11/8/20.
//

#include "dijkstra.hpp"

std::vector<unsigned> dijkstra(graph g, unsigned startNode){
  std::set<size_t> unvisited_nodes;
  std::vector<size_t> distance_to_nodes(g.size());

  for(size_t i = 0; i < g.size(); i++) {
    unvisited_nodes.insert(i);

    // temporarily set max distance
    distance_to_nodes[i] = std::numeric_limits<size_t>::max();
  }


  return std::vector<unsigned>();
}

void print_vector(std::vector<unsigned> v) {
  printf("[");
  for (size_t i = 0; i < v.size(); i++) {
    printf("%d,", v[i]);
  }
  printf("]\n");
}

int main(int argc, char **argv) {
  auto v = dijkstra(graph_5_nodes, 0);
  print_vector(v);

  return 0;
}
