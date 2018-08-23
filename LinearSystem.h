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

template <typename T>
class LinearSystem{
public:
    MinMatrix<T> Ab;
    int _m;
    int _n;
    LinearSystem(MinMatrix<T> A,MinVector<T> b){
        assert(A.size() == b.len());

         _m = A.row_num();
         _n = A.col_num();

        //assert(_m == _n);

        for(int i = 0 ; i < A.row_num();++i){
            Ab.addMinVector(A.row_vector(i).AddElem(b.getitem(i)));
        }

    }

    LinearSystem(MinMatrix<T> *A,MinVector<T> *b){
        assert(A->size() == b->len());

        _m = A->row_num();
        _n = A->col_num();

        assert(_m == _n);

        for(int i = 0 ; i < A->row_num();++i){
            Ab.addMinVector(A->row_vector(i).AddElem(b->getitem(i)));
        }

    }

    MinMatrix<T> _forward(){
        int n = this->_m;
        this->Ab = this->Ab.sorted();
        for( int i = 0 ; i < n; ++i){
            this->Ab = this->Ab.sorted();
            this->Ab.elimination(i,this->Ab[i]/this->Ab[i][i]);

            for( int j = i+1;j<n;++j){
                this->Ab.elimination(j,this->Ab[j].sub(this->Ab[i]*this->Ab[j][i]));
            }
        }

        return this->Ab;

    }

    MinMatrix<T> _backward(){
        int n = this->_m;
        for(int i = n-1;i>-1;--i){
            for(int j = i - 1;j>-1;--j){
                this->Ab.elimination(j,this->Ab[j].sub(this->Ab[i]*this->Ab[j][i]));
            }
        }
        return this->Ab;
    }

    void Gj_elem(){
        this->_forward();
        this->_backward();
    }

    void fancy_print(){
        for(int i = 0;i < this->_m;++i){
            for(int j = 0;j < this->_n;++j){
                cout<<this->Ab[i][j]<<"    ";
            }
            cout<<"|"<<this->Ab[i][this->_n]<<endl;
        }
    }

};

#endif //ML_CPP_LINEARSYSTEM_H
