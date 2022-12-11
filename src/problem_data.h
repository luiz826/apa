#pragma once

#include <vector>

using namespace std;

struct ProblemData {
    vector<vector<int>> L;
    vector<vector<int>> matrix;
    vector<int> p;
    int numeroPresentes;
    int k, Q, nElemL;
};