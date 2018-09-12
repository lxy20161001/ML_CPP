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
    T EPSILON = 1e-010;
    MinMatrix<T> Ab;
    int _m;
    int _n;
    vector<int> pivots;

public:
    LinearSystem(MinMatrix<T> A, MinVector<T> b) {
        assert(A.size() == b.len());

        _m = A.row_num();
        _n = A.col_num();


        for (int i = 0; i < _m; ++i) {
            Ab.addMinVector(A.row_vector(i).AddElem(b.getitem(i)));
        }

        pivots = {};

    }

    LinearSystem(MinMatrix<T> A,MinMatrix<T> B){
        assert(A.size() == B.size());

        _m = A.row_num();
        _n = A.col_num();

        for (int i = 0; i < _m; ++i) {
            Ab.addMinVector(A.row_vector(i).AddElem(B[i]));
        }

        pivots = {};
    }

    LinearSystem(MinMatrix<T> *A, MinVector<T> *b) {
        assert(A->size() == b->len());

        _m = A->row_num();
        _n = A->col_num();


        for (int i = 0; i < _m; ++i) {
            Ab.addMinVector(A->row_vector(i).AddElem(b->getitem(i)));
        }

        pivots = {};

    }


    LinearSystem(MinMatrix<T> *A,MinMatrix<T> *B){
        assert(A->size() == B->size());

        _m = A->row_num();
        _n = A->col_num();

        for (int i = 0; i < _m; ++i) {
            Ab.addMinVector(A->row_vector(i).AddElem(B[i]));
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
            this->Ab.swap_v(i,max_row);


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
        for (int i = n - 1; i > -1; i = i - 1) {
            //主元在AB[I][K]的位置
            T k = this->pivots[i];
            for (int j = i - 1; j > -1; j = j -1) {
                this->Ab.elimination(j, this->Ab[j].sub(this->Ab[i] * this->Ab[j][k]));
            }
        }
        //return this->Ab;
    }

    bool Gj_elem() {
        this->_forward();
        this->_backward();

        auto size = pivots.size()-1;

        for(int i = size;i < this->_m; ++i){
            if(this->is_zero(this->Ab[i][Ab[i].len()-1])){
                return false;
            }
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


template <typename T>
MinMatrix<T> inv(MinMatrix<T> A){
    if(A.row_num()!=A.col_num()) {
        cout<<"RowNum must be == ColNum";
        return MinMatrix<T>();
    }

    auto size = A.row_num();

    LinearSystem<T> ls(A,MinMatrix<T>().indentity(size));

    if(!ls.Gj_elem()){
        cout<<"No solution";
        return MinMatrix<T>();
    };


    MinMatrix<T> invA(A.shape());

    for(int i = 0; i < size;++i){
        //invA.valueChange(i,ls.Ab[i],size);
        invA.col_value_Change(i,ls.Ab.col_vector(i+size));
    }

    return invA;
    
}
#endif //ML_CPP_LINEARSYSTEM_H
