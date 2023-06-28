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

    int numNodesContinente;
    cout << "Ingrese la cantidad de nodos en el grafo dirigido del continente: ";
    cin >> numNodesContinente;

    int numNodesIslas;
    cout << "Ingrese la cantidad de nodos en el grafo no dirigido de las islas: ";
    cin >> numNodesIslas;

    int numPuertosContinente;
    cout << "Ingrese la cantidad de puertos en el continente (excepto la capital): ";
    cin >> numPuertosContinente;

    cout << "La capital del continente es el nodo 1 " << endl;
    cout << "La capital del archipielago es el nodo " << numNodesIslas << endl;

    unsigned t0, t1;
    t0 = clock();
    int numPuertoIslas = static_cast<int>(log2(numNodesIslas));
    
    // Generar los nodos y conexiones del continente
    unordered_map<int, unordered_map<int, int>> graphContinente = generateGraph(numNodesContinente);
    int distance, distance2, node1C, node2C;
    for (int i = 1; i < numNodesContinente; i++) {
        distance = rand() % 20 + 1;
        distance2 = rand() % 20 + 1;
        do {
            node1C = rand() % (numNodesContinente - 1) + 2; // Generar nodos aleatorios diferentes de la capital
            node2C = rand() % (numNodesContinente - 1) + 2; 
        } while (node1C == node2C); // Se  evalua que el nodo no sea el mismo para la conexion

        connectNodes(graphContinente, i, i + 1, distance); // Conexiones dirigidas secuenciales
        connectNodes(graphContinente, node1C, node2C, distance2); // Conexiones dirigidas aleatorias
    }
    

    // Generar los nodos y conexiones de las islas
    unordered_map<int, unordered_map<int, int>> graphIslas = generateGraph(numNodesIslas);
    int capital = numNodesIslas;
    int node1,node2;
    for (int i = 1; i < numNodesIslas; i++) {
        node1 = capital;
        node2 = i;
        int distance = rand() % 20 + 1;
        connectNodesNoDirigido(graphIslas, node1, node2, distance);
    }
    for (int i = 1; i <= numNodesIslas; i++) {
        int numConnections = rand() % (numNodesIslas - 1) + 1; // Número aleatorio de conexiones para cada isla
        for (int j = 0; j < numConnections; j++) {
            int node1, node2;
            do {
                node1 = rand() % (numNodesIslas - 1) + 1; // Generar nodos aleatorios diferentes de la capital
                node2 = rand() % (numNodesIslas - 1) + 1; 
            } while (node1 == node2); // Se  evalua que el nodo no sea el mismo para la conexion
            int distance = rand() % 20 + 1;
            connectNodesNoDirigido(graphIslas, node1, node2, distance); // Conexiones no dirigidas aleatorias
        }
    }

    // Generar una lista con los nodos del continente desde 2 al n-1
    vector<int> viñaDelMar;
    for (int i = 2; i <= numNodesContinente; i++) {
        viñaDelMar.push_back(i);
    }

    // Mezclar la lista de nodos
    random_device rd;
    mt19937 g(rd());
    shuffle(viñaDelMar.begin(), viñaDelMar.end(), g);

    // Seleccionar los primeros r escalones rotos
    vector<int> puertosContinente(viñaDelMar.begin(), viñaDelMar.begin() + numPuertosContinente);

    // Generar una lista con los nodos del continente desde 2 al n-1
    vector<int> islaDePascua;
    for (int i = 1; i <= numNodesIslas-1; i++) {
        islaDePascua.push_back(i);
    }

    // Mezclar la lista de nodos
    shuffle(islaDePascua.begin(), islaDePascua.end(), g);

    // Seleccionar los primeros r escalones rotos
    vector<int> puertosIslas(islaDePascua.begin(), islaDePascua.begin() + numPuertoIslas);

    // Generar la estructura de costo entre puertos
    unordered_map<int, unordered_map<int, int>> puerto_a_puerto = generatePuertoAPuerto(puertosContinente, puertosIslas);

    // Ejecutar el algoritmo de Dijkstra para encontrar las distancias a los puertos en el continente y las islas
    unordered_map<int, int> previousContinente;
    vector<int> distancesContinente = dijkstra(graphContinente, 1, puertosContinente, previousContinente);

    unordered_map<int, int> previousIslas;
    vector<int> distancesIslas = dijkstra(graphIslas, numNodesIslas, puertosIslas, previousIslas);

    if( numNodesContinente < 10 || numNodesIslas < 10){
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
}
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
                vector<int> pathIslas = getPath(numNodesIslas, island, previousIslas);
                
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