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
    Checa se é possível colocar o item no trenó sem ultrapassar a capacidade de peso
    */ 

    int sum_w = 0;
    for (int i=0; i < treno.size(); i++) {
        sum_w += p[treno[i]-1];      
    }

    if ((sum_w + p[item-1]) > Q) { // Se o peso dos itens já no trenó + o item que quero adicionar for maior que a capacidade Q, retorna false
        return false;
    }

    return true; 
}

void swap(int &i1, int &i2) { 
    /*
    Movimento de vizinhança. 
    */
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

bool reinsertion(vector<vector<int>> &matrix, vector<vector<int>> &sol, int &item, int t, vector<int> p, int Q) {
    /*
    Reinsere o item em outro trenó
    */

    for (int k = 0; k < sol.size(); k++) { // Para cada trenó
        if (k != t) {     // Se o trenó não for ele mesmo
            for (int i = 0; i < sol[k].size(); i++) { // Tenta encaixar o item checando as restrições
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
    /*
    Função objetivo
    */
    int value = 0;
    for (auto &v : solution) {
        if (v.size() != 0) {
            value++;
        };
    }

    return value;
}

vector<vector<int>> movementSwap(vector<vector<int>> solution, vector<vector<int>> matrix, vector<int> p, int Q) {
    /*
    Função que troca o item de um trenó para outro
    */
    srand (time(NULL)); // serve para setar uma seed
    vector<vector<int>> best_sol = solution;
    int tamSol = best_sol.size();

    int i = rand() % tamSol; // escolhe um trenó aleatório
    int j = rand() % tamSol; 
    while (i == j) { // escolhe um trenó aleatório diferente do anterior
        j = rand() % tamSol;
    }

    vector<vector<int>> tempSol;
    tempSol = solution; 

    if ( tempSol[i].size() > 0 && tempSol[j].size() > 0 ) { // Se os dois trenós possuem ao menos 1 item
        int chooseItem1 = rand() % tempSol[i].size(); // escolhe um item aleatório do trenó 1
        int chooseItem2 = rand() % tempSol[j].size(); // escolhe um item aleatório do trenó 2

        // Checa as restrições
        if ((matrix[tempSol[i][chooseItem1]-1][tempSol[j][chooseItem2]-1] != 1) || (matrix[tempSol[j][chooseItem2]-1][tempSol[i][chooseItem1]-1] != 1)) {
            if (checkingWei(tempSol[i][chooseItem1], tempSol[j], p, Q) && checkingWei(tempSol[j][chooseItem2], tempSol[i], p, Q)) {
                swap(tempSol[i][chooseItem1], tempSol[j][chooseItem2]);
            }
        }
        // Checa se a mudança melhora
        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }

    return best_sol;
}

vector<vector<int>> movementReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q) {
    /*
    Função que aplica o movimento de vizinhança tentando esvaziar o trenó t e colocar os itens dele em outro trenó
    */

    int best_fo_sol = fo(solution);
    vector<vector<int>> best_sol = solution;

    for (int i = 0; i < solution.size(); i++) { // Para todos os trenós da solução
        
        vector<vector<int>> tempSol;
        tempSol = solution; // copia a solução atual para uma solução temporária

        for (int item = 0; item < tempSol[i].size(); item++) { // Para cada item do trenó      
            bool check = reinsertion(matrix, tempSol, item, i, p, Q); // Tento reinserir o item em outro trenó que respeita as condições
            if (check) {
                tempSol[i].erase(tempSol[i].begin() + item); // Caso insira, eu apago o item do trenó atual
                item--;
            }
        }
        // Checa se a solução melhorou
        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }

    return best_sol;
}

vector<vector<int>> movementSwapReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q) {
    /*
    Função que aplica o movimento de vizinhança tentando esvaziar o trenó t e colocar os itens dele em outro trenó
    fazendo o swap antes.
    */
    int best_fo_sol = fo(solution);
    vector<vector<int>> best_sol = solution;

    for (int i = 0; i < solution.size(); i++) {
        
        vector<vector<int>> tempSol;
        tempSol = solution; // copia a solução atual para uma solução temporária

        for (int item = 0; item < tempSol[i].size(); item++) {  

            tempSol = movementSwap(tempSol, matrix, p, Q);            
            bool check = reinsertion(matrix, tempSol, item, i, p, Q);
            if (check) {
                tempSol[i].erase(tempSol[i].begin() + item);
                item--;
            }
        }

        
        if (fo(tempSol) < fo(best_sol)) {
            best_sol = tempSol;
        }
    }

    return best_sol;
}

void greedyalgorithm(ProblemData &data, vector<vector<int>> &sol) {
    /*
    Algoritmo guloso para distribuir os presentes entre os trenós
    Tendo como critério guloso inserir os itens com maior peso primeiro.
    */
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
    // Estrutura utilizada para ordenar os presentes pelo peso
    multimap<int, int>::iterator itr;
    for (itr = presentesPesos.begin(); itr != presentesPesos.end(); itr++) {
        presentes.push_back(itr->second); // Vetor com o indice dos presentes
        pesosOrd.push_back(itr->first); // Vetor com o peso dos presentes
    }
    
    for (int i = data.numeroPresentes-1; i > 0; i--) { // Para cada presente na lista de presentes
        int menor = 0;
        int flag = 0;
        int aux_treno = 0;
        while (flag != 1) {// While para a mudança de trenós
            
            if (trenos[aux_treno].capacidade_atual == data.Q) { // Se o trenó estiver vazio
                trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]); // Adiciona o presente ao trenó

                flag = 1;
            }
            else { // Se o trenó não estiver vazio
                treno copy_treno = trenos[aux_treno];
                if ((trenos[aux_treno].capacidade_atual - pesosOrd[i]) >= 0){  // Checa se o presente cabe
                    int flagNaoConflito = 0; // Isso é pra não adicionar o item no trenó se ele tiver conflito com algum item que já está no trenó
                    int flagTotal = 0;
                    for (int j = 0; j < copy_treno.n_presentes; j++) { // Para todos os itens que já estão no trenó
                        flagTotal++;
                        // Checa se permite pela restrição de compatibilidade
                        if ((data.matrix[presentes[i]-1][trenos[aux_treno].presentes[j].id-1] == 1) || (data.matrix[trenos[aux_treno].presentes[j].id-1][presentes[i]-1] == 1)) { // Se o item que quer adicionar tem conflito com algum item que já está no trenó]) {
                            aux_treno++;
                            break;
                        } else {
                            flagNaoConflito++;
                        }                        
                    }

                    if (flagNaoConflito == flagTotal) { // Se passou por tudo, pode adicionar no indice
                        trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]); // Se passou por tudo, pode adicionar no indice
                        flag = 1;
                    }

                } else {
                    aux_treno++;
                }
            }

        }         
        
    }    
    // Alocando o tamanho necessário para a solução
    int fo = 0;
    for (int i = 0; i < data.k; i++) {
        if (trenos[i].n_presentes > 0) {
            fo++;
        }
    }
    sol.resize(fo);
    
    // Inserindo no vetor solução os trenós com os presentes
    for (int i = 0; i < data.k; i++) {
        if (trenos[i].n_presentes > 0) {
            vector<int> presentes_i = trenos[i].getPresentes();
            for (int j = 0; j < presentes_i.size(); j++) {            
                sol[i].push_back(presentes_i[j]);
            }            
        }
    }
}

