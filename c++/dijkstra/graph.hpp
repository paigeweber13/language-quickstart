//
// Created by riley on 11/8/20.
//
// graph represented by an adjacency matrix. Also includes samples for testing.
//

#pragma once

typedef std::vector<std::vector<unsigned>> graph;

/*
 * Represents the following graph:
 *
 * 0 -- 2 - 3
 * |    | /
 * 1 -- 4
 *
 */

graph graph_5_nodes = {
    {0, 4, 1, 0, 0},
    {3, 0, 0, 0, 5},
    {5, 0, 0, 8, 7},
    {0, 0, 4, 3, 0},
    {0, 8, 3, 6, 0},
};

graph graph_6_nodes = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
};
