#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <map>
#include <fstream>
#include <regex>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std;

#include "algorithm.h"
#include "read_file.h"

// class movimento {
    
// };
 //vector<vector<int>> &matrix, 



int execute(string filename, ofstream &output) {

    string filenameCompleto = "./instances/" + filename;
    ProblemData data;
    // vector<vector<int>> L;
    // vector<vector<int>> matrix;
    vector<vector<int>> sol;
    // vector<int> p;
    // int Q, k, nElemL, numeroPresentes;
    
    output << filename + ", ";

    output << "-1, ";
    
    // readFile(filenameCompleto, L, matrix, p, numeroPresentes, k, Q, nElemL); // Passagem por referência, a função modifica esses caras
    readFile(filenameCompleto, data);
    auto startGreedy = high_resolution_clock::now();
    // greedyalgorithm(matrix, p, numeroPresentes, k, Q, nElemL, sol);
    greedyalgorithm(data, sol);

    auto stopGreedy = high_resolution_clock::now();
    auto durationGreedy = duration_cast<microseconds>(stopGreedy - startGreedy);

    

    output << to_string(fo(sol)) + ", ";
    output << to_string(durationGreedy.count()) + ", ";
    output << "-1, ";
    
    auto startVnd = high_resolution_clock::now();
    // sol = vnd(sol, matrix, p, numeroPresentes, Q, nElemL);
    sol = vnd(sol, data);

    auto stopVnd = high_resolution_clock::now();
    auto durationVnd = duration_cast<microseconds>(stopVnd - startVnd);

    output << to_string(fo(sol)) + ", ";
    output << to_string(durationVnd.count()) + ", ";
    output << "-1\n";


    return 0;
}

int main(void) {
    ofstream output("output.txt");

    string path = "./instances";
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.path().filename() == "otimos.txt" || entry.path().filename() == ".DS_Store") {
            continue;
        }

        
        for (int j = 0; j < 10; j++) {
            cout << "Executando " << entry.path().filename() << " " << j << endl;
            execute(entry.path().filename(), output);
        }
    }    

    output.close();
}