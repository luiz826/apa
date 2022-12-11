#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <time.h>
#include <map>
#include <fstream>

using namespace std;

class presente {
    public:
        int id;
        int peso;
        presente(int id, int peso = 0) {
            this->id = id;
            this->peso = peso;
        }
};

class treno {
    public:
        int capacidade;
        int capacidade_atual;
        int n_presentes = 0;
        vector<presente> presentes;

        treno(int capacidade) {
            this->capacidade = capacidade;
            this->capacidade_atual = capacidade;
        }
        void addPresente(int id, int peso) {
            presente p(id, peso);
            presentes.push_back(p);
            this->n_presentes++;
            this->capacidade_atual -= peso;
        }
         
        void printTreno(int t) {
            // cout << "Treno " << t << " com " << this->n_presentes << " presentes: ";
            for (int i = 0; i < this->n_presentes; i++) {
                cout << this->presentes[i].id << " ";
            }
            // cout << endl;
        }

        vector<int> getPresentes() {
            vector<int> presentes;
            for (int i = 0; i < this->n_presentes; i++) {
                presentes.push_back(this->presentes[i].id);
            }
            return presentes;
        }


};

// class movimento {
    
// };
 //vector<vector<int>> &matrix, 
void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {
    ifstream file(filename);
    string line, space1, space2;
    int line_number = 0;

    file >> line;
    file >> numeroPresentes;
    file >> k;
    file >> Q;
    file >> nElemL;

    for (int i = 0; i < numeroPresentes; i++) {
        file >> line;
        p.push_back(stoi(line));
    }

    for (int i = 0; i < nElemL; i++) {
        vector<int> eachLine;
        for (int j = 0; j < 2; j++) {
            file >> line;
            eachLine.push_back(stoi(line));
        }
        L.push_back(eachLine);
        
    }
    
    // matrix.resize(numeroPresentes);
    // for (int i = 0; i < numeroPresentes; i++) {
    //     matrix[i].resize(numeroPresentes);
    // }

    // for (int h = 0; h < numeroPresentes; h++) {
    //     for (int e = 0; e < numeroPresentes; e++) {
    //         matrix[h][e] = 0;        
    //     }
    // }

    // for (int w = 0; w < nElemL; w++) {
    //     matrix[L[w][0]-1][L[w][1]-1] = 1;
    //     matrix[L[w][1]-1][L[w][0]-1] = 1;
    // }

    // for (int i = 0; i < numeroPresentes; i++) {
    //     for (int j = 0; j < numeroPresentes; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    file.close();
}

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
                if (matrix[sol[t][item]-1][sol[k][i]-1] == 0) {                    
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

    for (int i = 0; i < solution.size()-1; i++) {
        for (int j = i+1; j < solution.size(); j++) {

            vector<vector<int>> tempSol;
            tempSol = solution; 

            if ( tempSol[i].size() == 0 || tempSol[j].size() == 0 ) {
                continue;
            }
    
            int chooseItem1 = rand() % tempSol[i].size(); // escolhe um item aleatório do trenó 1
            int chooseItem2 = rand() % tempSol[j].size(); // escolhe um item aleatório do trenó 2

            if (matrix[tempSol[i][chooseItem1]-1][tempSol[i][chooseItem2]-1] != 1) {
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
    }

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
    // cout << "Swap & Reinsertion START" << endl;
    vector<vector<int>> tempSol;
    tempSol = solution; // copia

    tempSol = movementSwap(tempSol, matrix, p, Q);
    tempSol = movementReinsetion(tempSol, matrix, p, Q);

    // cout << "Swap & Reinsertion END" << endl;
    return tempSol;
}

void greedyalgorithm(vector<vector<int>> &L, vector<int> &p, int numeroPresentes, int &k, int &Q, int &nElemL, vector<vector<int>> &sol) {
    vector<treno> trenos;
    for (int i = 0; i < k; i++) {
        trenos.push_back(treno(Q)); // i -> id do treno, Q -> capacidade do treno 
    }

    vector<vector<int>> matrix;

    matrix.resize(numeroPresentes);
    for (int i = 0; i < numeroPresentes; i++) {
        matrix[i].resize(numeroPresentes);
    }

    for (int h = 0; h < numeroPresentes; h++) {
        for (int e = 0; e < numeroPresentes; e++) {
            matrix[h][e] = 0;        
        }
    }

    for (int w = 0; w < nElemL; w++) {
        matrix[L[w][0]-1][L[w][1]-1] = 1;
        matrix[L[w][1]-1][L[w][0]-1] = 1;
    }

    vector<int> presentes;
    vector<int> pesosOrd;
    multimap<int, int> presentesPesos; 
    for (int w = 1; w < numeroPresentes+1; w++) {
        presentesPesos.insert(pair<int, int>(p[w-1], w));
    }    
    multimap<int, int>::iterator itr;
    for (itr = presentesPesos.begin(); itr != presentesPesos.end(); itr++) {
        presentes.push_back(itr->second);
        pesosOrd.push_back(itr->first);
    }

    // GULOSO DE FATO
    
    for (int i = numeroPresentes-1; i > 0; i--) { 
        cout << "PRESENTE " << presentes[i] << " PESO: " << pesosOrd[i] << endl << endl; 
        // cout << "-----------------------------" << endl;
        int menor = 0;
        int flag = 0;
        int aux_treno = 0;
        while (flag != 1) {// While para a mudança de trenós
            
            if (trenos[aux_treno].capacidade_atual == Q) { // Se o trenó estiver vazio
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
                    for (int j = 0; j < copy_treno.n_presentes; j++) { // Para todos os itens que já estão no trenó
                        if (matrix[presentes[i]-1][trenos[aux_treno].presentes[j].id-1] == 1) { // Se o item que quer adicionar tem conflito com algum item que já está no trenó]) {
                            aux_treno++;
                            // cout << "Entrou na re/strição " << k << endl;
                            break;
                        }// else {
                    }
                    // cout << "Segundo add presente " << endl;
                    trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]); // Se passou por tudo, pode adicionar no indice
                    // cout << "Indice presente: " << presentes[i] << endl; // Já pode adicionar no indice
                    // // cout << "Peso presente: " << pesosOrd[i] << endl;

                    flag = 1; // Muda a flag pra ir pro proximo item do loop            
                            // // cout << "Adicionou ao trenó não vazio. " << endl;
                        //}
                } else {
                    aux_treno++;
                }
            }

        }         
        
    }    
    
    int fo = 0;
    for (int i = 0; i < k; i++) {
        if (trenos[i].n_presentes > 0) {
            fo++;
        }
    }
    sol.resize(fo);
    

    for (int i = 0; i < k; i++) {
        if (trenos[i].n_presentes > 0) {
            vector<int> presentes_i = trenos[i].getPresentes();
            for (int j = 0; j < presentes_i.size(); j++) {            
                sol[i].push_back(presentes_i[j]);
            }            
        }
    }

    // Print pra ver a capacidade dos trenós
    for (int i = 0; i < k; i++){
        if (trenos[i].n_presentes > 0){
            cout << "Treno " << i << " capacidade atual: " << trenos[i].capacidade_atual << endl;
        }  
    }

}

