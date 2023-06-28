#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void imprimirCaminos(vector<vector<int>>& formas, int n) {
    cout << "Formas de saltar los escalones:" << endl;
    for (int i = 0; i < formas[n].size(); i += 2) {
        cout << formas[n][i] << " ";
    }
    cout << endl;
}

int formasPD(vector<int>& A, int n, vector<int>& B, int k, vector<bool>& escalones_rotos, vector<vector<int>>& formas) {
    for (int j = 0; j < k; j++) {
        if (B[j] <= n && !escalones_rotos[B[j]]) {
            A[B[j]] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (i > B[j] && !escalones_rotos[i - B[j]]) {
                A[i] += A[i - B[j]];
                for (int f : formas[i - B[j]]) {
                    formas[i].push_back(f);
                    formas[i].push_back(B[j]);
                }

            }
        }
    }

    return A[n];
}

int main() {
    int n, r, p;

    cout << "Ingrese el número total de escalones (n): ";
    cin >> n;
    cout << "Ingrese el número de escalones rotos (r): ";
    cin >> r;
    cout << "Ingrese el valor de p: ";
    cin >> p;

    vector<int> saltos;
    int i = 0;
    while (pow(p, i) <= n) {
        int resultado = pow(p, i);
        saltos.push_back(resultado);
        i++;
    }

    vector<int> escalonesRotos;
    escalonesRotos.push_back(4);
    escalonesRotos.push_back(5);
    escalonesRotos.push_back(8);

    vector<bool> escalones_rotos(n + 1, false);
    for (int i = 0; i < escalonesRotos.size(); i++){
        escalones_rotos[escalonesRotos[i]] = true;
        cout << escalonesRotos[i] << endl;
    }

    vector<int> A(n + 1, 0);
    vector<vector<int>> formas(n + 1);
    int resultado = formasPD(A, n, saltos, saltos.size(), escalones_rotos, formas);

    cout << "Las formas en que se puede llegar a N es: " << resultado << endl;

    imprimirCaminos(formas, n);

    return 0;
}
