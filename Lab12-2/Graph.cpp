#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

const int INF = INT_MAX;

class Graph {
private:
    int V;
    vector<vector<int>> adj; // Матрица смежности для весов

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adj[u][v] = weight; // Ориентированный граф
    }

    // 1. АЛГОРИТМ ДЕЙКСТРЫ
    vector<int> dijkstra(int start, vector<int>& prev) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);
        dist[start] = 0;
        prev.assign(V, -1); // Инициализация массива предков

        for (int i = 0; i < V - 1; i++) {
            // Поиск вершины с минимальным расстоянием
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INF) break;
            visited[u] = true;

            // Релаксация соседей
            for (int v = 0; v < V; v++) {
                if (adj[u][v] != 0 && !visited[v]) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                        prev[v] = u; // Запоминить, откуда пришли
                    }
                }
            }
        }
        return dist;
    }

    // Восстановление пути для Дейкстры
    vector<int> getPathDijkstra(int start, int end, const vector<int>& prev) {
        vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        if (path[0] != start) return {}; // Пути не существует
        return path;
    }

    // 2. АЛГОРИТМ ФЛОЙДА-УОРШЕЛЛА
    vector<vector<int>> floydWarshall(vector<vector<int>>& next) {
        vector<vector<int>> dist = adj;

        // Инициализация: если ребра нет - INF, кроме диагонали
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && dist[i][j] == 0) {
                    dist[i][j] = INF;
                }
            }
        }

        // Инициализация матрицы next (следующая вершина на пути)
        next.assign(V, vector<int>(V, -1));
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] != INF && i != j) {
                    next[i][j] = j;
                }
            }
        }

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k]; // Обновление пути
                        }
                    }
                }
            }
        }
        return dist;
    }

    // Восстановление пути для Флойда
    vector<int> getPathFloyd(int u, int v, const vector<vector<int>>& next) {
        if (next[u][v] == -1) return {};
        vector<int> path = { u };
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        return path;
    }

    void printDistances(const vector<int>& dist, int start) {
        cout << "Кратчайшие расстояния от вершины " << start << ":\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF) cout << "  До " << i << ": недостижима\n";
            else cout << "  До " << i << ": " << dist[i] << "\n";
        }
    }
};

// Функция для замера времени
double measureTimeDijkstra(int V) {
    Graph g(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && rand() % 3 == 0) {
                g.addEdge(i, j, rand() % 10 + 1);
            }
        }
    }
    vector<int> prev;
    auto start = high_resolution_clock::now();
    g.dijkstra(0, prev);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

double measureTimeFloyd(int V) {
    Graph g(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && rand() % 3 == 0) {
                g.addEdge(i, j, rand() % 10 + 1);
            }
        }
    }
    vector<vector<int>> next;
    auto start = high_resolution_clock::now();
    g.floydWarshall(next);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main() {
    setlocale(LC_ALL, "");

    // ДЕМОНСТРАЦИЯ РАБОТЫ
    cout << "Демонстрация работы алгоритмов" << endl;
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 1, 3);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 4, 2);

    // Дейкстра
    vector<int> prev;
    auto distD = g.dijkstra(0, prev);
    g.printDistances(distD, 0);

    cout << "\nВосстановленные пути (Дейкстра):" << endl;
    for (int i = 1; i < 5; i++) {
        cout << "  0 -> " << i << " (длина " << distD[i] << "): ";
        vector<int> path = g.getPathDijkstra(0, i, prev);
        for (int v : path) cout << v << " ";
        cout << endl;
    }

    // Флойд
    cout << "\nМатрица кратчайших путей (Флойд-Уоршелл):\n";
    vector<vector<int>> next;
    auto distF = g.floydWarshall(next);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (distF[i][j] == INF) cout << "INF ";
            else cout << setw(4) << distF[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nВосстановленные пути (Флойд):" << endl;
    for (int i = 1; i < 5; i++) {
        cout << "  0 -> " << i << " (длина " << distF[0][i] << "): ";
        vector<int> path = g.getPathFloyd(0, i, next);
        for (int v : path) cout << v << " ";
        cout << endl;
    }

    // СРАВНИТЕЛЬНЫЙ АНАЛИЗ ПРОИЗВОДИТЕЛЬНОСТИ
    cout << "\nСравнительный анализ производительности" << endl;
    cout << left << setw(10) << "V"
        << setw(20) << "Dijkstra (us)"
        << setw(20) << "Floyd-Warshall (us)" << endl;

    vector<int> sizes = { 10, 20, 50, 100 };
    for (int V : sizes) {
        double tD = measureTimeDijkstra(V);
        double tF = measureTimeFloyd(V);
        cout << left << setw(10) << V
            << setw(20) << tD
            << setw(20) << tF << endl;
    }

    return 0;
}