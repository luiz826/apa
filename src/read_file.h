#ifndef READ_FILE_H_INCLUDED
#define READ_FILE_H_INCLUDED

#include <iostream>
#include <vector>

#include "problem_data.h"

using namespace std;



// void readFile(string filename, vector<vector<int>> &L, vector<vector<int>> &matrix, vector<int> &p, int &numeroPresentes, int &k, int &Q, int &nElemL);

void readFile(string filename, ProblemData &data);


#endif