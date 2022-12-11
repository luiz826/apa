#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>

using namespace std;

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);
void readFile2(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL); 
void greedyalgorithm(vector<vector<int>>, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);

int main(void) {
    string filename = "/home/luiz/Documents/UFPB/apa/apa/instances/n30_k150_A.txt";
    vector<vector<int>> L;
    vector<int> p;
    int Q, k, numeroPresentes, nElemL;
    readFile2(filename, L, p, numeroPresentes, k, Q, nElemL); // Passagem por referência, a função modifica esses caras

    greedyalgorithm(L, p, numeroPresentes, k, Q, nElemL);
    cout << "A";

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
        cout << "OPENED" << endl;
        file >> numeroPresentes >> k >> Q >> nElemL;

        cout << numeroPresentes << endl;
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

void readFile2(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL, int **aux) {
    // read file
    ifstream file(filename);
    string line, space1, space2;
    int line_number = 0;

    file >> line;
    file >> numeroPresentes;
    file >> k;
    file >> Q;
    file >> nElemL;
    // file >> space1;

    // read p
    for (int i = 0; i < numeroPresentes; i++) {
        file >> line;
        p.push_back(stoi(line));
    }

    // file >> space2;
    // read L
    for (int i = 0; i < nElemL; i++) {
        vector<int> eachLine;
        for (int j = 0; j < 2; j++) {
            // cout << " j: " << j << endl;
            file >> line;
            eachLine.push_back(stoi(line));
        }
        L.push_back(eachLine);
    }

    file.close();
}


void greedyalgorithm(vector<vector<int>> L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {

    int matrix[nElemL][nElemL]; 
    
    for (int i = 0; i < nElemL; i++) {
        for (int j = 0; j < nElemL; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < nElemL; i++) {
        matrix[L[i][0]-1][L[i][1]-1] = 1;
        matrix[L[i][1]-1][L[i][0]-1] = 1;
    }


    vector<treno> trenos;
    vector<int> presentes;
    int peso = 0;
    int numeroPresentesTreno = 0;
    for (int i = 0; i < nElemL; i++) {
        for (int j = 0; j < numeroPresentes; j++) {
            if (matrix[i][j] != 1) {
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