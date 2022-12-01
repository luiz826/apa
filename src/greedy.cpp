#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);

void quick_sort(vector<int> &p, int left, int right);

int main(void) {
    string filename = "../instances/n30_k150_A.txt";
    vector<vector<int>> L;
    vector<int> p;
    int Q, k, nElemL, numeroPresentes;
    readFile(filename, L, p, Q, k, nElemL, numeroPresentes); // Passagem por referência, a função modifica esses caras

    

    return 0;
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

void quick_sort(vector<int> &p, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = p[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (p[i] < pivot)
            i++;
        while (p[j] > pivot)
            j--;
        if (i <= j) {
            tmp = p[i];
            p[i] = p[j];
            p[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quick_sort(p, left, j);
    if (i < right)
        quick_sort(p, i, right);
}
