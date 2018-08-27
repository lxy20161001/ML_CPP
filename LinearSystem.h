//
// Created by john on 2018-8-22.
//

#ifndef ML_CPP_LINEARSYSTEM_H
#define ML_CPP_LINEARSYSTEM_H

#include "MinMatrix.h"
#include "MinVector.h"
#include "MinStatistics.h"
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
class LinearSystem {
public:
    T EPSILON = 1e-8;
    MinMatrix<T> Ab;
    int _m;
    int _n;
    vector<int> pivots;

public:
    LinearSystem(MinMatrix<T> A, MinVector<T> b) {
        assert(A.size() == b.len());

        _m = A.row_num();
        _n = A.col_num();


        for (int i = 0; i < A.row_num(); ++i) {
            Ab.addMinVector(A.row_vector(i).AddElem(b.getitem(i)));
        }

        pivots = {};

    }

    LinearSystem(MinMatrix<T> *A, MinVector<T> *b) {
        assert(A->size() == b->len());

        _m = A->row_num();
        _n = A->col_num();


        for (int i = 0; i < A->row_num(); ++i) {
            Ab.addMinVector(A->row_vector(i).AddElem(b->getitem(i)));
        }

        pivots = {};

    }

    T _max_row(int index_i, int index_j, int n) {
        T best = this->Ab[index_i][index_j];
        T ret = index_i;
        for (int i = index_i + 1; i < n; ++i) {
            if (this->Ab[i][index_j] > best) {
                best = this->Ab[i][index_j];
                ret = i;
            }

        }
        return ret;
    }

    void _forward() {
        int i = 0;
        int k = 0;
        int n = this->_m;

        while (i < this->_m && k < this->_n) {
            auto max_row = this->_max_row(i, k, this->_m);
            this->Ab.swap(i,max_row,this->Ab[max_row],this->Ab[i]);


            if (is_zero(this->Ab[i][k])) {
                k = k + 1;
            } else {
                this->Ab.elimination(i, this->Ab[i] / this->Ab[i][k]);
                for (int j = i + 1; j < n; ++j) {
                    this->Ab.elimination(j, this->Ab[j].sub(this->Ab[i] * this->Ab[j][k]));
                }
                this->pivots.push_back(k);
                i = i + 1;
            }

        }

        //return this->Ab;

    }

    void _backward() {
        int n = this->pivots.size();
        for (int i = n - 1; i > -1; --i) {
            //主元在AB[I][K]的位置
            T k = this->pivots[i];
            for (int j = i - 1; j > -1; --j) {
                this->Ab.elimination(j, this->Ab[j].sub(this->Ab[i] * this->Ab[j][k]));
            }
        }
        //return this->Ab;
    }

    bool Gj_elem() {
        this->_forward();
        this->_backward();

        for(int i = this->pivots.size()-1;i < this->_m; ++i){
            if(!this->is_zero(this->Ab[i][Ab[i].len()-1]))
                return false;
        }
        return true;
    }

    void fancy_print() {
        for (int i = 0; i < this->_m; ++i) {
            for (int j = 0; j < this->_n; ++j) {
                cout << this->Ab[i][j] << "    ";
            }
            cout << "|" << this->Ab[i][this->_n] << endl;
        }
    }

private:
    bool is_zero(T x) {
        return abs(x) < EPSILON;
    }

    bool is_equal(T a, T b) {
        return abs(a - b) < EPSILON;
    }
};

#endif //ML_CPP_LINEARSYSTEM_H