void greedyalgorithm2(vector<vector<int>> &L, vector<int> &p, int numeroPresentes, int &k, int &Q, int &nElemL, vector<vector<int>> &sol) {
    vector<treno> trenos;
    for (int i = 0; i < k; i++) {
        trenos.push_back(treno(Q)); // i -> id do treno, Q -> capacidade do treno 
    }
    
    vector<vector<int>> matrix;
    matrix.resize(numeroPresentes);
    for (int i = 0; i < numeroPresentes; i++) {
        matrix[i].resize(numeroPresentes);
    }

    for (int h = 0; h < numeroPresentes; h++) {
        for (int e = 0; e < numeroPresentes; e++) {
            matrix[h][e] = 0;        
        }
    }

    for (int w = 0; w < nElemL; w++) {
        matrix[L[w][0]-1][L[w][1]-1] = 1;
        matrix[L[w][1]-1][L[w][0]-1] = 1;
    }

    vector<int> presentes;
    vector<int> pesosOrd;
    multimap<int, int> presentesPesos; 
    for (int w = 1; w < numeroPresentes+1; w++) {
        presentesPesos.insert(pair<int, int>(p[w-1], w));
    }    
    multimap<int, int>::iterator itr;
    for (itr = presentesPesos.begin(); itr != presentesPesos.end(); itr++) {
        presentes.push_back(itr->second);
        pesosOrd.push_back(itr->first);
    }

    // GULOSO DE FATO
    
    for (int i = numeroPresentes-1; i > 0; i--) { 
        // cout << "PRESENTE " << presentes[i] << endl << endl; 
        // cout << "-----------------------------" << endl;
        int menor = 0;
        int flag = 0;
        int aux_treno = 0;
        while (flag != 1) {// While para a mudança de trenós
            
            if (trenos[aux_treno].capacidade_atual == Q) { // Se o trenó estiver vazio
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
                if ((trenos[aux_treno].capacidade_atual - pesosOrd[i]) >= 0){  // Se couber
                    for (int k = 0; k < copy_treno.n_presentes; k++) { // Para todos os itens que já estão no trenó
                        if (matrix[presentes[i]-1][trenos[aux_treno].presentes[k].id-1] == 1) { // Se o item que quer adicionar tem conflito com algum item que já está no trenó]) {
                            aux_treno += 1;
                            cout << "Entrou na restrição " << k << endl;
                            break;
                        }// else {
                    }
                    cout << "Segundo add presente " << endl;
                    trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]); // Se passou por tudo, pode adicionar no indice
                    cout << "Indice presente: " << presentes[i] << endl; // Já pode adicionar no indice
                    // // cout << "Peso presente: " << pesosOrd[i] << endl;

                    flag = 1; // Muda a flag pra ir pro proximo item do loop            
                            // // cout << "Adicionou ao trenó não vazio. " << endl;
                        //}
                } else {
                    aux_treno += 1;
                }
            }
        }
        
    }    
    
    int fo = 0;
    for (int i = 0; i < k; i++) {
        if (trenos[i].n_presentes > 0) {
            fo++;
        }
    }
    sol.resize(fo);
    

    for (int i = 0; i < k; i++) {
        if (trenos[i].n_presentes > 0) {
            vector<int> presentes_i = trenos[i].getPresentes();
            for (int j = 0; j < presentes_i.size(); j++) {            
                sol[i].push_back(presentes_i[j]);
            }            
        }
    }
    // Print pra ver a capacidade dos trenós
    for (int i = 0; i < k; i++){
        if (trenos[i].n_presentes > 0){
            cout << "Treno " << i << " capacidade atual: " << trenos[i].capacidade_atual << endl;
    }   }

}

