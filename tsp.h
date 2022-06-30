//
// Created by Sebastian Knell on 29/06/22.
//

#ifndef TSP_TSP_H
#define TSP_TSP_H

#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

using Graph = vector<vector<double>>;
using Path = struct {stack<int> nodes; double cost;};

pair<Graph, double> reduce(const Graph&, int from, int to);
pair<Graph, double> initialReduce(const Graph&);
Path SecuentialBAB(const Graph&, int);

Path ParallelBAB();


#endif //TSP_TSP_H