void vnd(vector<vector<int>> &solution, ProblemData &data) {
    /*
    Heurística que aplica os movimentos de vizinhança
    */
    int mov = 1;
    int r = 2;
    vector<vector<int>> sol_ = solution;
    while (mov <= r) {
        
        switch (mov) {
            case 1:
                sol_ = movementReinsetion(sol_, data.matrix, data.p, data.Q); // Reisertion 
                break;
            case 2:
                sol_ = movementSwapReinsetion(sol_, data.matrix, data.p, data.Q); //Swap & Reinsertion 
                break;
        }

        if (fo(sol_) < fo(solution)) {
            mov = 1;
            solution = sol_;
        } else {
            mov++;
        }        
    }

}

vector<vector<int>> naivePertubation(vector<vector<int>> solution, ProblemData &data) {
    /*
    Pertubação criada para aplicação do ILS. Critério de perturbação: 
    Para cada trenó 
    Se o trenó tiver solução com tamanho maior que um
    pega o proximo presente depois do primeiro e joga em um trenó vazio.
    */
    vector<vector<int>> pertubation = solution;
    
    pertubation.resize(data.k);

    int proxTreno = 0;
    int tamSolucao = fo(solution);

    for (int i=0; i < tamSolucao; i++) { // Para cada trenós com soluções
        if (solution[i].size() > 1) {
            pertubation[tamSolucao+proxTreno].push_back(solution[i][1]); // o 1 aqui é pra pegar o prox independente de quantos tem a mais
            pertubation[i].erase(pertubation[i].begin() + 1);
            proxTreno++;
        }
        
    } 

    return pertubation;
}

