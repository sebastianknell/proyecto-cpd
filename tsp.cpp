//
// Created by Sebastian Knell on 29/06/22.
//

#include "tsp.h"

void printPath(Path *path) {
    for (auto &n : path->nodes) cout << n << "->";
    cout << path->nodes.front();
    cout << endl;
}

void printPath(Path* path, vector<string> &names) {
    string line(30, '-');
    cout << line << endl;
    cout << "El camino optimo es:" << endl;
    for (int i = 0; i < path->nodes.size()-1; i++) {
        cout << names[path->nodes[i]] << " -> " << names[path->nodes[i+1]] << endl;
    }
    cout << names[path->nodes.size()-1] << " -> " << names[0] << endl;
    cout << "Distancia total: " << path->cost << endl;
    cout << line << endl;
}

pair<Graph, double> initialReduce(const Graph &graph) {
    Graph copy = graph;
    double cost = 0;
    for (int i = 0; i < graph.size(); i++) {
        double min = *min_element(graph[i].begin(), graph[i].end());
        if(min != INT_MAX) {
            cost += min;
        }
        for (int j = 0; j < graph.size(); j++) {
            if(copy[i][j] != INT_MAX){
                copy[i][j] -= min;
            }
        }
    }
    for (int i = 0; i < graph.size(); i++) {
        double min = INT_MAX;
        for (int j = 0; j < graph.size(); j++) {
            if(copy[j][i] < min){
                min = copy[j][i];
            }
        }
        if (min != INT_MAX) {
            cost += min;
        }
        for (int j = 0; j < graph.size(); j++) {
            if(copy[j][i] != INT_MAX){
                copy[j][i] -= min;
            }
        }
    }
    return {copy, cost};
}

pair<Graph, double> initialReduceParallel(const Graph &graph) {
    Graph copy = graph;
    double cost = 0;
    #pragma omp parallel for default(none) shared(graph, cost, copy)
    for (int i = 0; i < graph.size(); i++) {
        double min = *min_element(graph[i].begin(), graph[i].end());
        if(min != INT_MAX) {
            #pragma omp atomic update
            cost += min;
        }
        for (int j = 0; j < graph.size(); j++) {
            if(copy[i][j] != INT_MAX){
                copy[i][j] -= min;
            }
        }
    }
    #pragma omp parallel for default(none) shared(graph, cost, copy)
    for (int i = 0; i < graph.size(); i++) {
        double min = INT_MAX;
        for (int j = 0; j < graph.size(); j++) {
            if(copy[j][i] < min){
                min = copy[j][i];
            }
        }
        if (min != INT_MAX) {
            #pragma omp atomic update
            cost += min;
        }
        for (int j = 0; j < graph.size(); j++) {
            if(copy[j][i] != INT_MAX){
                copy[j][i] -= min;
            }
        }
    }
    return {copy, cost};
}

pair<Graph, double> reduce(const Graph &graph, int from, int to) {
    auto reducedGraph = graph;
    // ambos paralelos
    for (int i = 0; i < graph.size(); i++) reducedGraph[from][i] = INT_MAX;
    for (int i = 0; i < graph.size(); i++) reducedGraph[i][to] = INT_MAX;
    reducedGraph[to][0] = INT_MAX;
    return initialReduce(reducedGraph);
}

pair<Graph, double> reduceParallel(const Graph &graph, int from, int to) {
    auto reducedGraph = graph;
    // ambos paralelos
    for (int i = 0; i < graph.size(); i++) reducedGraph[from][i] = INT_MAX;
    for (int i = 0; i < graph.size(); i++) reducedGraph[i][to] = INT_MAX;
    reducedGraph[to][0] = INT_MAX;
    return initialReduceParallel(reducedGraph);
}

