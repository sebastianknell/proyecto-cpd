//
// Created by Sebastian Knell on 29/06/22.
//

#include "tsp.h"

pair<Graph, double> initialReduce(const Graph &graph) {
    Graph copy = graph;
    double cost = 0;
    for(int i = 0; i<graph.size(); i++){
        double min = *min_element(graph[i].begin(), graph[i].end());
        cost += min;
        for(int j = 0; j<graph.size();j++){
            if(copy[j][i] != DBL_MAX){
                copy[j][i] -= min;
            }
        }
    }
    for(int i = 0; i<graph.size(); i++){
        double min = DBL_MAX;
        for(int j = 0; j<graph.size();j++){
            if(copy[j][i] < min){
                min = copy[j][i];
            }
        }
        cost += min;
        for(int j = 0; j<graph.size();j++){
            if(copy[j][i] != DBL_MAX){
                copy[j][i] -= min;
            }
        }
    }
    return {copy, cost};
}

pair<Graph, double> reduce(const Graph &graph, int from, int to) {
    auto reducedGraph = graph;
    for (int i = 0; i < graph.size(); i++) reducedGraph[from][i] = BDL_MAX;
    for (int i = 0; i < graph.size(); i++) reducedGraph[i][to] = DBL_MAX;
    reducedGraph[to][0] = DBL_MAX;
    return initialReduce(reducedGraph);
}


Path SecuentialBAB(const Graph &distance, int first) {
    auto reduction = initialReduce(distance);
    auto graph = reduction.first;
    auto cost = reduction.second;

    auto cmp = [](Path &a, Path &b) {
        return a.cost < b.cost;
    };

    double UpperBound = DBL_MAX;

    priority_queue<Path, vector<Path>, decltype(cmp)> queue(cmp);
    Path* currentPath = new Path();
    currentPath->graph = graph;
    currentPath->nodes.push(first);
    currentPath->cost = cost;
    queue.push(*currentPath);

    Path* optimalPath = nullptr;

    while (!queue.empty()) {
        auto CurrentPath = queue.top();
        queue.pop();
        if(currentPath.cost <= UpperBound){
            bool StopCondition = false;
            vector<int> nextDistrito = {};
            for(int i = 0; i< graph.size(); i++){
                if(currentPath.graph[currentPath.currentDistrito][i] != DBL_MAX && currentPath.){
                    StopCondition = true;
                    nextDistrito.push_back(i);
                }
            }
            if(!StopCondition){
                UpperBound = currentPath.cost;
                if(optimalPath == nullptr) optimalPath = &currentPath;
                else if(currentPath.cost<optimalPath.cost) optimalPath = &currentPath;
            } else{
                for(int i = 0; i<nextDistrito.size(); i++){
                    Path* nextPath = new Path();
                    reduction = reduction();
                    nextPath->graph = reduction.first;
                    nextPath->nodes = currentPath.nodes;
                    nextPath->nodes.push(i);
                    nextPath->cost = reduction.second;
                    queue.push(*nextPath);
                }
            }
        }

    }

    return Path();
}
