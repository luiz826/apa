#include <iostream>
#include <vector>

using namespace std;   

int f(vector<vector<int>> s) {
    return s.size();
}

vector<vector<int>> vnd(vector<vector<int>> &L, vector<vector<int>> &sol, vector<int> p, int Q) {
    
    int k = 1;
    int r = 2;
    while (k <= r) {
        vector<vector<int>> sol_;
        switch (k) {
            case 1:
                // mov 1
                break;
            case 2:
                // mov 2
                break;
        }

        if (f(sol) < f(sol)) {
            k = 1;
            sol = sol_;
        } else {
            k++;
        }
        
    }

    return sol;
}

