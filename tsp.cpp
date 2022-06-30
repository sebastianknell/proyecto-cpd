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
            if(copy[j][i] != INT_MAX){
                copy[j][i] -= min;
            }
        }
    }
    for(int i = 0; i<graph.size(); i++){
        double min = INT_MAX;
        for(int j = 0; j<graph.size();j++){
            if(copy[j][i] < min){
                min = copy[j][i];
            }
        }
        cost += min;
        for(int j = 0; j<graph.size();j++){
            if(copy[j][i] != INT_MAX){
                copy[j][i] -= min;
            }
        }
    }
    return {copy, cost};
}

pair<Graph, double> reduce(const Graph &graph, int from, int to) {
    auto reducedGraph = graph;
    for (int i = 0; i < graph.size(); i++) reducedGraph[from][i] = INT_MAX;
    for (int i = 0; i < graph.size(); i++) reducedGraph[i][to] = INT_MAX;
    reducedGraph[to][0] = INT_MAX;
    return initialReduce(reducedGraph);
}


Path SecuentialBAB(const Graph &distance, int first) {
    auto reduction = initialReduce(distance);
    auto graph = reduction.first;
    auto cost = reduction.second;

    auto cmp = [](Path &a, Path &b) {
        return a.cost < b.cost;
    };

    priority_queue<Path, vector<Path>, decltype(cmp)> queue(cmp);
    Path* currentPath = new Path();
    currentPath->nodes.push(first);
    currentPath->cost = cost;
    queue.push(*currentPath);

    while (!queue.empty()) {

    }

    for (int i = 0; i < graph.size(); i++) {

    }



    return Path();
}
