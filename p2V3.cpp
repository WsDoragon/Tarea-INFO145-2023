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

    // Constructor para inicializar el grafo
    Graph(int n) : n(n), adj(n) {}
};

// Estructura para representar un grafo no dirigido ponderado
struct GraphPrime {
    int n; // número de nodos
    vector<vector<pair<int, int>>> adj; // lista de adyacencia

    // Constructor para inicializar el grafo
    GraphPrime(int n) : n(n), adj(n) {}
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
            cout << "Costo de viajar desde el puerto " << port << " hasta la isla " << island << ": " << cost << endl;
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
                cout << "Costo de la ruta más económica hasta el momento: " << cost << " con " << dist_ports[port] << "|" << dist_ships[i][j] << "|" << dist_prime[island] <<endl; // Se imprime el costo de la ruta más económica hasta el momento
                min_cost = cost;
            }
        }
    }
        // Se imprimen los costos de cada arista en el grafo G
    cout << "Grafo G:\n";
    for (int u = 0; u < g.n; u++) {
        for (auto [v, w] : g.adj[u]) {
            cout << "Costo de la arista (" << u << " -> " << v << "): " << w << endl;
        }
    }

    // Se imprimen los costos de cada arista en el grafo G'
    cout << "\nGrafo G':\n";
    for (int u = 0; u < g_prime.n; u++) {
        for (auto [v, w] : g_prime.adj[u]) {
            cout << "Costo de la arista (" << u << " <-> " << v << "): " << w << endl;
        }
    }

    // Se imprimen los valores entre los puertos y las islas habilitadas
        //Aqui esta calculando literalmente la distancia entre la capital continental al peurto y la capital regional del archipielago al puerto
    cout << "\nValores entre puertos y islas:\n";
    for (int i = 0; i < ports.size(); i++) {
        int port = ports[i];
        for (int j = 0; j < islands.size(); j++) {
            int island = islands[j];
            int value = dist[port] + dist_prime[island];
            cout << "Valor entre puerto " << port << " e isla " << island << ": " << value << endl;
        }
    }



    // Se retorna la distancia desde la capital continental hasta la capital regional del archipiélago
    return min_cost;
}

int main() {
    // Se inicializa el grafo G
    Graph g(5);
    addEdge(g, 0, 1, 2);
    addEdge(g, 0, 4, 8);
    addEdge(g, 1, 0, 3);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 4, 3);
    addEdge(g, 2, 0, 4);
    addEdge(g, 2, 3, 6);
    addEdge(g, 3, 2, 5);
    addEdge(g, 3, 4, 9);
    addEdge(g, 4, 3, 2);
    addEdge(g, 4, 2, 2);

    // Se inicializa el grafo G'
    GraphPrime g_prime(9);
    addEdge(g_prime, 0, 1, 1);
    addEdge(g_prime, 0, 4, 3);
    addEdge(g_prime, 0, 8, 12);
    addEdge(g_prime, 0, 3, 5);
    addEdge(g_prime, 1, 4, 2);
    addEdge(g_prime, 2, 8, 2);
    addEdge(g_prime, 3, 8, 5);
    addEdge(g_prime, 3, 5, 4);
    addEdge(g_prime, 4, 2, 1);
    addEdge(g_prime, 4, 6, 4);
    addEdge(g_prime, 5, 8, 3);
    addEdge(g_prime, 6, 3, 7);
    addEdge(g_prime, 6, 8, 2);
    addEdge(g_prime, 7, 5, 7);

    // Se definen los puertos en el continente y las islas habilitadas para recibir barcos
    vector<int> ports = {3, 4};
    vector<int> islands = {0, 1, 3};

    // Se encuentra la ruta más económica desde la capital continental hasta la capital regional del archipiélago
    int cheapest_route = findCheapestRoute(g, g_prime, ports, islands);

    // Se imprime el resultado
    cout << "La distancia mínima para llegar desde los puertos en el continente hasta la capital regional del archipiélago es: " << cheapest_route << endl;

    return 0;
}