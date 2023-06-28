#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int, int>>& graph, int start, vector<int>& goals, unordered_map<int, int>& previous) {
    // Initialize distances to infinity and add start node to queue
    unordered_map<int, int> distances;
    unordered_map<int, bool> visited;
    auto cmp = [&distances](int a, int b) { return distances[a] > distances[b]; };
    priority_queue<int, vector<int>, decltype(cmp)> queue(cmp);

    for (auto& node : graph) {
        distances[node.first] = INT_MAX;
    }
    distances[start] = 0;
    queue.push(start);

    unordered_map<int, int> result;
    int num_goals_visited = 0;

    while (!queue.empty() && num_goals_visited < goals.size()) {
        int current = queue.top();
        queue.pop();

        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        for (auto& neighbor : graph[current]) {
            int distance = neighbor.second;
            int alt = distances[current] + distance;
            if (alt < distances[neighbor.first]) {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = current;
                queue.push(neighbor.first);
            }
        }

        if (find(goals.begin(), goals.end(), current) != goals.end()) {
            // Found a goal node, add it to the result map
            result[current] = distances[current];
            num_goals_visited++;
        }
    }

    // Convert the result map to a vector and return it
    vector<int> distances_to_goals;
    for (auto& goal : goals) {
        distances_to_goals.push_back(result[goal]);
    }
    return distances_to_goals;
}

int totalCost(vector<int>& distancesContinente, vector<int>& distancesIslas, vector<int>& puertosContinente, vector<int>& puertosIslas, unordered_map<int, unordered_map<int, int>>& puerto_a_puerto) {
    int min_cost = INT_MAX;
    for (int i = 0; i < puertosContinente.size(); i++) {
        int port = puertosContinente[i];
        for (int j = 0; j < puertosIslas.size(); j++) {
            int island = puertosIslas[j];
            int cost = distancesContinente[i] + puerto_a_puerto[port][island] + distancesIslas[j];
            if (cost < min_cost) {
                min_cost = cost;
            }
        }
    }
    return min_cost;
}

