#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int formasPD(std::vector<int>& A, int n, std::vector<int>& B, int k, std::vector<bool>& escalones_rotos, std::vector<std::vector<int>>& formas) {
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


int main(){
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

    for (int i = 0; i < saltos.size(); i++){
        cout << saltos[i] << endl;
    }

    //Escalones
    vector<int> escalonesRotos;
    escalonesRotos.push_back(4);
    escalonesRotos.push_back(5);
    escalonesRotos.push_back(8);
    escalonesRotos.push_back(9);

/*
    for (int i = 0; i < r; i++){
        int escalon;
        cout << "Ingrese el escalon roto: ";
        cin >> escalon;
        escalonesRotos.push_back(escalon);
    }
*/
    //Escalones rotos
    vector<bool> escalones_rotos(n + 1, false);
    for (int i = 0; i < escalonesRotos.size(); i++){
        escalones_rotos[escalonesRotos[i]] = true;
        cout << escalonesRotos[i] << endl;
    }




    //arreglo auxiliar
    std::vector<int> A(n + 1, 0);


    std::vector<std::vector<int>> formas(n + 1);
    int resultado = formasPD(A, n, saltos, saltos.size(), escalones_rotos, formas);

    std::cout << "Las formas en que se puede llegar a N es: " << resultado << std::endl;

    std::cout << "Formas de saltar los escalones:" << std::endl;
    for (int f : formas[n]) {
        std::cout << f << " ";
    }
    std::cout << std::endl;

    return 0;
    


}