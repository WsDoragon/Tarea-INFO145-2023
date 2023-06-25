#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

// Estructura para representar un grafo dirigido ponderado
struct Graph {
    int n; // número de nodos
    vector<vector<pair<int, int>>> adj; // lista de adyacencia
};

// Estructura para representar un grafo no dirigido ponderado
struct GraphPrime {
    int n; // número de nodos
    vector<vector<pair<int, int>>> adj; // lista de adyacencia
};

// Función para agregar una arista dirigida ponderada al grafo
void addEdge(Graph& g, int u, int v, int w) {
    g.adj[u].push_back({v, w});
}

// Función para agregar una arista no dirigida ponderada al grafo
void addEdge(GraphPrime& g, int u, int v, int w) {
    g.adj[u].push_back({v, w});
    g.adj[v].push_back({u, w});
}

// Función para encontrar la ruta más económica desde la capital continental hasta la capital regional del archipiélago
int findCheapestRoute(Graph& g, GraphPrime& g_prime, vector<int>& ports, vector<int>& islands) {
    // Se inicializan las distancias desde la capital continental hasta cada nodo del grafo G y del grafo G'
    vector<int> dist(g.n, numeric_limits<int>::max());
    vector<int> dist_prime(g_prime.n, numeric_limits<int>::max());

    // Se inicializan las distancias desde la capital continental hasta los puertos del continente
    vector<int> dist_ports(g.n, numeric_limits<int>::max());
    for (int port : ports) {
        dist_ports[port] = 0;
    }

    // Se inicializan las distancias desde los puertos del continente hasta las islas habilitadas para recibir barcos
    vector<vector<int>> dist_ships(ports.size(), vector<int>(islands.size(), numeric_limits<int>::max()));
    for (int i = 0; i < ports.size(); i++) {
        for (int j = 0; j < islands.size(); j++) {
            int port = ports[i];
            int island = islands[j];
            int cost = rand() % 101 - 50; // Se genera un costo aleatorio entre -50 y 50
            dist_ships[i][j] = cost;
        }
    }

    // Se aplica el algoritmo de Dijkstra para encontrar las distancias desde la capital continental hasta cada nodo del grafo G
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto [v, w] : g.adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Se aplica el algoritmo de BFS para encontrar las distancias desde la capital regional del archipiélago hasta cada isla habilitada para recibir barcos
    queue<int> q;
    vector<bool> visited(g_prime.n, false);
    for (int island : islands) {
        q.push(island);
        visited[island] = true;
        dist_prime[island] = 0;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : g_prime.adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist_prime[v] = dist_prime[u] + w;
                q.push(v);
            }
        }
    }

    // Se busca la ruta más económica desde la capital continental hasta la capital regional del archipiélago
    int min_cost = numeric_limits<int>::max();
    for (int i = 0; i < ports.size(); i++) {
        int port = ports[i];
        for (int j = 0; j < islands.size(); j++) {
            int island = islands[j];
            int cost = dist_ports[port] + dist_ships[i][j] + dist_prime[island];
            if (cost < min_cost) {
                min_cost = cost;
            }
        }
    }

    // Se retorna la distancia desde la capital continental hasta la capital regional del archipiélago
    return min_cost;
}

int main() {
    // Se inicializa el grafo G
    Graph g;
    g.n = 5;
    g.adj.resize(g.n);
    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 2, 5);
    addEdge(g, 1, 2, 2);
    addEdge(g, 1, 3, 1);
    addEdge(g, 2, 1, 3);
    addEdge(g, 2, 3, 9);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 4, 4);

    // Se inicializa el grafo G'
    GraphPrime g_prime;
    g_prime.n = 9;
    g_prime.adj.resize(g_prime.n);
    addEdge(g_prime, 0, 1, 5);
    addEdge(g_prime, 0, 2, -2);
    addEdge(g_prime, 0, 3, 3);
    addEdge(g_prime, 1, 4, 1);
    addEdge(g_prime, 1, 5, 2);
    addEdge(g_prime, 2, 6, 4);
    addEdge(g_prime, 2, 7, -1);
    addEdge(g_prime, 3, 8, 2);

    // Se definen los puertos y las islas habilitadas para recibir barcos desde el continente
    vector<int> ports = {0, 2};
    vector<int> islands = {1, 2, 4};

    // Se encuentra la ruta más económica desde la capital continental hasta la capital regional del archipiélago
    int cheapest_route = findCheapestRoute(g, g_prime, ports, islands);

    // Se imprime la ruta más económica
    cout << "La ruta más económica desde la capital continental hasta la capital regional del archipiélago es: " << cheapest_route << endl;

    return 0;
}