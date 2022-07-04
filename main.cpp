#include "tsp.h"
#include "tester.cpp"

int main() {
    Graph cities = {
            {0.0,  4.4, 7.1,  10.5, 3.8,  13.4, 13.7, 3.3,  6.8,  7.1},  // Distancias de LIMA CENTRO a todos los demas
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

    Graph traffic = {
            {0.0,  1.2,  2.2,  0.9,  1.2,  1.0,  2.3,  0.7,  1.3,  1.1},  // Cantidad de trafico de LIMA CENTRO a todos los demas
            {1.2,  0.0,  0.8,  1.1,  0.9,  1.0,  1.3,  0.9,  1.1,  0.7},  // Cantidad de trafico de LINCE a todos los demas
            {1.1,  1.0,  0.0,  1.3,  1.3,  1.0,  2.4,  1.2,  1.1,  0.8},  // Cantidad de trafico de MIRAFLORES a todos los demas
            {0.7,  0.9,  3.0,  0.0,  1.1,  1.2,  0.8,  0.9,  1.0,  0.9},  // Cantidad de trafico de BARRANCO a todos los demas
            {1.0,  1.0,  1.1,  1.2,  0.0,  2.2,  1.0,  0.9,  3.2,  1.0},  // Cantidad de trafico de RIMAC a todos los demas
            {1.0,  3.0,  2.0,  2.3,  0.7,  0.0,  1.5,  2.1,  3.2,  1.3},  // Cantidad de trafico de LOS OLIVOS a todos los demas
            {1.0,  3.2,  1.4,  1.5,  1.3,  3.4,  0.0,  4.5,  3.2,  3.5},  // Cantidad de trafico de LA MOLINA a todos los demas
            {3.3,  2.8,  0.7,  1.0,  6.6,  2.1,  0.9,  0.0,  0.8,  2.3},  // Cantidad de trafico de LA VICTORIA a todos los demas
            {3.5,  4.5,  5.7,  1.2,  1.5,  1.4,  2.2,  2.3,  0.0,  2.1},  // Cantidad de trafico de MAGDALENA DEL MAR a todos los demas
            {3.2,  5.0,  0.7,  1.0,  3.2,  0.8,  0.9,  4.1,  2.4,  0.0}   // Cantidad de trafico de SAN BORJA a todos los demas
    };

    vector<string> names = {"Lima Centro", "Lince", "Miraflores", "Barranco", "Rimac", "Los Olivos", "La Molina", "La Victoria", "Magdalena del Mar", "San Borja"};

    int n;
    int x;
    omp_set_num_threads(2);
    vector<int> finalCities = {};
    cout<<"Ingrese el numero de ciudades que desee considerar: ";
    cin>>n;
    if(n>10 || n<1){cout<<"Numero invalido\n"; return 0;}
    cout<<"\nIngrese las ciudades que desee considerar:\n\n";
    for(int i = 0; i<names.size(); i++){
        cout<<names[i]<<" ("<<i<<")"<<"\n";
    }
    cout << endl;
    for(int i = 0; i<n; i++){
        cout << "> ";
        cin>>x;
        if(x<10 & x>=0) finalCities.push_back(x);
        else {cout<<"Numero de ciudad invalido\n"; return 0;}
    }
    cout << endl;
    cout<<"Ingrese metodo de resolucion:\n";
    cout<<"0. Sequential BAB\n";
    cout<<"1. Parallel BAB\n";
    cout<<"2. Sequential BAB with additional cost\n";
    cout<<"3. Parallel BAB with additional cost\n";
    cout << "> ";
    cin>>n;

    if(n>3 || n<0){cout<<"Numero invalido\n"; return 0;}

    Path* path;
    PathExtra* path2;

    switch (n) {
        case 0:
            path = SequentialBABOpt(cities, finalCities[0], finalCities);
            printPath(path, names);
            break;
        case 1:
            path = ParallelBABOpt(cities, finalCities[0], finalCities);
            printPath(path, names);
            break;
        case 2:
            path2 = SequentialBABCostOpt(cities, finalCities[0],traffic, finalCities);
            printPath(path2, names);
            break;
        case 3:
            path2 = ParallelBABCostOpt(cities, finalCities[0],traffic, finalCities);
            printPath(path2, names);
            break;
        default:
            cout<<"Numero invalido";
    }


    return 0;
}
