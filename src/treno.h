#pragma once
#include <iostream>
#include <vector>

#include "presente.h"

using namespace std;

class treno {
    public:
        int capacidade;
        int capacidade_atual;
        int n_presentes = 0;
        vector<presente> presentes;

        treno(int capacidade) {
            this->capacidade = capacidade;
            this->capacidade_atual = capacidade;
        }
        void addPresente(int id, int peso) {
            presente p(id, peso);
            presentes.push_back(p);
            this->n_presentes++;
            this->capacidade_atual -= peso;
        }
         
        void printTreno(int t) {
            cout << "Treno " << t << " com " << this->n_presentes << " presentes: ";
            for (int i = 0; i < this->n_presentes; i++) {
                cout << this->presentes[i].id << " ";
            }
            cout << endl;
        }

        vector<int> getPresentes() {
            vector<int> presentes;
            for (int i = 0; i < this->n_presentes; i++) {
                presentes.push_back(this->presentes[i].id);
            }
            return presentes;
        }


};