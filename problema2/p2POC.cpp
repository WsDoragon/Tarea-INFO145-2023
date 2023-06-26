#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<pair<int, bool>> findMostEconomicalRoute(unordered_map<int, unordered_map<int, int>>& G, unordered_map<int, unordered_map<int, int>>& G_prime, int s, int z, int k) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, bool> visited;
    unordered_map<int, int> distance;
    unordered_map<int, int> prev;

    for (auto it = G.begin(); it != G.end(); it++) {
        distance[it->first] = numeric_limits<int>::max();
        prev[it->first] = -1;
    }
    for (auto it = G_prime.begin(); it != G_prime.end(); it++) {
        distance[it->first] = numeric_limits<int>::max();
        prev[it->first] = -1;
    }

    pq.push(make_pair(0, s));
    distance[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;

        if (G.find(u) != G.end()) {
            for (auto it = G[u].begin(); it != G[u].end(); it++) {
                int v = it->first;
                int weight = it->second;
                if (!visited[v] && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    prev[v] = u;
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
        if (G_prime.find(u) != G_prime.end()) {
            for (auto it = G_prime[u].begin(); it != G_prime[u].end(); it++) {
                int v = it->first;
                int weight = it->second;
                if (!visited[v] && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    prev[v] = u;
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
    }

    vector<pair<int, bool>> path;
    int u = z;
    while (prev[u] != -1) {
        path.push_back(make_pair(u, G.find(prev[u]) != G.end()));
        u = prev[u];
    }
    path.push_back(make_pair(u, G.find(prev[u]) != G.end()));
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    srand(time(NULL));

    unordered_map<int, unordered_map<int, int>> G;
    int n = 5;
    int m = 9;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int weight = rand() % 100 + 1;
            G[i][j] = weight;
            G[j][i] = weight;
        }
    }

    unordered_map<int, unordered_map<int, int>> G_prime;
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            int weight = rand() % 100 + 1;
            G_prime[i][j] = weight;
            G_prime[j][i] = weight;
        }
    }

    int s = rand() % n + 1;
    int z = rand() % m + 1;
    while (z == s) {
        z = rand() % m + 1;
    }

    cout << "Start node: City " << s << endl;
    cout << "End node: Island " << z << endl;

    int k = 2;

    cout << "Cities:" << endl;
    for (auto it = G.begin(); it != G.end(); it++) {
        cout << "City " << it->first << ":" << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "  -> City " << it2->first << " (weight " << it2->second << ")" << endl;
        }
    }

    cout << "Islands:" << endl;
    for (auto it = G_prime.begin(); it != G_prime.end(); it++) {
        cout << "Island " << it->first << ":" << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << "  -> Island " << it2->first << " (weight " << it2->second << ")" << endl;
        }
    }

    vector<pair<int, bool>> path = findMostEconomicalRoute(G, G_prime, s, z, k);

    cout << "Most economical path from City " << s << " to Island " << z << ":" << endl;
    for (auto it = path.begin(); it != path.end(); it++) {
        if (it->second) {
            cout << "City " << it->first << endl;
        } else {
            cout << "Island " << it->first << endl;
        }
    }

    return 0;
}
