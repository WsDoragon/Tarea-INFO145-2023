#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

int costBoat(int p, int q, int k, int m) {
    // Check if p is a city with a port and q is an island enabled to receive boats from the mainland
    if (p <= k && q <= pow(2, floor(log2(m)))) {
        // Calculate the cost of the boat trip from city p to island q
        // For example, you can use a distance-based cost function
        int distance = abs(p - q);
        return distance * 10; // Assuming a cost of 10 per unit of distance
    } else {
        // Return a high cost if the boat trip is not possible
        return INT_MAX;
    }
}

vector<int> findMostEconomicalRoute(unordered_map<int, unordered_map<int, int>> G,
                                     unordered_map<int, vector<int>> G_prime,
                                     int s, int z, int k, int m) {
    // Initialize distances to infinity and add start node to queue
    unordered_map<int, int> distances;
    unordered_map<int, bool> visited;
    //auto cmp = [](int a, int b) { return distances[a] > distances[b]; };
    auto cmp = [&distances](int a, int b) { return distances[a] > distances[b]; };
    priority_queue<int, vector<int>, decltype(cmp)> queue(cmp);
    unordered_map<int, int> previous;

    for (auto& node : G) {
        distances[node.first] = INT_MAX;
    }
    distances[s] = 0;
    queue.push(s);

    while (!queue.empty()) {
        int current = queue.top();
        queue.pop();

        if (current == z) {
            // Found shortest path, return it
            vector<int> path;
            int node = z;
            while (node != s) {
                path.insert(path.begin(), node);
                node = previous[node];
            }
            path.insert(path.begin(), s);
            return path;
        }

        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        for (auto& neighbor : G[current]) {
            int distance = neighbor.second;
            int alt = distances[current] + distance;
            if (alt < distances[neighbor.first]) {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = current;
                queue.push(neighbor.first);
            }
        }

        if (G_prime.find(current) != G_prime.end()) {
            for (auto& neighbor : G_prime[current]) {
                if (!visited[neighbor]) {
                    int cost = costBoat(current, neighbor, k, m);
                    int alt = distances[current] + cost;
                    if (alt < distances[neighbor]) {
                        distances[neighbor] = alt;
                        previous[neighbor] = current;
                        queue.push(neighbor);
                    }
                }
            }
        }
    }

    // No path found
    return vector<int>();
}




int main() {
    // Define the directed graph G and the undirected graph G_prime here
    unordered_map<int, unordered_map<int, int>> G = {
        {1, {{2, 5}, {3, 3}}},
        {2, {{4, 1}}},
        {3, {{4, 2}, {5, 6}}},
        {4, {{5, 4}}},
        {5, {}}
    };

    unordered_map<int, vector<int>> G_prime = {
        {1, {2, 3}},
        {2, {1}},
        {3, {1, 4}},
        {4, {3, 5}},
        {5, {4}}
    };

    // Call the findMostEconomicalRoute function with the given parameters
    vector<int> path = findMostEconomicalRoute(G, G_prime, 1, 5, 2, 9);

    // Print the resulting path
    cout << "Most economical path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
