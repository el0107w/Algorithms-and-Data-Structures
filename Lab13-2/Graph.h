#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;
        if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
        else { parent[rootY] = rootX; rank[rootX]++; }
        return true;
    }
};

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
        edges.push_back(Edge(u, v, weight));
    }

    // Добавлен параметр print, чтобы можно было отключать вывод для замеров
    int primMST(bool print = true) {
        vector<int> minEdge(V, INT_MAX);
        vector<bool> inMST(V, false);
        vector<int> parent(V, -1);
        int totalWeight = 0;

        minEdge[0] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!inMST[j] && (u == -1 || minEdge[j] < minEdge[u])) {
                    u = j;
                }
            }

            if (minEdge[u] == INT_MAX) {
                if (print) cout << "Граф несвязный!" << endl;
                return -1;
            }

            inMST[u] = true;
            totalWeight += minEdge[u];

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < minEdge[v]) {
                    minEdge[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        if (print) {
            cout << "1. Алгоритм Прима" << endl;
            cout << "Рёбра MST:" << endl;
            for (int i = 1; i < V; i++) {
                if (parent[i] != -1) {
                    cout << "  " << parent[i] << " - " << i << " (вес: " << minEdge[i] << ")" << endl;
                }
            }
            cout << "Общий вес MST: " << totalWeight << endl << endl;
        }
        return totalWeight;
    }

    int kruskalMST(const vector<Edge>& sortedEdges, vector<Edge>& mstEdges, bool print = false) {
        DSU dsu(V);
        int totalWeight = 0;
        mstEdges.clear();

        if (print) cout << "2. Алгоритм Краскала" << endl << "Рёбра MST:" << endl;

        for (const Edge& e : sortedEdges) {
            if (dsu.unite(e.u, e.v)) {
                totalWeight += e.weight;
                mstEdges.push_back(e);
                if (print) cout << "  " << e.u << " - " << e.v << " (вес: " << e.weight << ")" << endl;
                if (mstEdges.size() == V - 1) break;
            }
        }

        if (mstEdges.size() != V - 1) return -1;
        return totalWeight;
    }

    // Метод для получения всех рёбер
    vector<Edge> getEdges() const { return edges; }

    void findSecondMST() {
        vector<Edge> sortedEdges = edges;
        sort(sortedEdges.begin(), sortedEdges.end());

        vector<Edge> mstEdges;
        int mstWeight = kruskalMST(sortedEdges, mstEdges, true);

        if (mstWeight == -1) {
            cout << "Граф несвязный, MST не существует." << endl;
            return;
        }
        cout << "Вес первого MST: " << mstWeight << endl;

        int secondMST = INT_MAX;
        for (size_t i = 0; i < mstEdges.size(); i++) {
            vector<Edge> tempEdges;
            for (const Edge& e : sortedEdges) {
                if (e.u == mstEdges[i].u && e.v == mstEdges[i].v && e.weight == mstEdges[i].weight) {
                    continue;
                }
                tempEdges.push_back(e);
            }

            vector<Edge> tempMst;
            int currentWeight = kruskalMST(tempEdges, tempMst, false);
            if (currentWeight != -1 && currentWeight < secondMST && currentWeight != mstWeight) {
                secondMST = currentWeight;
            }
        }

        cout << "Вес второго минимального MST: " << (secondMST == INT_MAX ? -1 : secondMST) << endl << endl;
    }

    void networkApplication() {
        cout << "3. Задача о прокладке сетей" << endl;
        vector<Edge> sortedEdges = edges;
        sort(sortedEdges.begin(), sortedEdges.end());

        vector<Edge> mstEdges;
        int cost = kruskalMST(sortedEdges, mstEdges, false);

        if (cost == -1) {
            cout << "Граф несвязный! Невозможно соединить все города." << endl;
        }
        else {
            cout << "Минимальная стоимость соединения: " << cost << endl;
            cout << "Дороги для строительства:" << endl;
            for (const Edge& e : mstEdges) {
                cout << "  " << e.u << " - " << e.v << " (стоимость: " << e.weight << ")" << endl;
            }
        }
        cout << endl;
    }
};