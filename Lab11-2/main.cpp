#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    // Создание графа на 7 вершин
    Graph g(7);

    // Добавление ориентированных ребрер
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(0, 5);
    g.addEdge(5, 4);
    g.addEdge(4, 6);

    // ВАРИАНТ 11: Добавление петли
    g.addEdge(1, 1);

    // 1. Вывод графа
    g.print();
    cout << endl;

    // 2. Обходы (DFS итеративный и BFS) от вершины 0
    g.DFS_iterative(0);
    g.BFS(0);
    cout << endl;

    // 3. ВАРИАНТ 11: Вершины на заданном расстоянии
    // Расстояние 2 от вершины 0
    g.findVerticesAtDistance(0, 2);
    cout << endl;

    // 4. Компоненты связности
    g.findComponents();
    cout << endl;

    // 5. Кратчайший путь от 0 до 6
    g.shortestPath(0, 6);

    return 0;
}