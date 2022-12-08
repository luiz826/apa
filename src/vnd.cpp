#include <iostream>
#include <vector>

using namespace std;   

int fo(vector<vector<int>> solution) {
    int value = 0;
    for (auto &v : solution) {
        if (v.size() != 0) {
            value++;
        };
    }

    return value;
}

vector<vector<int>> vnd(vector<vector<int>> &L, vector<vector<int>> &sol, vector<int> p, int Q) {
    
    int k = 1;
    int r = 2;
    while (k <= r) {
        vector<vector<int>> sol_;
        switch (k) {
            case 1:
                sol_ = movementSwap(solution, L, p, Q, k);
                break;
            case 2:
                sol_ = movementReinsetion(solution, L, p, Q, k);
                break;
        }

        if (fo(sol_) < fo(sol)) {
            k = 1;
            sol = sol_;
        } else {
            k++;
        }
        
    }

    return sol;
}

