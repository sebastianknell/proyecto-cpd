#include "tsp.h"

int main() {
    Graph graph = {
        {0.0,  4.4,  7.1,  10.5, 3.8,  13.4, 13.7, 3.3,  6.8,  7.1},  // Distancias de LIMA CENTRO a todos los demas
        {4.4,  0.0,  3.2,  6.9,  7.4,  16.8, 14.3, 2.8,  4.6,  5.8},  // Distancias de LINCE a todos los demas
        {7.1,  3.2,  0.0,  3.9,  10.7, 20.0, 13.5, 5.4,  5.7,  5.2},  // Distancias de MIRAFLORES a todos los demas
        {10.5, 6.9,  3.9,  0.0,  14.1, 23.4, 14.5, 8.3,  8.7,  7.4},  // Distancias de BARRANCO a todos los demas
        {3.8,  7.4,  10.7, 14.1, 0.0,  11.4, 15.9, 6.6,  9.6,  10.3}, // Distancias de RIMAC a todos los demas
        {13.4, 16.8, 20.0, 23.4, 11.4, 0.0,  26.5, 16.5, 16.5, 20.2}, // Distancias de LOS OLIVOS a todos los demas
        {13.7, 14.3, 13.5, 14.5, 15.9, 26.5, 0.0,  13.2, 17.9, 8.8},  // Distancias de LA MOLINA a todos los demas
        {3.3,  2.8,  5.4,  8.3,  6.6,  16.5, 12.3, 0.0,  6.8,  4.3},  // Distancias de LA VICTORIA a todos los demas
        {6.8,  4.6,  5.7,  8.7,  9.6,  16.5, 17.9, 6.8,  0.0,  9.2},  // Distancias de MAGDALENA DEL MAR a todos los demas
        {7.1,  5.8,  5.2,  7.4,  10.3, 20.2, 8.8,  4.3,  9.2,  0.0}   // Distancias de SAN BORJA a todos los demas
    };

    auto path = SequentialBAB(graph, 0);
    if (path) printPath(path);

    return 0;
}
