//
// Created by riley on 11/8/20.
//
// graph represented by an adjacency matrix. Also includes samples for testing.
//

#pragma once

typedef std::vector<std::vector<unsigned>> graph;

/* an image of this graph is found in this directory. It is an svg file of
 * the same name
 *
 * expected shortest path from 0:
 *  - cost:
 *  - path:
 */
graph graph_5_nodes = {
    {0, 4, 1, 0, 0},
    {3, 0, 0, 0, 5},
    {0, 0, 0, 8, 7},
    {0, 0, 4, 3, 0},
    {0, 8, 3, 6, 0},
};
