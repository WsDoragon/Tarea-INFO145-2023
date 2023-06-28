#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <omp.h>

using namespace std;

void buscaCombi(int escaTotal, const vector<int>& potencias, const vector<int>& rotos, int sum, vector<int>& combinacion, vector<vector<int>>& combiList) {
    if (sum == escaTotal) {
        combiList.push_back(combinacion);
        return;
    }
    if (sum > escaTotal) {
        return;
    }
    for (int num : potencias) {
        if (find(rotos.begin(), rotos.end(), sum + num) == rotos.end()) {
            combinacion.push_back(num);
            buscaCombi(escaTotal, potencias, rotos, sum + num, combinacion, combiList);
            combinacion.pop_back();
        }
    }
}

vector<int> potencias(int escaTotal, int p) {
    vector<int> pots;
    int pote = 1;
    while (pote <= escaTotal) {
        pots.push_back(pote);
        pote *= p;
        if (pote == escaTotal) {
            break;  // Evitar generar potencias adicionales si coincide exactamente con escaTotal
        }
    }
    return pots;
}


vector<int> escaRotos(int r, int escaTotal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribucion(1, escaTotal-1);

    vector<int> escR;
    int i = 0;
    while(i < r){
        int al = distribucion(gen);
        auto it = find(escR.begin(), escR.end(), al);
        if (it == escR.end()) {
            // El número no se encuentra en el vector, añadirlo al final
            escR.push_back(al);
            i++;
        }
    }
    return escR;
}

int menorSaltos(vector<vector<int>>& combiList){
    int men = combiList[0].size();
    int ind = 0;
    for (int i = 1; i < combiList.size(); i++){
        if (combiList[i].size() < men) {
            men = combiList[i].size();
            ind = i;
        }
    }
    return ind;
}

int main() {
    double t1 = omp_get_wtime();
    
    int escaTotal = 80;
    int p = 7;
    int r = 15;

    vector<int> pot = potencias(escaTotal, p);
    vector<int> roto = escaRotos(r, escaTotal);

    vector<vector<int>> combiList;
    vector<int> temp;

    buscaCombi(escaTotal, pot, roto, 0, temp, combiList);

    cout << "combiList: " << combiList.size() << endl;

    cout << "Combinaciones encontradas: " << endl;
    for (const auto& combinacion : combiList) {
        for (int num : combinacion) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "roto: ";
    for (int i : roto) {
        cout << i << " ";
    }
    cout << endl;

    cout << "rotoIndice: ";
    for (int i : roto) {
        cout << i - 1 << " ";
    }
    cout << endl;

    int menor = menorSaltos(combiList);

    cout << "menor indice: " << menor << endl;

    cout << "menor saltos: ";
    for (int i : combiList[menor]){
        cout << i << " ";
    }
    cout << endl;

    cout << "saltos menor: ";     
    int sum = 0;
    for (int i : combiList[menor]){
        sum = sum + i;
        cout << sum << " ";
    }
    cout << endl;


    for (int i = 0; i < escaTotal; i++) {
        if (find(roto.begin(), roto.end(), i + 1) != roto.end()) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }
    cout << endl;
   
    
    
    
    double t2 = omp_get_wtime();
    double t = t2-t1;
    cout << t << " segundos" << endl;   

    return 0;
}