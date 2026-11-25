#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; // Количество вершин
    vector<vector<int>> adj; // Список смежности

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // Добавление ориентированного ребра (с поддержкой петель)
    void addEdge(int u, int v) {
        adj[u].push_back(v); // Только в одну сторону, так как граф ориентированный
    }

    // Вывод списка смежности
    void print() {
        cout << "Список смежности (ориентированный):" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i]) cout << v << " ";
            cout << endl;
        }
    }

    // 1. ИТЕРАТИВНЫЙ DFS
    void DFS_iterative(int start) {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);

        cout << "DFS (итеративный) от " << start << ": ";
        while (!st.empty()) {
            int v = st.top();
            st.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";

                // Добавление соседей в стек (в обратном порядке для правильного вывода)
                for (int i = adj[v].size() - 1; i >= 0; i--) {
                    int u = adj[v][i];
                    if (!visited[u]) st.push(u);
                }
            }
        }
        cout << endl;
    }

    // 2. BFS
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS от " << start << ": ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
        cout << endl;
    }

    // 3. Поиск вершин на заданном расстоянии
    void findVerticesAtDistance(int start, int targetDist) {
        vector<int> dist(V, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u : adj[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }

        cout << "Вершины на расстоянии " << targetDist << " от " << start << ": ";
        bool found = false;
        for (int i = 0; i < V; i++) {
            if (dist[i] == targetDist) {
                cout << i << " ";
                found = true;
            }
        }
        if (!found) cout << "не найдены";
        cout << endl;
    }

    // 4. ПОИСК КОМПОНЕНТ СВЯЗНОСТИ (слабая связность)
    // Для ориентированного графа ищем компоненты
    void findComponents() {
        vector<bool> visited(V, false);
        int components = 0;

        cout << "\nКомпоненты связности:" << endl;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                components++;
                cout << "Компонента " << components << ": ";

                // Использование BFS для сбора компоненты
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    cout << v << " ";

                    // Проверка исходящих ребер
                    for (int u : adj[v]) {
                        if (!visited[u]) {
                            visited[u] = true;
                            q.push(u);
                        }
                    }
                    // Проверка входящиъ ребер
                    for (int u = 0; u < V; u++) {
                        for (int neighbor : adj[u]) {
                            if (neighbor == v && !visited[u]) {
                                visited[u] = true;
                                q.push(u);
                            }
                        }
                    }
                }
                cout << endl;
            }
        }
        cout << "Всего компонент: " << components << endl;
    }

    // 5. КРАТЧАЙШИЙ ПУТЬ (BFS)
    void shortestPath(int start, int end) {
        vector<int> dist(V, -1);
        vector<int> prev(V, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (v == end) break;

            for (int u : adj[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    prev[u] = v;
                    q.push(u);
                }
            }
        }

        if (dist[end] == -1) {
            cout << "Пути между " << start << " и " << end << " не существует." << endl;
            return;
        }

        vector<int> path;
        for (int v = end; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Кратчайший путь от " << start << " до " << end << ": ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << " (длина: " << dist[end] << ")" << endl;
    }
};