vector<int> getPath(int start, int end, unordered_map<int, int>& previous) {
    vector<int> path;
    int current = end;
    while (current != start) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

unordered_map<int, unordered_map<int, int>> generateGraph(int numNodes) {
    unordered_map<int, unordered_map<int, int>> graph;
    for (int i = 1; i <= numNodes; i++) {
        unordered_map<int, int> neighbors;
        graph[i] = neighbors;
    }
    return graph;
}
//Conecta nodos de grafo dirigido
void connectNodes(unordered_map<int, unordered_map<int, int>>& graph, int node1, int node2, int distance) {
    graph[node1][node2] = distance;
}
//conecta nodos de grafo no dirigido
void connectNodesNoDirigido(unordered_map<int, unordered_map<int, int>>& graph, int node1, int node2, int distance) {
    graph[node1][node2] = distance;
    graph[node2][node1] = distance;
}

//Genera los valores para las conexiones entre puerto y puerto
unordered_map<int, unordered_map<int, int>> generatePuertoAPuerto(const vector<int>& shipPortsContinent, const vector<int>& shipPortsIslands) {
    unordered_map<int, unordered_map<int, int>> puerto_a_puerto;

    for (int port : shipPortsContinent) {
        unordered_map<int, int> islandCosts;
        for (int island : shipPortsIslands) {
            int cost = rand() % 20 - 10; // Generar un costo aleatorio entre -10 y 10
            islandCosts[island] = cost;
        }
        puerto_a_puerto[port] = islandCosts;
    }

    return puerto_a_puerto;
}

int main() {
    srand(time(NULL));

        // Define directed graph here
    unordered_map<int, unordered_map<int, int>> graphContinente = {
        {1, {{2, 2}, {5, 8}}},
        {2, {{1, 3}, {3, 1} , {5, 3}}},
        {3, {{1, 4}, {4, 6}}},
        {4, {{3, 5}, {5, 9}}},
        {5, {{3, 2}, {4, 2}}}
    };

    unordered_map<int, unordered_map<int, int>> puerto_a_puerto = {
        {4, {{1, -4} , {2, 9} , {3, 7}}},
        {5, {{1, 12} , {2, -3} , {3, 21}}}
    };

    // Define the undirected graph here
    unordered_map<int, unordered_map<int, int>> graphIslas = {
        {1, {{2 , 1} , {4 , 2} }},
        {2, {{1 , 1} , {3 , 5} , {4 , 3}, {6 , 12}}},
        {3, {{2 , 5} , {6 , 5} , {9 , 4}}},
        {4, {{1 , 2} , {2 , 3} , {5 , 1}, {7 , 4}}},
        {5, {{4 , 1} , {6 , 2}}},
        {6, {{2 , 12} , {5 , 2} , {3 , 5} , {7 , 2} , {9 , 3}}},
        {7, {{4 , 4} , {6 , 2} , {8 , 3}}},
        {8, {{7 , 3} , {9 , 7}}},
        {9, {{3, 4} , {6 , 3} , {8 , 7}}}
    };

    vector<int> puertosContinente = { 4 , 5 };
    vector<int> puertosIslas = { 1 , 2 , 3 };

    unsigned t0, t1;
    t0 = clock();
    // Ejecutar el algoritmo de Dijkstra para encontrar las distancias a los puertos en el continente y las islas
    unordered_map<int, int> previousContinente;
    vector<int> distancesContinente = dijkstra(graphContinente, 1, puertosContinente, previousContinente);

    unordered_map<int, int> previousIslas;
    vector<int> distancesIslas = dijkstra(graphIslas, 6, puertosIslas, previousIslas);

    
     // Print the graph and edge costs
    cout << "Grafo Continente:" << endl;
    for (auto& node : graphContinente) {
        for (auto& neighbor : node.second) {
            cout << "Costo de la arista (" << node.first << " -> " << neighbor.first << "): " << neighbor.second << endl;
        }
    }
    cout << endl;
    // Print the values between ports and islands
    cout << "Valores entre puertos continente y puertos islas:" << endl;
    for (auto& port : puerto_a_puerto) {
        for (auto& island : port.second) {
            cout << "Valor entre la ciudad " << port.first << " e isla " << island.first << ": " << island.second << endl;
        }
    }
    cout << endl;

    cout << "Grafo Islas:" << endl;
    for (auto& node : graphIslas) {
        for (auto& neighbor : node.second) {
            cout << "Costo de la arista (" << node.first << " -> " << neighbor.first << "): " << neighbor.second << endl;
        }
    }
    cout << endl;

    // Calcular el costo total y mostrarlo en pantalla
    int minCost = totalCost(distancesContinente, distancesIslas, puertosContinente, puertosIslas, puerto_a_puerto);
    cout << "El costo mínimo para navegar desde la capital continental hasta la capital de archipielago es: " << minCost << endl;

    // Print the optimal paths
    cout << "Caminos óptimos:" << endl;
    int minCosto = totalCost(distancesContinente, distancesIslas, puertosContinente, puertosIslas, puerto_a_puerto);
    for (int i = 0; i < puertosContinente.size(); i++) {
        int port = puertosContinente[i];
        
        for (int j = 0; j < puertosIslas.size(); j++) {
            int island = puertosIslas[j];
            int cost = distancesContinente[i] + puerto_a_puerto[port][island] + distancesIslas[j];
            if (cost == minCosto) {
                cout << "Desde el puerto " << port << " hasta la isla " << island << ":" << endl;
                
                //obtiene los caminos de costo minimo desde el nodo inicial hasta el nodo objetivo en el archipielago
                vector<int> pathContinente = getPath(1, port, previousContinente);
                vector<int> pathIslas = getPath(6, island, previousIslas);
                
                for (int k = 0; k < pathContinente.size(); k++) {
                    cout << "Ciudad " << pathContinente[k];
                    if (k < pathContinente.size() - 1) {
                        cout << " -> ";
                    }
                }
                for (int k = pathIslas.size()-1; k > -1; k--) {
                    cout << " -> Isla " << pathIslas[k];
                }
                cout << endl;
            }
        }
    }

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    return 0;
}