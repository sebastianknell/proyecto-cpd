//
// Created by Sebastian Knell on 2/07/22.
//
#include <random>
#include "tsp.h"

class Tester {
    static Graph* generateGraph(int n) {
        auto graph = new Graph(n, vector<double>(n));
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist(0,n*100);
        for (int i = 0; i < graph->size(); i++) {
            for (int j = 0; j < graph->front().size(); j++) {
                (*graph)[i][j] = dist(rng) / 100.0;
            }
        }
        return graph;
    }

    static void testParallel(int n, int maxThreads) {
        vector<int> threads = {2, 4, 6, 8, 10, 12};
        vector<double> times;
        auto testGraph = generateGraph(n);
        for (auto t : threads) {
            if (t >= maxThreads) break;
            int iterations = 10;
            double avg = 0;
            omp_set_num_threads(t);
            for (int i = 0; i < iterations; i++) {
                auto t1 = omp_get_wtime();
                ParallelBAB(*testGraph, 0);
                auto t2 = omp_get_wtime();
                avg += t2-t1;
            }
            avg /= iterations;
            times.push_back(avg);
        }
        cout << "Resultados para n = "<< n << endl;
        for (int i = 0; i < times.size(); i++) {
            cout << "# de threads = " << threads[i] << " | " << "tiempo = " << times[i] << endl;
        }
    }
};