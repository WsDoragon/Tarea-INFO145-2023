#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>
#include <ctime>

#include <climits>
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



map<int, vector<vector<int>>> findWaysToClimbDP(int n, int r, int p, vector<int>& brokenStairs, vector<int> saltos) {
    map<int, vector<vector<int>>> dp; // Mapa de programación dinámica
    vector<int> stairs(n + 1, 0); // Inicializar los escalones
    vector<int> new_path;
    // Marcar los escalones rotos
    for (int i = 0; i < r; i++) {
        stairs[brokenStairs[i]] = 1;
    }

    dp[0].push_back(vector<int>(1, 0)); // Solo hay una forma de empezar: desde el primer escalón

    for (int i = 1; i <= n; i++) {
        if (stairs[i] != 1) {
             // Si el escalón actual está roto, no se puede llegar a él
        

        // Actualizar los caminos para los escalones a los que se puede saltar desde el escalón actual
            for (int j = 0; j < saltos.size() && saltos[j] <= i; j++) {
            //cout << "Con salto: " << saltos[j] << endl;
            if (dp.count(i - saltos[j]) > 0) {
                for (auto& path : dp[i - saltos[j]]) {
                    /*cout << "path: ";
                    for (int k = 0; k < path.size(); k++) {
                        cout << path[k] << " ";
                    }
                    cout << endl;*/
                    new_path = path;
                    new_path.push_back(i);
                    dp[i].push_back(new_path);
                }
            }
        }
        }
    }

    return dp; // Los caminos para el último escalón son la solución del problema
}

int main() {
    int n = 10; // Total de escalones
    int r = 3; // Escalones rotos
    int p = 2; // Base de los saltos (estos serán de la forma p^k)
    vector<int> brokenStairs = {4,5,8}; // Escalones rotos

    //Calcular potencias
    vector<int> saltos;
    int i = 0;
    while (pow(p, i) <= n) {
        int resultado = pow(p, i);
        saltos.push_back(resultado);
        i++;
    }
    unsigned t0, t1;
    t0=clock();
    map<int, vector<vector<int>>> paths = findWaysToClimbDP(n, r, p, brokenStairs, saltos);
    t1 = clock();
    cout << "Total: " << paths[n].size() << endl;

        if (paths[n].size() > 15) {
        int minJumps = INT_MAX;
        int minJumpsIndex = -1;

        for (int i = 0; i < paths[n].size(); i++) {
            if (paths[n][i].size() - 1 < minJumps) {
                minJumps = paths[n][i].size() - 1;
                minJumpsIndex = i;
            }
        }

        if (minJumpsIndex != -1) {
            for (int i = 0; i < paths[n][minJumpsIndex].size(); i++) {
                cout << paths[n][minJumpsIndex][i] << " ";
            }
            cout << endl;
        }
    } else {
        for (auto& path : paths[n]) {
            for (int i = 1; i < path.size(); i++) {
                cout << path[i] << " ";
            }
            cout << endl;
        }
    }

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    return 0;
}