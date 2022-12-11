#pragma once

#include <vector>

#include "problem_data.h"

using namespace std;

bool checkingWei(int &item, vector<int> treno, vector<int> p, int Q);
void swap(int &i1, int &i2);
bool reinsertion(vector<vector<int>> &matrix, vector<vector<int>> &sol, int &item, int t, vector<int> p, int Q);
int fo(vector<vector<int>> solution);
vector<vector<int>> movementSwap(vector<vector<int>> solution, vector<vector<int>> matrix, vector<int> p, int Q);
vector<vector<int>> movementReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q);
vector<vector<int>> movementSwapReinsetion(vector<vector<int>> &solution, vector<vector<int>> matrix, vector<int> p, int Q);
void greedyalgorithm(ProblemData &data, vector<vector<int>> &sol);
vector<vector<int>> vnd(vector<vector<int>> &solution, ProblemData &data);