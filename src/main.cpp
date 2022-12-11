#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <map>
#include <fstream>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std;

#include "algorithm.h"
#include "read_file.h"


vector<vector<int>> iteratedLocalSearch(string path, string filename, ofstream &output, ProblemData &data, vector<vector<int>> sol) {
    /* Greedy */
    auto startGreedy = high_resolution_clock::now();
    greedyalgorithm(data, sol);
    auto stopGreedy = high_resolution_clock::now();
    auto durationGreedy = duration_cast<microseconds>(stopGreedy - startGreedy);

    output << to_string(fo(sol)) + ", ";
    output << to_string(durationGreedy.count()) + ", ";
    output << "-1, ";
    

    /* VND -> Variable Neighbour Descent*/
    auto startVnd = high_resolution_clock::now();
    vnd(sol, data);
    auto stopVnd = high_resolution_clock::now();
    auto durationVnd = duration_cast<microseconds>(stopVnd - startVnd);

    output << to_string(fo(sol)) + ", ";
    output << to_string(durationVnd.count()) + ", ";
    output << "-1, ";

    int exec = 0;
    while (exec < 3) { // Critério 3 execuções do ILS
        vector<vector<int>> sol_ = naivePertubation(sol, data);
        vnd(sol_, data);
        
        if (fo(sol_) < fo(sol)) {
            sol = sol_;
        }
        
        exec++;
    }
    
    
    return sol;
}

int main(void) {
    ofstream output("../outputs/outputFinal.csv");

    output << "instancia, otimo, solucao_gulosa, tempo_guloso, gap_guloso, solucao_vnd, tempo_vnd, gap_vnd, solucao_ils, tempo_ils, gap_ils\n";

    string path = "../instances";
    for (const auto & entry : fs::directory_iterator(path)) {
        if (entry.path().filename() == "otimos.txt" || entry.path().filename() == ".DS_Store") { // .DS_Store é um arquivo oculto da pasta
            continue;
        }

        ProblemData data;
        
        readFile(entry.path(), data);
        
        for (int j = 0; j < 10; j++) {
            vector<vector<int>> sol;

            output << entry.path().filename();
            output << ", -1, ";

            cout << "Executando " << entry.path().filename() << " " << j << endl;
            
            auto startILS = high_resolution_clock::now();
            sol = iteratedLocalSearch(path, entry.path().filename(), output, data, sol);
            auto stopILS = high_resolution_clock::now();
            auto durationILS = duration_cast<microseconds>(stopILS - startILS);

            output << to_string(fo(sol)) + ", ";
            output << to_string(durationILS.count()) + ", ";
            output << "-1\n";
            
        }
        
    }    

    output.close();
}