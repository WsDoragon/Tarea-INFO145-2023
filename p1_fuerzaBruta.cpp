#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <algorithm>


using namespace std;

// Funcion recusiva que encuentra todas las formas de subir la escalera
void findPaths(vector<int>& stairs, int n, int r, int p, int current, vector<int>& path, vector<vector<int>>& paths) {
    // Si se llega al escalón n-esimo (la meta), se agrega el camino actual a la lista de caminos encontrados
    if (current == n) {
        paths.push_back(path);
        return;
    }

    // Se evalua si nuestro escalon actual se encuentra roto, si no lo esta se continua la busqueda de caminos para el escalon actual
    if (stairs[current] != 1) {
        for (int i = 0; pow(p, i) < n ; i++) {
            int next = current + pow(p, i);
            if (next <= n) {
                path.push_back(next);
                findPaths(stairs, n, r, p, next, path, paths);
                path.pop_back();
            }
            else{
                return;
            }
        }
    }
    else { return;}
}

// Funcion para encontrar las formas de subir la escalera
vector<vector<int>> findWaysToClimb(int n, int r, int p, vector<int>& brokenStairs) {
    vector<vector<int>> paths;
    vector<int> stairs(n + 1, 0); // Inicializamos los escalones como no rotos

    // Marcamos los escalones rotos para no pisarlos
    for (int i = 0; i < r; i++) {
        stairs[brokenStairs[i]] = 1;
    }

    vector<int> path;
    //path.push_back(0); // entregamos el escalon de inicio como el 0
    findPaths(stairs, n, r, p, 0, path, paths);

    return paths;
}


void printPaths(vector<vector<int>>& paths) {
    int count = paths.size();
    cout << "Existen " << count << " formas posibles para llegar sin caerse:" << endl;
    if(paths.size() < 15){ 
    for (int i = 0; i < count; i++) {
        cout << "- Forma " << i + 1 << ": pisando los escalones: ";
        for (int j = 0; j < paths[i].size(); j++) {
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }
    }
}

int main() {
    /*int n, r, p; descomentar luego
    
    // Solicitar al usuario los valores de n, r y p
    cout << "Ingrese el número total de escalones (n): ";
    cin >> n;
    cout << "Ingrese el número de escalones rotos (r): ";
    cin >> r;
    cout << "Ingrese la base de los saltos (p): ";
    cin >> p;
*/
    int n = 10; // Total de escalones
    int r = 3; // Escalones rotos
    int p = 2; // Base de los saltos (estos serán de la forma p^k)

    vector<int> brokenStairs = {4,5,8}; // Escalones rotos

    // Generar aleatoriamente los escalones rotos
    
    srand(time(0));
    /*Descomentar luego
    vector<int> brokenStairs;
    vector<int> misEscalones;
    for (int j = 1 ; j < n; j++){
        misEscalones.push_back(j);
    }

    //generar r random a partir de misEscalones
    random_shuffle(misEscalones.begin(), misEscalones.end());
    cout << "escalones rotos: ";
    for (int i = 0; i < r; i++) {
        brokenStairs.push_back(misEscalones[i]);
        cout << misEscalones[i] << " - ";
        
    }
    cout<< " " << endl;
    */
/*
    for (int i = 0; i < r; i++) {
        int randomStair = rand() % (n + 1);
        brokenStairs.push_back(randomStair);
    }
    */
    unsigned t0, t1;
    t0=clock();
    vector<vector<int>> paths = findWaysToClimb(n, r, p, brokenStairs);
    t1 = clock();
    printPaths(paths);

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    return 0;
}
