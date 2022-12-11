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
                sol_ = movementSwap(sol, L, p, Q, k); // Reisertion 
                break;
            case 2:
                sol_ = movementReinsetion(sol, L, p, Q, k); //Swap & Reinsertion 
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
