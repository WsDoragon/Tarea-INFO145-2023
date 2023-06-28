#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<pii>> Graph;

const int INF = 1e9;

vi dijkstra(int s, const Graph& G, const vector<int>& w) {
    int n = G.size();
    vi dist(n, INF);
    dist[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        for (auto& e : G[u]) {
            int v = e.first;
            int wuv = e.second + w[u];
            if (dist[v] > dist[u] + wuv) {
                dist[v] = dist[u] + wuv;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n = 5, k = 2, m = 9, blog_mc = 3;
    Graph G(n), G_prime(m);
    vector<int> port_dist(n), island_dist(m);
    // Generar grafos aleatorios
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                G[i].push_back({j, rand() % 20 + 1});
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j) {
                G_prime[i].push_back({j, rand() % 20 + 1});
            }
        }
    }
    // Generar distancias aleatorias para los puertos y las islas
    for (int i = 0; i < n; i++) {
        if (i < k) {
            port_dist[i] = rand() % 21 - 10;
        } else {
            port_dist[i] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        if (i < blog_mc) {
            island_dist[i] = rand() % 21 - 10;
        } else {
            island_dist[i] = INF;
        }
    }
    // Ejecutar algoritmo
    vi Puertos = dijkstra(0, G, port_dist);
    vector<vi> Islas;
    for (int i = 0; i < blog_mc; i++) {
        Islas.push_back(dijkstra(i, G_prime, island_dist));
    }
    int minCost = INF, besti = -1, bestj = -1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < blog_mc; j++) {
            int costo = Puertos[i] + rand() % 21 - 10 + Islas[j][m-1];
            if (costo < minCost) {
                minCost = costo;
                besti = i;
                bestj = j;
            }
        }
    }
    cout << "Costo mínimo: " << minCost << endl;
    cout << "Mejor puerto: " << besti << endl;
    cout << "Mejor isla: " << bestj << endl;
    return 0;
}