vector<vector<int>> vnd(vector<vector<int>> solution, vector<vector<int>> matrix, vector<int> p, int numeroPresentes, int Q, int &nElemL) {
    
    int mov = 1;
    int r = 2;
    vector<vector<int>> sol_ = solution;
    while (mov <= r) {
        
        switch (mov) {
            case 1:
                sol_ = movementReinsetion(sol_, matrix, p, Q); // Reisertion 
                // cout << "swap" << endl;
                break;
            case 2:
                sol_ = movementSwapReinsetion(sol_, matrix, p, Q); //Swap & Reinsertion 
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

    return solution;
}
//, vector<vector<int>> &matrix

int main(void) {
    string filename = "./instances/n30_k150_B.txt";
    vector<vector<int>> L;
    // vector<vector<int>> matrix;
    vector<int> p;
    int Q, k, nElemL, numeroPresentes;
    
    readFile(filename, L, p, numeroPresentes, k, Q, nElemL); // Passagem por referência, a função modifica esses caras
    vector<vector<int>> sol;
    // matrix,
    //greedyalgorithm(L, p, numeroPresentes, k, Q, nElemL, sol);
    greedyalgorithm2(L, p, numeroPresentes, k, Q, nElemL, sol);
    cout << "Q: " << Q << endl; 


    cout << endl << "Solucao GREEDY" << endl;
    for (int i = 0; i < sol.size(); i++) {
        int pt = 0;
        for (int j = 0; j < sol[i].size(); j++) {
            pt += p[sol[i][j]-1];
            cout << sol[i][j] << " ";
        }
        cout << "peso: "<< pt<<endl;
    }
    cout << endl << "FO: "<<  fo(sol) << endl << endl;

    // sol = vnd(sol, matrix, p, numeroPresentes, Q, nElemL);
    // cout << endl << "Solucao BUSCA LOCAL" << endl;
    // for (int i = 0; i < sol.size(); i++) {
    //     int pt = 0;
    //     for (int j = 0; j < sol[i].size(); j++) {
    //         pt += p[sol[i][j]-1];
    //         cout << sol[i][j] << " ";
    //     }
    //     cout << "peso: "<< pt<<endl;
    // }
    // cout << endl << "FO: "<<  fo(sol) << endl << endl;

    return 0;
}