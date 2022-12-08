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
        int id;
        int capacidade;
        int presentes;
        vector<int> presentes_id;
        treno(int id, int capacidade) {
            this->id = id;
            this->capacidade = capacidade;
            this->presentes = 0;
        }
        void addPresente(int id) {
            this->presentes_id.push_back(id);
            this->presentes++;
        }
        void print() {
            cout << "Treno " << this->id << " com " << this->presentes << " presentes: ";
            for (int i = 0; i < this->presentes; i++) {
                cout << this->presentes_id[i] << " ";
            }
            cout << endl;
        }
};

void greedyalgorithm(vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {
    vector<treno> trenos;
    for (int i = 0; i < k; i++) {
        trenos.push_back(treno(i, Q));
    }
    for (int i = 0; i < numeroPresentes; i++) {
        int menor = 0;
        for (int j = 0; j < k; j++) {
            if (trenos[j].capacidade - trenos[j].presentes > trenos[menor].capacidade - trenos[menor].presentes) {
                menor = j;
            }
        }
        trenos[menor].addPresente(i);
    }

    for (int i = 0; i < k; i++) {
        trenos[i].print();
    }
}

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {
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
            cout << " j: " << j << endl;
            file >> line;
            eachLine.push_back(stoi(line));
        }
        L.push_back(eachLine);
    }
    
    file.close();
}