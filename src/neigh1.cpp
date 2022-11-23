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

// movimento se swap entre dois itens
void swap(int &i1, int &i2) { 
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

bool checkAndSwap(vector<vector<int>> constr, int &i1, int &i2, vector<int> t1, vector<int> t2) {
    /*  Checar os trenós de a e b e ver se é possível fazer o swap 
        Se for possível, fazer o swap e retornar true
        Se não for possível, retornar false
    */ 
    
}

int main(void) {

    srand (time(NULL)); // serve para setar uma seed
    
    int nTrenos = 3;
    vector<int> p{4, 5, 7, 2};
    vector<vector<int>> trenos{ { 0 }, 
                                { 3, 1 }, 
                                { 2 } };
    vector<vector<int>> constr{ { 0, 1 }, 
                                    { 0, 3 }};

    /* Não criei lista de itens, utilizei os próprios indices*/


    int chooseT1 = rand() % nTrenos; // escolhe um trenó aleatório
    int chooseT2 = rand() % nTrenos; 
    while (chooseT1 == chooseT2) { // escolhe um trenó aleatório diferente do anterior
        chooseT2 = rand() % nTrenos;
    }
    
    int chooseItem1 = rand() % trenos[chooseT1].size(); // escolhe um item aleatório do trenó 1
    int chooseItem2 = rand() % trenos[chooseT2].size(); // escolhe um item aleatório do trenó 2

    // printa trenos antes do movimento
    for (auto &v : trenos) { 
        for (auto &i : v) {
            cout << i << " - PESO: " << p[i] << endl;
        }
        cout << endl;
    }
    cout << endl;

    int item1 = trenos[chooseT1][chooseItem1];
    int item2 = trenos[chooseT2][chooseItem2];
    
    swap(item1, item2); // faz o swap entre os itens

    cout << "======================" << endl;
    // printa trenos depois do movimento
    for (auto &v : trenos) {
        for (auto &i : v) {
            cout << i << " - PESO: " << p[i] << endl;
        }
        cout << endl;
    }
}

