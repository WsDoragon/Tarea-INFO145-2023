#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
using namespace std;

/**/
/* // Funcion recusiva que encuentra todas las formas de subir la escalera */
/* void findPaths(vector<int>& stairs, int n, int r, int p, int current, vector<int>& path, vector<vector<int>>& paths, unordered_map<int, vector<vector<int>>>& memo) { */
/*     // Si se llega al escalón n-esimo (la meta), se agrega el camino actual a la lista de caminos encontrados */
/*     if (current == n) { */
/*         paths.push_back(path); */
/*         return; */
/*     } */
/**/
/*     // Se evalua si nuestro escalon actual se encuentra roto, si no lo esta se continua la busqueda de caminos para el escalon actual */
/*     if (stairs[current] != 1) { */
/*         for (int i = 0; pow(p, i) < n ; i++) { */
/*             int next = current + pow(p, i); */
/*             if (next <= n) { */
/*                 path.push_back(next); */
/*                 if (memo.find(next) != memo.end()) { */
/*                     // El resultado ya está en la tabla de memoizacion, lo usamos directamente */
/*                     for (const auto& subpath : memo[next]) { */
/*                         //cout<< subpath[0] << endl; */
/*                         vector<int> updatedPath = path; */
/*                         updatedPath.insert(updatedPath.end(), subpath.begin(), subpath.end()); */
/*                         if (updatedPath.back() == n) { */
/*                             paths.push_back(updatedPath); */
/*                         } */
/*                     } */
/*                 } else { */
/*                     findPaths(stairs, n, r, p, next, path, paths, memo); */
/*                 } */
/*                 path.pop_back(); */
/*             } */
/*         } */
/*     } */
/**/
/*     // Guardar el resultado parcial en la tabla de memoización */
/*     memo[current] = paths; */
/* } */
/**/
/* // Funcion para encontrar las formas de subir la escalera */
/* vector<vector<int>> findWaysToClimb(int n, int r, int p, vector<int>& brokenStairs) { */
/*     vector<vector<int>> paths; */
/*     vector<int> stairs(n + 1, 0); // Inicializamos los escalones como no rotos */
/**/
/*     // Marcamos los escalones rotos para no pisarlos */
/*     for (int i = 0; i < r; i++) { */
/*         stairs[brokenStairs[i]] = 1; */
/*     } */
/**/
/*     unordered_map<int, vector<vector<int>>> memo; */
/*     vector<int> path; */
/*     findPaths(stairs, n, r, p, 0, path, paths, memo); */
/**/
/*     return paths; */
/* } */
/**/
/* void printPaths(vector<vector<int>>& paths) { */
/*     int count = paths.size(); */
/*     cout << "Existen " << count << " formas posibles para llegar sin caerse:" << endl; */
/*     for (int i = 0; i < count; i++) { */
/*         cout << "- Forma " << i + 1 << ": pisando los escalones: "; */
/*         for (int j = 0; j < paths[i].size(); j++) { */
/*             cout << paths[i][j] << " "; */
/*         } */
/*         cout << endl; */
/*     } */
/* } */
/**/



map<int, vector<vector<int>>> findWaysToClimbDP(int n, int r, int p, vector<int>& brokenStairs) {
    map<int, vector<vector<int>>> dp; // Mapa de programación dinámica
    vector<int> stairs(n + 1, 0); // Inicializar los escalones

    // Marcar los escalones rotos
    for (int i = 0; i < r; i++) {
        stairs[brokenStairs[i]] = 1;
    }

    dp[0].push_back(vector<int>(1, 0)); // Solo hay una forma de empezar: desde el primer escalón

    for (int i = 1; i <= n; i++) {
        if (stairs[i] == 1) {
            continue; // Si el escalón actual está roto, no se puede llegar a él
        }

        // Actualizar los caminos para los escalones a los que se puede saltar desde el escalón actual
        for (int j = 0; pow(p, j) <= i; j++) {
            for(auto& path : dp[i - pow(p, j)]) {
                vector<int> new_path = path;
                new_path.push_back(i);
                dp[i].push_back(new_path);
            }
        }
    }

    return dp; // Los caminos para el último escalón son la solución del problema
}



int main() {
    int n = 10; // Total de escalones
    int r = 3; // Escalones rotos
    int p = 2; // Base de los saltos (estos seran de la forma p^k)
    vector<int> brokenStairs = {4, 5, 8}; // Escalones rotos
  
    map<int, vector<vector<int>>> paths = findWaysToClimbDP(n, r, p, brokenStairs);
   
    cout << "Total: " << paths[n].size() << endl;

    for (auto& path : paths[n]) {
        for (int i = 1; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
