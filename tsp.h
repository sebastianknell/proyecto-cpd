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
typedef struct{Graph graph; vector<int> nodes; double cost; int currentDistrito; double oil;} PathExtra;

void printPath(Path*);
void printPath(Path*, vector<string>&);
void printPath(PathExtra*, vector<string>&);
pair<Graph, double> reduce(const Graph&, int from, int to);
pair<Graph, double> initialReduce(const Graph&);
Path* SequentialBAB(Graph&, int);
Path* ParallelBAB(Graph&, int);
PathExtra* SequentialBABCost(Graph, int, Graph&);
PathExtra* ParallelBABCost(Graph, int, Graph&);
Path* SequentialBABOpt(Graph&, int, vector<int>&);
Path* ParallelBABOpt(Graph&, int, vector<int>&);
PathExtra* SequentialBABCostOpt(Graph, int, Graph&, vector<int>&);
PathExtra* ParallelBABCostOpt(Graph, int, Graph&, vector<int>&);



#endif //TSP_TSP_H
