#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

// Definición de la estructura de datos para representar un grafo dirigido
struct Edge {
    int dest; // Nodo destino
    int weight; // Peso de la arista
};

struct Graph {
    int n; // Número de nodos
    vector<vector<Edge>> adj; // Lista de adyacencia
};

// Definición de la estructura de datos para representar un grafo no dirigido
struct EdgePrime {
    int dest; // Nodo destino
    int weight; // Peso de la arista
};

struct GraphPrime {
    int n; // Número de nodos
    vector<vector<EdgePrime>> adj; // Lista de adyacencia
};

// Función para agregar una arista a un grafo dirigido
void addEdge(Graph& g, int u, int v, int w) {
    g.adj[u].push_back({v, w});
}

// Función para agregar una arista a un grafo no dirigido
void addEdge(GraphPrime& g, int u, int v, int w) {
    g.adj[u].push_back({v, w});
    g.adj[v].push_back({u, w});
}

// Función para encontrar la ruta más corta desde un nodo de origen a todos los demás nodos en un grafo dirigido
vector<int> dijkstra(const Graph& g, int start) {
    vector<int> dist(g.n, numeric_limits<int>::max()); // Distancias más cortas desde el nodo de origen
    dist[start] = 0; // La distancia más corta desde el nodo de origen a sí mismo es 0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Cola de prioridad para almacenar los nodos a visitar
    pq.push({0, start}); // Agregar el nodo de origen a la cola de prioridad
    while (!pq.empty()) {
        int u = pq.top().second; // Obtener el nodo con la menor distancia desde el nodo de origen
        pq.pop();
        for (const auto& e : g.adj[u]) { // Recorrer los vecinos del nodo u
            int v = e.dest;
            int w = e.weight;
            if (dist[u] + w < dist[v]) { // Si la distancia desde el nodo de origen hasta u más el peso de la arista (u, v) es menor que la distancia actual desde el nodo de origen hasta v
                dist[v] = dist[u] + w; // Actualizar la distancia más corta desde el nodo de origen hasta v
                pq.push({dist[v], v}); // Agregar v a la cola de prioridad
            }
        }
    }
    return dist;
}

// Función para encontrar la ruta más corta desde un nodo de origen a todos los demás nodos en un grafo no dirigido
vector<int> bfs(const GraphPrime& g, int start) {
    vector<int> dist(g.n, numeric_limits<int>::max()); // Distancias más cortas desde el nodo de origen
    dist[start] = 0; // La distancia más corta desde el nodo de origen a sí mismo es 0
    queue<int> q; // Cola para almacenar los nodos a visitar
    q.push(start); // Agregar el nodo de origen a la cola
    while (!q.empty()) {
        int u = q.front(); // Obtener el nodo en el frente de la cola
        q.pop();
        for (const auto& e : g.adj[u]) { // Recorrer los vecinos del nodo u
            int v = e.dest;
            int w = e.weight;
            if (dist[u] + w < dist[v]) { // Si la distancia desde el nodo de origen hasta u más el peso de la arista (u, v) es menor que la distancia actual desde el nodo de origen hasta v
                dist[v] = dist[u] + w; // Actualizar la distancia más corta desde el nodo de origen hasta v
                q.push(v); // Agregar v a la cola
            }
        }
    }
    return dist;
}

// Función para calcular el costo de viajar desde un puerto en el continente a una isla habilitada para recibir barcos
int costoBarco(int pi, int qj) {
    // Aquí puedes definir la función que calcula el costo de viajar desde el puerto pi hasta la isla qj
    // Puedes utilizar la información del grafo G' y los puertos habilitados para recibir barcos desde el continente
    // En este ejemplo, se utiliza una función aleatoria que devuelve un número entre -50 y 50
    return rand() % 101 - 50;
}

int main() {
    // Se crea el grafo G (Continente)
    Graph g;
    g.n = 5;
    g.adj.resize(g.n);
    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 2, 5);
    addEdge(g, 1, 3, 1);
    addEdge(g, 2, 1, 3);
    addEdge(g, 2, 3, 8);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 4, 4);

    // Se crea el grafo G' (Archipiélago)
    GraphPrime g_prime;
    g_prime.n = 9;
    g_prime.adj.resize(g_prime.n);
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

    // Encontrar las distancias más cortas desde la capital continental hasta todos los nodos en G
    vector<int> dist_g = dijkstra(g, 0); // La capital continental es el nodo 0

    // Encontrar las distancias más cortas desde la capital regional del archipiélago hasta todos los nodos en G'
    vector<int> dist_g_prime = bfs(g_prime, 8); // La capital regional del archipiélago es el nodo 8

    // Calcular los costos de construcción de los puertos en el continente
    vector<int> costs(g.n);
    for (int i = 0; i < g.n; i++) {
        costs[i] = dist_g[i] * 1000; // El costo de construcción es la distancia más corta multiplicada por 1000
    }

    // Calcular los costos de viajar desde los puertos del continente a las islas habilitadas para recibir barcos
    vector<int> costs_barco(g_prime.n, numeric_limits<int>::max());
    for (int i = 0; i < g.n; i++) {
        if (i == 1 || i == 2) { // Solo se consideran los puertos habilitados para recibir barcos
            for (int j = 0; j < 3; j++) { // Se consideran las 3 islas habilitadas para recibir barcos
                int qj = pow(2, j); // La isla qj es la isla número 2^j
                int costo = costoBarco(i, qj); // Se calcula el costo de viajar desde el puerto i hasta la isla qj
                if (costo < 0) { // Si el costo es negativo, se aplica una bonificación
                    costo = max(costo, -50); // La bonificación máxima es de -50
                }
                int v = g_prime.n - 1 - j; // El nodo v en G' es el último nodo menos j
                costs_barco[v] = min(costs_barco[v], dist_g[i] * 1000 + costo + dist_g_prime[qj]); // Se actualiza el costo de viajar desde el puerto i hasta la isla qj
            }
        }
    }

    // Encontrar la ruta más económica desde la capital continental hasta la capital regional del archipiélago
    int min_cost = numeric_limits<int>::max();
    for (int i = 0; i < g_prime.n; i++) {
        if (i == 8 || i == 7 || i == 6) { // Solo se consideran las islas habilitadas para recibir barcos
            min_cost = min(min_cost, costs_barco[i]); // Se actualiza el costo mínimo
        }
    }

    // Imprimir la ruta más económica
    cout << "La ruta más económica desde la capital continental hasta la capital regional del archipiélago es: " << min_cost << endl;

    return 0;
}