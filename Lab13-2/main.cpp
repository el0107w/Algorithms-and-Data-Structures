#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

using namespace std;
using namespace chrono;

// Функция для генерации случайного графа и замера времени
void runBenchmark() {
    cout << "Сравнительная таблица производительности" << endl;
    cout << left << setw(10) << "V"
        << setw(20) << "Плотность"
        << setw(22) << "Прим (мкс)"
        << setw(20) << "Краскал (мкс)" << endl;

    vector<int> sizes = { 100, 200, 500 };
    vector<int> densities = { 20, 80 }; // 20% (разреженный), 80% (плотный)

    for (int V : sizes) {
        for (int density : densities) {
            Graph g(V);
            // Генерация случайного графа
            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    if (rand() % 100 < density) {
                        g.addEdge(i, j, rand() % 100 + 1);
                    }
                }
            }

            // Замер Прима
            auto start = high_resolution_clock::now();
            g.primMST(false);
            auto end = high_resolution_clock::now();
            auto primTime = duration_cast<microseconds>(end - start).count();

            // Замер Краскала
            vector<Edge> sortedEdges = g.getEdges();
            sort(sortedEdges.begin(), sortedEdges.end());
            vector<Edge> mst;

            start = high_resolution_clock::now();
            g.kruskalMST(sortedEdges, mst, false);
            end = high_resolution_clock::now();
            auto kruskalTime = duration_cast<microseconds>(end - start).count();

            cout << left << setw(10) << V
                << setw(20) << (to_string(density) + "%")
                << setw(22) << primTime
                << setw(20) << kruskalTime << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0)); 

    // 1. Демонстрация на конкретном графе
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 5, 5);
    g.addEdge(1, 5, 8);

    g.primMST();
    g.findSecondMST();
    g.networkApplication();

    // 2. Сравнительная таблица
    runBenchmark();

    return 0;
}