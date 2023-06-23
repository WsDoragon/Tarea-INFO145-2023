#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;
typedef vector<vector<pii>> Graph;

vector<int> dijkstra(const Graph& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() {
    // Grafo del continente
    int n1 = 5; // Número de ciudades en el continente
    Graph graph1(n1);

    // Agregar las rutas entre las ciudades con sus respectivos costos
    graph1[0].push_back(make_pair(1, 2));
    graph1[0].push_back(make_pair(5, 8));
    graph1[1].push_back(make_pair(0, 3));
    graph1[1].push_back(make_pair(2, 1));
    graph1[1].push_back(make_pair(5, 3));
    graph1[2].push_back(make_pair(0, 4));
    graph1[2].push_back(make_pair(3, 6));
    graph1[3].push_back(make_pair(2, 5));
    graph1[3].push_back(make_pair(4, 9));
    graph1[4].push_back(make_pair(2, 2));
    graph1[4].push_back(make_pair(3, 2));

    // Grafo de las islas
    int n2 = 9; // Número de islas
    Graph graph2(n2);

    // Agregar las rutas entre las islas con sus respectivos costos
    graph2[0].push_back(make_pair(1, 1));
    graph2[0].push_back(make_pair(3, 2));
    graph2[1].push_back(make_pair(0, 1));
    graph2[1].push_back(make_pair(2, 5));
    graph2[1].push_back(make_pair(3, 3));
    graph2[1].push_back(make_pair(5, 12));
    graph2[2].push_back(make_pair(1, 4));
    graph2[2].push_back(make_pair(6, 7));
    graph2[2].push_back(make_pair(9, 9));
    graph2[3].push_back(make_pair(0, 2));
    graph2[3].push_back(make_pair(1, 3));
    graph2[3].push_back(make_pair(4, 1));
    graph2[3].push_back(make_pair(6, 9));
    graph2[4].push_back(make_pair(3, 6));
    graph2[4].push_back(make_pair(5, 2));
    graph2[5].push_back(make_pair(1, 2));
    graph2[5].push_back(make_pair(2, 5));
    graph2[5].push_back(make_pair(4, 3));
    graph2[5].push_back(make_pair(6, 4));
    graph2[5].push_back(make_pair(8, 2));
    graph2[6].push_back(make_pair(3, 4));
    graph2[6].push_back(make_pair(5, 6));
    graph2[6].push_back(make_pair(7, 3));
    graph2[7].push_back(make_pair(6, 2));
    graph2[7].push_back(make_pair(8, 4));
    graph2[8].push_back(make_pair(2, 6));
    graph2[8].push_back(make_pair(5, 1));
    graph2[8].push_back(make_pair(7, 2));

    // Grafo de los puertos
    int k = 2; // Número de puertos marítimos
    Graph graphPuertos(k);

    // Agregar las rutas entre los puertos con sus respectivos costos
    graphPuertos[0].push_back(make_pair(0, -4));
    graphPuertos[0].push_back(make_pair(1, 9));
    graphPuertos[0].push_back(make_pair(2, 7));
    graphPuertos[1].push_back(make_pair(0, 12));
    graphPuertos[1].push_back(make_pair(1, -3));
    graphPuertos[1].push_back(make_pair(2, 21));

    vector<int> puertos = {3, 4};

    // Ciudad de origen en el continente
    int source = 0;

    // Obtener las distancias más cortas desde la ciudad de origen en el continente
    vector<int> distContinent = dijkstra(graph1, source);

    // Obtener la ciudad de la capital regional del archipiélago
    int capitalRegional = 5; // Supongamos que la capital regional es la ciudad 3 en el grafo del archipiélago

    // Calcular las distancias desde los puertos marítimos hasta la capital regional del archipiélago
    vector<int> distPuertos(k);
    for (int i = 0; i < k; ++i) {
        distPuertos[i] = distContinent[puertos[i]] + graphPuertos[i][capitalRegional].second;
    }

    // Encontrar la distancia mínima desde los puertos hasta la capital regional
    int minDistance = distPuertos[0];
    for (int i = 1; i < k; ++i) {
        minDistance = min(minDistance, distPuertos[i]);
    }

    cout << "La distancia mínima desde la capital continental hasta la capital regional es: " << minDistance << endl;

    return 0;
}
