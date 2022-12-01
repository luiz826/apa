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

// movimento se swap entre dois itens
void swap(int &i1, int &i2) { 
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

void reinsertion(vector<vector<int>> &L, vector<vector<int>> &sol, int &item, int t, vector<int> p, int Q) {
    /*  Reinsere o item no trenó com menos itens
        Se não for possível, então o item é descartado
    */

    for (int k = 0; k < sol.size(); k++) {
        if (k != t) {
            if (checking(L, item, sol[k], p, Q)){
                sol[k].push_back(sol[t][item]);
                return ;
            }
        }
    }
    
}


int fo(vector<vector<int>> solution) {
    int i;
    for (i = 0; i < solution.size(); i++); 

    return i;
}

int main(void) {

    srand (time(NULL)); // serve para setar uma seed
    
    int k = 3;
    int Q = 10;
    vector<int> p{3, 5, 5, 2, 1, 2};
    vector<vector<int>> solution{{ 0, 4}, 
                                 { 3, 1 }, 
                                 { 2, 5 }};
    vector<vector<int>> L{ { 0, 1 }, 
                           { 2, 3 }};
    

    /* Não criei lista de itens, utilizei os próprios indices*/

    int chooseT1 = rand() % k; // escolhe um trenó aleatório
    int chooseT2 = rand() % k; 
    while (chooseT1 == chooseT2) { // escolhe um trenó aleatório diferente do anterior
        chooseT2 = rand() % k;
    }
    
    int chooseItem1 = rand() % solution[chooseT1].size(); // escolhe um item aleatório do trenó 1
    int chooseItem2 = rand() % solution[chooseT2].size(); // escolhe um item aleatório do trenó 2

    // printa solution antes do movimento   
    cout << "Solution antes do movimento: " << endl;
    int w;
    for (auto &v : solution) {
        w = 0;
        for (auto &i : v) {
            cout << i << " ";
            w += p[i];
        }
        cout << " -> " << w << endl;
    }
    cout << "Função objetivo: " << fo(solution) << endl;

    if ((checking(L, chooseItem1, solution[chooseT2], p, Q)) & (checking(L, chooseItem1, solution[chooseT2], p, Q))) {
        swap(solution[chooseT1][chooseItem1], solution[chooseT2][chooseItem2]); // faz o swap entre os itens
    }
    

    // printa solution depois do movimento Swap
    cout << "Solution depois do movimento Swap: " << endl;
    
    for (auto &v : solution) {
        w = 0;
        for (auto &i : v) {
            cout << i << " ";
            w += p[i];
        }
        cout << " -> " << w << endl;
    }
    cout << "Função objetivo: " << fo(solution) << endl;


    /*  pegar o treno com menor peso entre chooseT1 e chooseT2
        esvaziar o treno e tentar inserir esses itens em outros trenós
    */ 

    int wT1, wT2 = 0;
    for (int i = 0; i < solution[chooseT1].size(); i++) {
        wT1 += p[solution[chooseT1][i]];
    }
    for (int i = 0; i < solution[chooseT2].size(); i++) {
        wT2 += p[solution[chooseT2][i]];
    }
    
    
    if (wT1 < wT2) {
        for (int i = 0; i < solution[chooseT1].size(); i++) {
            
            reinsertion(L, solution, i, chooseT1, p, Q);    
        }

        solution.erase(solution.begin() + chooseT1);

    } else {
        for (int i = 0; i < solution[chooseT2].size(); i++) {
            
            reinsertion(L, solution, i, chooseT2, p, Q);
        }

        solution.erase(solution.begin() + chooseT2);
    }

    // printa solution depois do movimento Reinsertion
    cout << "Solution depois do movimento Reinsertion: " << endl;
    for (auto &v : solution) {
        w = 0;
        for (auto &i : v) {
            cout << i << " ";
            w += p[i];
        }
        cout << " -> " << w << endl;
    }
    cout << "Função objetivo: " << fo(solution) << endl;
    

    return 0;
}

