//
// Created by Sebastian Knell on 29/06/22.
//

#ifndef TSP_TSP_H
#define TSP_TSP_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>
#include <omp.h>

using namespace std;

typedef vector<vector<double>> Graph;
typedef struct{Graph graph; vector<int> nodes; double cost; int currentDistrito;} Path;

void printPath(Path*);
void printPath(Path*, vector<string>&);
pair<Graph, double> reduce(const Graph&, int from, int to);
pair<Graph, double> initialReduce(const Graph&);
Path* SequentialBAB(Graph&, int);
Path* ParallelBAB(Graph&, int);


#endif //TSP_TSP_H
