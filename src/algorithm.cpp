#include <time.h>
#include <random>
#include <map>
#include <chrono>

using namespace std::chrono;

#include "treno.h"
#include "algorithm.h"

#include "presente.h"

using namespace std;

bool checkingWei(int &item, vector<int> treno, vector<int> p, int Q) {
    /*  
        Se for possível, fazer o swap e retornar true
        Se não for possível, retornar false
    */ 

    int sum_w = 0;
    for (int i=0; i < treno.size(); i++) {
        sum_w += p[treno[i]-1];      
    }


    if ((sum_w + p[item-1]) > Q) {
        return false;
    }

    return true; 
}

void swap(int &i1, int &i2) { 
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

bool reinsertion(vector<vector<int>> &matrix, vector<vector<int>> &sol, int &item, int t, vector<int> p, int Q) {
    /*  Reinsere o item no trenó com menos itens
        Se não for possível, então o item é descartado
    */

    for (int k = 0; k < sol.size(); k++) {
        if (k != t) {    
            for (int i = 0; i < sol[k].size(); i++) {
                // cout << "item: " << item << " sol[t][item]: " << sol[t][item] << " sol[k][i]: " << sol[k][i] << " matrix[sol[t][item]-1][sol[k][i]-1]: " << matrix[sol[t][item]-1][sol[k][i]-1] << endl;
                if ((matrix[sol[t][item]-1][sol[k][i]-1] == 0) || matrix[sol[k][i]-1][sol[t][item]-1] == 0) {                    
                    if (checkingWei(sol[t][item], sol[k], p, Q)) {
                        sol[k].push_back(sol[t][item]);
                        return true;
                    }
                }
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

vector<vector<int>> movementSwap(vector<vector<int>> solution, vector<vector<int>> matrix, vector<int> p, int Q) {
    srand (time(NULL)); // serve para setar uma seed
    vector<vector<int>> best_sol = solution;
    // cout << "inicia SWAP" << endl;
    int tamSol = best_sol.size();

    int i = rand() % tamSol; // escolhe um trenó aleatório
    int j = rand() % tamSol; 
    while (i == j) { // escolhe um trenó aleatório diferente do anterior
        j = rand() % tamSol;
    }

    // for (int i = 0; i < solution.size()-1; i++) {
    //     for (int j = i+1; j < solution.size(); j++) {

    vector<vector<int>> tempSol;
    tempSol = solution; 

    if ( tempSol[i].size() > 0 && tempSol[j].size() > 0 ) {
        int chooseItem1 = rand() % tempSol[i].size(); // escolhe um item aleatório do trenó 1
        int chooseItem2 = rand() % tempSol[j].size(); // escolhe um item aleatório do tren


        if ((matrix[tempSol[i][chooseItem1]-1][tempSol[j][chooseItem2]-1] != 1) || (matrix[tempSol[j][chooseItem2]-1][tempSol[i][chooseItem1]-1] != 1)) {
            // cout << "check matrix" << endl;
            if (checkingWei(tempSol[i][chooseItem1], tempSol[j], p, Q) && checkingWei(tempSol[j][chooseItem2], tempSol[i], p, Q)) {
                // cout << "check weight" << endl;
                swap(tempSol[i][chooseItem1], tempSol[j][chooseItem2]);
            }
        }

        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }
        // }

    return best_sol;
}

vector<vector<int>> movementReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q) {


    int best_fo_sol = fo(solution);
    vector<vector<int>> best_sol = solution;

    for (int i = 0; i < solution.size(); i++) {
        
        vector<vector<int>> tempSol;
        tempSol = solution; // copia a solução atual para uma solução temporária

        for (int item = 0; item < tempSol[i].size(); item++) {              
            bool check = reinsertion(matrix, tempSol, item, i, p, Q);
            // cout << check << endl;
            if (check) {
                tempSol[i].erase(tempSol[i].begin() + item);
                item--;
            }
        }
        // cout << "fo: " << fo(tempSol) << endl;
        
        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }

    return best_sol;
}

vector<vector<int>> movementSwapReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q) {
    
    int best_fo_sol = fo(solution);
    vector<vector<int>> best_sol = solution;

    for (int i = 0; i < solution.size(); i++) {
        
        vector<vector<int>> tempSol;
        tempSol = solution; // copia a solução atual para uma solução temporária

        for (int item = 0; item < tempSol[i].size(); item++) {  

            tempSol = movementSwap(tempSol, matrix, p, Q);            
            bool check = reinsertion(matrix, tempSol, item, i, p, Q);
            // cout << check << endl;
            if (check) {
                tempSol[i].erase(tempSol[i].begin() + item);
                item--;
            }
        }
        // cout << "fo: " << fo(tempSol) << endl;
        
        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }

    return best_sol;
}

// void greedyalgorithm(vector<vector<int>> &matrix, vector<int> &p, int numeroPresentes, int &k, int &Q, int &nElemL, vector<vector<int>> &sol) {
void greedyalgorithm(ProblemData &data, vector<vector<int>> &sol) {
    vector<treno> trenos;
    for (int i = 0; i < data.k; i++) {
        trenos.push_back(treno(data.Q)); // i -> id do treno, Q -> capacidade do treno 
    }


    vector<int> presentes;
    vector<int> pesosOrd;
    multimap<int, int> presentesPesos; 
    for (int w = 1; w < data.numeroPresentes+1; w++) {
        presentesPesos.insert(pair<int, int>(data.p[w-1], w));
    }    
    multimap<int, int>::iterator itr;
    for (itr = presentesPesos.begin(); itr != presentesPesos.end(); itr++) {
        presentes.push_back(itr->second);
        pesosOrd.push_back(itr->first);
    }

    // GULOSO DE FATO
    
    for (int i = data.numeroPresentes-1; i > 0; i--) { 
        // cout << "PRESENTE " << presentes[i] << " PESO: " << pesosOrd[i] << endl << endl; 
        // cout << "-----------------------------" << endl;
        int menor = 0;
        int flag = 0;
        int aux_treno = 0;
        while (flag != 1) {// While para a mudança de trenós
            
            if (trenos[aux_treno].capacidade_atual == data.Q) { // Se o trenó estiver vazio
                // cout << "TRENO VAZIO: " << trenos[aux_treno].capacidade_atual << endl;
                // // cout << "Trenó vazio: " << aux_treno << endl;
                // cout << "Primeiro addPresente " << endl;
                trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]);
                // cout << "Indice presente: " << presentes[i] << endl; // Já pode adicionar no indice
                //// cout << "Peso presente: " << pesosOrd[i] << endl;
                flag = 1;
                // // cout << "Adicionou ao trenó vazio. " << endl;
            }
            else {
                // // cout << "Trenó não vazio: " << aux_treno << endl;
                treno copy_treno = trenos[aux_treno];
                // cout << "TRENO NAO VAZIO: " << trenos[aux_treno].capacidade_atual  - pesosOrd[i] << endl;
                if ((trenos[aux_treno].capacidade_atual - pesosOrd[i]) >= 0){  // Se couber
                    // cout << "TRENO NAO VAZIO (MAIOR Q ZERO): " << trenos[aux_treno].capacidade_atual  - pesosOrd[i] << endl;
                    int flagNaoConflito = 0; // Isso é pra não adicionar o item no trenó se ele tiver conflito com algum item que já está no trenó
                    int flagTotal = 0;
                    for (int j = 0; j < copy_treno.n_presentes; j++) { // Para todos os itens que já estão no trenó
                        flagTotal++;
                        if ((data.matrix[presentes[i]-1][trenos[aux_treno].presentes[j].id-1] == 1) || (data.matrix[trenos[aux_treno].presentes[j].id-1][presentes[i]-1] == 1)) { // Se o item que quer adicionar tem conflito com algum item que já está no trenó]) {
                            aux_treno++;
                            // cout << "Entrou na re/strição " << k << endl;
                            break;
                        } else {
                            flagNaoConflito++;
                        }                        
                    }

                    if (flagNaoConflito == flagTotal) { // Se passou por tudo, pode adicionar no indice
                        // cout << "Segundo addPresente " << endl;
                        trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]); // Se passou por tudo, pode adicionar no indice
                        flag = 1;
                    }
                    // cout << "Segundo add presente " << endl;

                    
                    // cout << "Indice presente: " << presentes[i] << endl; // Já pode adicionar no indice
                    // // cout << "Peso presente: " << pesosOrd[i] << endl;

                    // flag = 1; // Muda a flag pra ir pro proximo item do loop            
                            // // cout << "Adicionou ao trenó não vazio. " << endl;
                        //}
                } else {
                    aux_treno++;
                }
            }

        }         
        
    }    
    
    int fo = 0;
    for (int i = 0; i < data.k; i++) {
        if (trenos[i].n_presentes > 0) {
            fo++;
        }
    }
    sol.resize(fo);
    

    for (int i = 0; i < data.k; i++) {
        if (trenos[i].n_presentes > 0) {
            vector<int> presentes_i = trenos[i].getPresentes();
            for (int j = 0; j < presentes_i.size(); j++) {            
                sol[i].push_back(presentes_i[j]);
            }            
        }
    }

    // Print pra ver a capacidade dos trenós
    for (int i = 0; i < data.k; i++){
        if (trenos[i].n_presentes > 0){
            // cout << "Treno " << i << " capacidade atual: " << trenos[i].capacidade_atual << endl;
        }  
    }

}

