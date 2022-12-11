#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "read_file.h"

using namespace std;

void readFile(string filename, vector<vector<int>> &L, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);

void quick_sort(vector<int> &p, int left, int right);

int main(void) {
    string filename = "../instances/n30_k150_A.txt";
    vector<vector<int>> L;

    vector<int> p;
    vector<int> aux;
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




void merge(vector<int> &p, vector<int> &aux, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = p[left + i];
    for (j = 0; j < n2; j++)
        R[j] = p[middle + 1 + j];

    /* Merge the temp arrays back into p[left..right]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            aux[k] = i;
            p[k] = L[i];
            i++;
        } else {
            aux[k] = i;
            p[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        p[k] = L[i];
        aux[k] = i;
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        p[k] = R[j];
        aux[k] = j;
        j++;
        k++;
    }
}


void mergeSort(vector<int> &p, vector<int> &aux, int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        mergeSort(p, aux, left, middle);
        mergeSort(p, aux, middle + 1, right);
        merge(p, aux, left, middle, right);
    }
}

