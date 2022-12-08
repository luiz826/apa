#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);
void greedyalgorithm(vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);

int main(void) {
    string filename = "../instances/n30_k150_A.txt";
    vector<vector<int>> L;
    vector<int> p;
    int Q, k, nElemL, numeroPresentes;
    readFile(filename, L, p, numeroPresentes, k, Q, nElemL); // Passagem por referência, a função modifica esses caras
    greedyalgorithm(L, p, numeroPresentes, k, Q, nElemL);

    return 0;
}

class treno {
    public:
        int numeroPresentes;
        int peso;
        vector<int> presentes;
        treno(int numeroPresentes, int peso, vector<int> presentes) {
            this->numeroPresentes = numeroPresentes;
            this->peso = peso;
            this->presentes = presentes;
        }
};  

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        file >> numeroPresentes >> k >> Q >> nElemL;
        for (int i = 0; i < nElemL; i++) {
            vector<int> aux;
            for (int j = 0; j < numeroPresentes; j++) {
                int aux2;
                file >> aux2;
                aux.push_back(aux2);
            }
            L.push_back(aux);
        }
        for (int i = 0; i < numeroPresentes; i++) {
            int aux;
            file >> aux;
            p.push_back(aux);
        }
    }
    file.close();
}

void greedyalgorithm(vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {
    vector<treno> trenos;
    vector<int> presentes;
    int peso = 0;
    int numeroPresentesTreno = 0;
    for (int i = 0; i < nElemL; i++) {
        for (int j = 0; j < numeroPresentes; j++) {
            if (L[i][j] == 1) {
                if (peso + p[j] <= Q) {
                    peso += p[j];
                    numeroPresentesTreno++;
                    presentes.push_back(j);
                }
            }
        }
        trenos.push_back(treno(numeroPresentesTreno, peso, presentes));
        peso = 0;
        numeroPresentesTreno = 0;
        presentes.clear();
    }
    for (int i = 0; i < trenos.size(); i++) {
        cout << trenos[i].numeroPresentes << " " << trenos[i].peso << " ";
        for (int j = 0; j < trenos[i].presentes.size(); j++) {
            cout << trenos[i].presentes[j] << " ";
        }
        cout << endl;
    }
}