void vnd(vector<vector<int>> &solution, ProblemData &data) {
    
    int mov = 1;
    int r = 2;
    vector<vector<int>> sol_ = solution;
    while (mov <= r) {
        
        switch (mov) {
            case 1:
                sol_ = movementReinsetion(sol_, data.matrix, data.p, data.Q); // Reisertion 
                // cout << "swap" << endl;
                break;
            case 2:
                sol_ = movementSwapReinsetion(sol_, data.matrix, data.p, data.Q); //Swap & Reinsertion 
                // cout << "rein" << endl;
                break;
        }

        if (fo(sol_) < fo(solution)) {
            mov = 1;
            solution = sol_;
        } else {
            mov++;
        }
        // cout << "Mov: " << mov << endl;
        // cout << "FO: " << fo(solution) << endl;
        
    }

    // return solution;
}

vector<vector<int>> naivePertubation(vector<vector<int>> solution, ProblemData &data) {
    vector<vector<int>> pertubation = solution;
    // Nova ideia: para cada trenó 
    // Se o trenó tiver solução com tamanho maior que um
    // pega o ultimo e joga em um trenó vazio.
    
    pertubation.resize(data.k);

    int proxTreno = 0;
    int tamSolucao = fo(solution);

    for (int i=0; i < tamSolucao; i++) { // Para cada trenós com soluções
        // cout << "Trenó: " << proxTreno << endl;
        // cout << solution[i].size() << endl;
        if (solution[i].size() > 1) {
            pertubation[tamSolucao+proxTreno].push_back(solution[i][1]); // O 1 aqui é pra pegar o prox independente
            pertubation[i].erase(pertubation[i].begin() + 1);
            proxTreno++;
        }
        
    } 

    return pertubation;
}

