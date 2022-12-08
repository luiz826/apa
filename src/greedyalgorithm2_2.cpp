#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

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
    
    file.close();
}

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
            cout << "Treno " << t << " com " << this->n_presentes << " presentes: ";
            for (int i = 0; i < this->n_presentes; i++) {
                cout << this->presentes[i].id << " ";
            }
            cout << endl;
        }
};

void greedyalgorithm(vector<vector<int>> &L, vector<int> &p, int numeroPresentes, int &k, int &Q, int &nElemL) {
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

    // for (int w = 0; w < numeroPresentes; w++) {
    //     for (int e = 0; e < numeroPresentes; e++) {
    //         cout << matrix[w][e] << " ";
    //     }
    //     cout << endl;
    // }

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
    // int contadoooor = 0;
    for (int i = numeroPresentes-1; i > 0; i--) { 
        cout << "PRESENTE " << presentes[i] << endl << endl; 
        cout << "-----------------------------" << endl;
        int menor = 0;
        int flag = 0;
        int aux_treno = 0;
        while (flag != 1) {// While para a mudança de trenós
            
            if (trenos[aux_treno].capacidade_atual == Q) { // Se o trenó estiver vazio
                // // cout << "Trenó vazio: " << aux_treno << endl;
                cout << "Primeiro addPresente " << endl;
                trenos[aux_treno].addPresente(presentes[i], pesosOrd[i]);
                cout << "Indice presente: " << presentes[i] << endl; // Já pode adicionar no indice
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
        // contadoooor++;

        // if (contadoooor == 5){break;}
            
    }

    for (int i = 0; i < k; i++) {
        trenos[i].printTreno(i);
    }
}



int main(void) {
    string filename = "../instances/n30_k150_A.txt";
    vector<vector<int>> L;
    vector<int> p;
    int Q, k, nElemL, numeroPresentes;
    readFile(filename, L, p, numeroPresentes, k, Q, nElemL); // Passagem por referência, a função modifica esses caras
    // cout << numeroPresentes << endl;
    greedyalgorithm(L, p, numeroPresentes, k, Q, nElemL);

    return 0;
}