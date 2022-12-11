/*
    Este movimento se baseia em fazer o swap entre dois itens 
    (respeitando as restrições) e verificar se abriu espaço
    em um dos trenós para colocar um item que estava no treno
    com menos itens. Se abriu espaço, então o item é movido 
    para o trenó que abriu espaço. Se não abriu espaço, 
    então o movimento é descartado.
*/

#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <time.h>

using namespace std;

/*
    TODO:   Ajustar a função de checking, pois ainda dá resultados inesperados             
*/


bool checking(vector<vector<int>> &L, int &item, vector<int> t, vector<int> p, int Q) {
    /*  
        Se for possível, fazer o swap e retornar true
        Se não for possível, retornar false
    */ 

    for (int i = 0; i < L.size(); i++) {   
        if (L[i][0] == t[item]) {
            for (int j = 0; j < t.size(); j++) {
                if (t[j] == L[i][1]) {
                    return false; // não é possível fazer o swap
                }
            }
        }
        if (L[i][1] == t[item]) {
            for (int j = 0; j < t.size(); j++) {
                if (t[j] == L[i][0]) {
                    return false; // não é possível fazer o swap
                }
            }
        }
    }

    int sum_w = 0;
    for (int i=0; i < t.size(); i++) {
        sum_w += p[t[i]];      
    }


    if ((sum_w + p[t[item]]) > Q) {
        return false;
    }


    return true; 
}

bool reinsertion(vector<vector<int>> &L, vector<vector<int>> &sol, int &item, int t, vector<int> p, int Q) {
    /*  Reinsere o item no trenó com menos itens
        Se não for possível, então o item é descartado
    */

    for (int k = 0; k < sol.size(); k++) {
        if (k != t) {
            if (checking(L, item, sol[k], p, Q)){
                sol[k].push_back(sol[t][item]);
                return true;
            }
        }
    }

    return false;
    
}


int fo(vector<vector<int>> solution) {
    int value = 0;
    for (auto &v : solution) {
        if (v.size() != 0) {
            value++;
        };
    }

    return value;
}


vector<vector<int>> movementReinsetion(vector<vector<int>> &solution, vector<vector<int>> L, vector<int> p, int Q, int k) {

    srand (time(NULL)); // serve para setar uma seed
    /* Não criei lista de itens, utilizei os próprios indices*/

    int best_fo_sol = fo(solution);
    vector<vector<int>> best_sol = solution;

    for (int i = 0; i < solution.size(); i++) {
        
        vector<vector<int>> tempSol;
        tempSol = solution; // copia a solução atual para uma solução temporária

        for (int item = 0; item < tempSol[i].size(); item++) {   
            bool check = reinsertion(L, tempSol, item, i, p, Q);

            if (check) {
                tempSol[i].erase(tempSol[i].begin() + item);
                item--;
            }
        }
        
        if (fo(tempSol) < fo(best_sol)) {
            best_fo_sol = fo(tempSol);
            best_sol = tempSol;
        }
        
        int w;
        for (auto &v : tempSol) {
            w = 0;
            for (auto &i : v) {
                cout << i << " ";
                w += p[i];
            }
                cout << " -> " << w << endl;
        }
        cout << "Função objetivo: " << fo(tempSol) << endl;
        // for (auto &v : tempSol) {
        //     v.clear();
        // }
    }

    return best_sol;
}



// int main(void) {

//     int k = 3;
//     int Q = 10;
//     vector<int> p{3, 5, 5, 2, 1, 2};
//     vector<vector<int>> solution{{ 0, 4}, 
//                                  { 3, 1 }, 
//                                  { 2, 5 }};
//     vector<vector<int>> L{ { 0, 1 }
//                            };
    

//     cout << "Solution antes do movimento: " << endl;
//     int w;
//     for (auto &v : solution) {
//         w = 0;
//         for (auto &i : v) {
//             cout << i << " ";
//             w += p[i];
//         }
//         cout << " -> " << w << endl;
//     }

//     cout << "Função objetivo: " << fo(solution) << endl;

//     vector<vector<int>> newSol = movementReinsetion(solution, L, p, Q, k);

//     cout << "Solution depois do movimento: " << endl;

//     for (auto &v : newSol) {
//         w = 0;
//         for (auto &i : v) {
//             cout << i << " ";
//             w += p[i];
//         }
//         cout << " -> " << w << endl;
//     }

//     cout << "Função objetivo: " << fo(newSol) << endl;

//     return 0;
// }

