#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <algorithm>


using namespace std;

int main(){
    vector<vector> grafo1[];
    vector<vector> grafo2[];


    //Grafo del continente
    grafo1[0].push_back({1,2});
    grafo1[0].push_back({5,8});
    grafo1[1].push_back({0,3});
    grafo1[1].push_back({2,1});
    grafo1[1].push_back({5,3});
    grafo1[2].push_back({0,4});
    grafo1[2].push_back({3,6});
    grafp1[3].push_back({2,5});
    grafo1[3].push_back({4,9});
    grafo1[4].push_back({2,2});
    grafo1[4].push_back({3,2});

    //grafo de las islas
    grafo2[0].push_back({1,3});
    grafo2[1].push_back({0,2,3,5});
    grafo2[2].push_back({1,6,9});
    grafo2[3].push_back({0,1,4,6});
    grafo2[4].push_back({3,5});
    grafo2[5].push_back({1,2,4,6,8});
    grafo2[6].push_back({3,5,7});
    grafo2[7].push_back({6,8});
    grafo2[8].push_back({2,5,7});

    //Grafo de Los puertos
    vector<vector> grafoPuertos[];
    grafoPuertos[0].push_back({1,-4});
    grafoPuertos[0].push_back({2,9});
    grafoPuertos[0].push_back({3,7});
    grafoPuertos[1].push_back({0,12});
    grafoPuertos[1].push_back({2,-3});
    grafoPuertos[1].push_back({3,21});

    vector<int> puertos ={3,4}



}