#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// random
#include <stdlib.h>     
#include <time.h>

#include "read_file.h"

using namespace std;

// Precisa tirar os data daqui

// void readFile(string filename, vector<vector<int>> &L, vector<vector<int>> &matrix, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL) {

    
//     ifstream file(filename);
//     string line, space1, space2;
//     int line_number = 0;

//     file >> line;
//     file >> data.numeroPresentes;
//     file >> data.k;
//     file >> data.Q;
//     file >> data.nElemL;

//     for (int i = 0; i < data.numeroPresentes; i++) {
//         file >> line;
//         data.p.push_back(stoi(line));
//     }

//     for (int i = 0; i < data.nElemL; i++) {
//         vector<int> eachLine;
//         for (int j = 0; j < 2; j++) {
//             file >> line;
//             eachLine.push_back(stoi(line));
//         }
//         data.L.push_back(eachLine);
        
//     }
//     int contm = 0;
//     data.matrix.resize(data.numeroPresentes);
//     for (int i = 0; i < data.numeroPresentes; i++) {
//         data.matrix[i].resize(data.numeroPresentes-contm);
//         contm--;
//     }
//     // matrix.resize(numeroPresentes);
//     // for (int i = 0; i < numeroPresentes; i++) {
//     //     matrix[i].resize(numeroPresentes);
//     // }

//     for (int h = 0; h < data.numeroPresentes; h++) {
//         for (int e = h+1; e < data.numeroPresentes; e++) {
//             data.matrix[h][e] = 0;        
//         }
//     }

    
//     for (int w = 0; w < data.nElemL; w++) {
//         data.matrix[data.L[w][0]-1][data.L[w][1]-1] = 1;
        
//     }

//     file.close();
// }

void readFile(string filename, ProblemData &data) {

    
    ifstream file(filename);
    string line, space1, space2;
    int line_number = 0;

    file >> line;
    file >> data.numeroPresentes;
    file >> data.k;
    file >> data.Q;
    file >> data.nElemL;

    for (int i = 0; i < data.numeroPresentes; i++) {
        file >> line;
        data.p.push_back(stoi(line));
    }

    for (int i = 0; i < data.nElemL; i++) {
        vector<int> eachLine;
        for (int j = 0; j < 2; j++) {
            file >> line;
            eachLine.push_back(stoi(line));
        }
        data.L.push_back(eachLine);
        
    }
    int contm = 0;
    data.matrix.resize(data.numeroPresentes);
    for (int i = 0; i < data.numeroPresentes; i++) {
        data.matrix[i].resize(data.numeroPresentes-contm);
        contm--;
    }

    for (int h = 0; h < data.numeroPresentes; h++) {
        for (int e = h+1; e < data.numeroPresentes; e++) {
            data.matrix[h][e] = 0;        
        }
    }

    
    for (int w = 0; w < data.nElemL; w++) {
        data.matrix[data.L[w][0]-1][data.L[w][1]-1] = 1;
        
    }

    file.close();
}

