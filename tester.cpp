//
// Created by Sebastian Knell on 2/07/22.
//
#include <random>
#include "tsp.h"

class Tester {
public:
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

    static void testSequential(Graph* testGraph, int iterations) {
        double avg = 0;
        for (int i = 0; i < iterations; i++) {
            auto t1 = omp_get_wtime();
            SequentialBAB(*testGraph, 0);
            auto t2 = omp_get_wtime();
            avg += t2-t1;
        }
        cout << "Tiempo secuencial: " << avg/iterations << endl;
    }

    static void testParallel(Graph* testGraph, int maxThreads, int iterations) {
        vector<int> threads = {2, 4, 6, 8, 10, 12};
        vector<double> times;
        for (auto t : threads) {
            if (t > maxThreads) break;
            double avg = 0;
            omp_set_num_threads(t);
            cout << "Prueba con " << t << " threads" << endl;
            for (int i = 0; i < iterations; i++) {
                auto t1 = omp_get_wtime();
                ParallelBAB(*testGraph, 0);
                auto t2 = omp_get_wtime();
                avg += t2-t1;
            }
            avg /= iterations;
            times.push_back(avg);
        }
        cout << "Resultados para n = "<< testGraph->size() << endl;
        for (int i = 0; i < times.size(); i++) {
            cout << "# de threads = " << threads[i] << " | " << "tiempo = " << times[i] << endl;
        }
    }

    static void testWeakScaling(int maxThreads, int iterations) {
        vector<int> threads = {2, 4, 6, 8, 10, 12, 14, 16};
        vector<double> times;
        int n = 10;
        auto testGraph = generateGraph(n);
        testSequential(testGraph, iterations);
        n += 2;
        for (auto t : threads) {
            if (t > maxThreads) break;
            double avg = 0;
            testGraph = generateGraph(n);
            omp_set_num_threads(t);
            cout << "Prueba con " << t << " threads" << endl;
            for (int i = 0; i < iterations; i++) {
                auto t1 = omp_get_wtime();
                ParallelBAB(*testGraph, 0);
                auto t2 = omp_get_wtime();
                avg += t2-t1;
            }
            avg /= iterations;
            times.push_back(avg);
            n += 2;
        }
        cout << "Resultados para n = "<< testGraph->size() << endl;
        for (int i = 0; i < times.size(); i++) {
            cout << "# de threads = " << threads[i] << " | " << "tiempo = " << times[i] << endl;
        }
    }
};