Path* SequentialBAB(Graph &cities, int first) {
    for (int i = 0; i < cities.size(); i++) cities[i][i] = INT_MAX;
    auto reduction = initialReduce(cities);
    auto graph = reduction.first;
    auto cost = reduction.second;

    auto cmp = [](Path* a, Path* b) {
        return a->cost > b->cost;
    };
    priority_queue<Path*, vector<Path*>, decltype(cmp)> queue(cmp);

    double upperBound = INT_MAX;
    Path* currentPath = new Path();
    currentPath->graph = graph;
    currentPath->cost = cost;
    currentPath->nodes.push_back(first);
    currentPath->currentDistrito = first;
    queue.push(currentPath);

    Path* optimalPath = nullptr;

    while (!queue.empty()) {
        currentPath = queue.top();
        queue.pop();
        if (currentPath->cost <= upperBound) {
            bool stopCondition = false;
            vector<int> nextDistrito = {};
            for (int i = 0; i < graph.size(); i++) {
                if (currentPath->graph[currentPath->currentDistrito][i] != INT_MAX && count(currentPath->nodes.begin(),currentPath->nodes.end(), i ) == 0){
                    stopCondition = true;
                    nextDistrito.push_back(i);
                }
            }
            if (!stopCondition) {
                upperBound = currentPath->cost;
                if(optimalPath == nullptr || currentPath->cost < optimalPath->cost) optimalPath = currentPath;
            }
            else {
                for (int i = 0; i < nextDistrito.size(); i++) {
                    Path* nextPath = new Path();
                    reduction = reduce(currentPath->graph, currentPath->currentDistrito, nextDistrito[i]);
                    nextPath->graph = reduction.first;
                    nextPath->nodes = currentPath->nodes;
                    nextPath->nodes.push_back(nextDistrito[i]);
                    nextPath->cost = reduction.second + currentPath->cost + currentPath->graph[currentPath->currentDistrito][nextDistrito[i]]; // fix
                    nextPath->currentDistrito = nextDistrito[i];
                    queue.push(nextPath);
                }
            }
        }
        else break;
    }
    return optimalPath;
}

Path* ParallelBAB(Graph &cities, int first) {
    for (int i = 0; i < cities.size(); i++) cities[i][i] = INT_MAX;
    auto reduction = initialReduceParallel(cities);
    auto graph = reduction.first;
    auto cost = reduction.second;

    auto cmp = [](Path* a, Path* b) {
        return a->cost < b->cost;
    };
    priority_queue<Path*, vector<Path*>, decltype(cmp)> queue(cmp);

    double upperBound = INT_MAX;
    Path* currentPath = new Path();
    currentPath->graph = graph;
    currentPath->cost = cost;
    currentPath->nodes.push_back(first);
    currentPath->currentDistrito = first;
    queue.push(currentPath);

    Path* optimalPath = nullptr;

    while (!queue.empty()) {
        currentPath = queue.top();
        queue.pop();
        if(currentPath->cost <= upperBound){
            bool stopCondition = false;
            vector<int> nextDistrito = {};
            for (int i = 0; i < graph.size(); i++) {
                if (currentPath->graph[currentPath->currentDistrito][i] != INT_MAX && count(currentPath->nodes.begin(),currentPath->nodes.end(), i ) == 0) {
                    stopCondition = true;
                    nextDistrito.push_back(i);
                }
            }
            if (!stopCondition){
                upperBound = currentPath->cost;
                if(optimalPath == nullptr || currentPath->cost < optimalPath->cost) optimalPath = currentPath;
            }
            else {
                #pragma omp parallel for default(none) shared(nextDistrito, currentPath ,queue)
                for (int i = 0; i < nextDistrito.size(); i++) {
                    Path* nextPath = new Path();
                    auto newReduction = reduceParallel(currentPath->graph, currentPath->currentDistrito, nextDistrito[i]);
                    nextPath->graph = newReduction.first;
                    nextPath->nodes = currentPath->nodes;
                    nextPath->nodes.push_back(nextDistrito[i]);
                    nextPath->cost = newReduction.second + currentPath->cost + currentPath->graph[currentPath->currentDistrito][nextDistrito[i]];
                    nextPath->currentDistrito = nextDistrito[i];
                    #pragma omp critical
                    queue.push(nextPath);
                }
            }
        }
    }
    return optimalPath;
}
