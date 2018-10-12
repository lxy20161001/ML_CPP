//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_LINEARSYSTEM_H
#define NEW_ML_CPP_LINEARSYSTEM_H

#include "ConMatrix.h"
#include <tuple>

using namespace std;

template <typename T>
class LinearSystem{
    T _m,_n;
    vector<T> privots;

public:
    MinMatrix<T> Ab;
    LinearSystem() {

    }


    LinearSystem(MinMatrix<T> A, MinVector<T> b):_m(A.row_num()),_n(A.col_num()){
        assert(A.row_num() == b._size());

        for( int i = 0 ; i < this->_m; ++i ){
            A._Matrix()[i].push_back(b[i]);
        }

        Ab = A;

        this->privots = {};
    }

    LinearSystem(vector<vector<T>> A,vector<T> b):_m(A.size()),_n(A[0].size()){
        assert(A.size() == b.size());
        for( int i = 0 ; i < this->_m; ++i ){
            A[i].push_back(b[i]);
        }

        Ab = MinMatrix<T>(A);

        this->privots = {};
    }

    LinearSystem(MinMatrix<T> A,MinMatrix<T> B){
        assert(A.size() == B.size());

        _m = A.row_num();
        _n = A.col_num();

        for (int i = 0; i < _m; ++i) {
            A.addEle(i,B[i]);
        }

        Ab = A;

        this->privots = {};
    }

    LinearSystem(vector<vector<T>> A,vector<vector<T>> B){
        assert(A.size() == B.size());

        _m = A.size();
        _n = A[0].size();

        for (int i = 0; i < _m; ++i) {
            for( int j = 0; j < _n;++j){
                A[i].push_back(B[i][j]);
            }
        }

        Ab = MinMatrix<T>(A);

        this->privots = {};
    }

    LinearSystem(MinMatrix<T> A, vector<T> b):_m(A.row_num()),_n(A.col_num()){
        assert(A.row_num() == b.size());

        for( int i = 0 ; i < this->_m; ++i ){
            A._Matrix()[i].push_back(b[i]);
            Ab.addVector(A.row_vector(i));
        }

        this->privots = {};
    }

    T _mar_row(int index_i, int index_j, int n){
        auto best = this->Ab[index_i][index_j];
        auto ret = index_i;
        for( int i = index_i; i < n; ++i){
            if(this->Ab[i][index_j] > best){
                best = this->Ab[i][index_j];
                ret = i;
            }
        }

        return ret;
    }


private:
    void _forward(){
        int i = 0;
        int k = 0;
        int n = this->_m;

        while( i < this->_m && k < this->_n){
            auto max_row = this->_mar_row(i,k,this->_m);
            swap(this->Ab._Matrix()[i],this->Ab._Matrix()[max_row]);

            if(_is_zero(this->Ab[i][k])){
                k +=1;
            }

            else{
                this->Ab.elimination(i,this->Ab[i] / this->Ab[i][k]);
                for( int j = i + 1 ; j < n ; ++j){
                    this->Ab.elimination(j,this->Ab[j] - ( this->Ab[i] * this->Ab[j][k]));
                }

                this->privots.push_back(k);
                i+=1;
            }
        }
    }

    void _backward() {
        int n = this->privots.size();
        for (int i = n - 1; i > -1; i = i - 1) {
            //主元在AB[I][K]的位置
            T k = this->privots[i];
            for (int j = i - 1; j > -1; j = j -1) {
                this->Ab.elimination(j, this->Ab[j] - (this->Ab[i] * this->Ab[j][k]));
            }
        }
    }

public:
    bool Gj_elem(){
        this->_forward();
        this->_backward();

        auto size = privots.size()-1;

        for(int i = size;i < this->_m; ++i){
            if(this->_is_zero(this->Ab[i][Ab[i]._size()-1])){
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
    bool _is_zero(T x){
        return abs(x) < EPSILON;
    }

    bool is_equal(T a, T b) {
        return abs(a - b) < EPSILON;
    }
};

template <typename T>
bool is_zero(T x) {
    return abs(x) < EPSILON;
}

template <typename T>
MinMatrix<T> inv(MinMatrix<T> A){
    if(A.row_num()!=A.col_num()) {
        cout<<"RowNum must be == ColNum";
        return MinMatrix<T>();
    }

    auto size = A.row_num();

    LinearSystem<T> ls(A,MinMatrix<T>().identiry(size));

    if(!ls.Gj_elem()){
        cout<<"No solution";
        return MinMatrix<T>();
    };


    auto invA = MinMatrix<T>().zero(A.shape());

    for(int i = 0; i < size;++i){
        invA.col_value_Change(i,ls.Ab.col_vector(i+size));
    }

    return invA;

}


template <typename T>
tuple<MinMatrix<T>,MinMatrix<T>> LU_mat(MinMatrix<T> mat){
    assert(mat.shape()[0] == mat.shape()[1]);

    auto n = mat.shape()[0];
    auto L = MinMatrix<T>().identiry(n);
    tuple<MinMatrix<T>,MinMatrix<T>> newT;

    for(int i = 0; i < n ; ++i){
        if(is_zero(mat[i][i])){
            cout<<"Matrix LU is None None"<<endl;
            return make_tuple(MinMatrix<T>(),MinMatrix<T>());
        } else{
            for( int j = i+1; j < n; ++j ){
                auto p = mat[j][i]/mat[i][i];
                mat.row_value_Change(j,mat[j] - mat[i]*p); //A[j] = A[j] - p*A[i]
                L._Matrix()[j][i] = p;
            }
        }
    }
    return make_tuple(L,mat);
}

template <typename T>
MinMatrix<T> LU(MinMatrix<T> mat){
    assert(mat.shape()[0] == mat.shape()[1]);

    auto n = mat.shape()[0];
    auto L = MinMatrix<T>().identiry(n);
    tuple<MinMatrix<T>,MinMatrix<T>> newT;

    for(int i = 0; i < n ; ++i){
        if(is_zero(mat[i][i])){
            cout<<"Matrix LU is None None"<<endl;
            return MinMatrix<T>();
        } else{
            for( int j = i+1; j < n; ++j ){
                auto p = mat[j][i]/mat[i][i];
                mat.row_value_Change(j,mat[j] - mat[i]*p); //A[j] = A[j] - p*A[i]
                L._Matrix()[j][i] = p;
            }
        }
    }
    return L.dot(mat);
}

#endif //NEW_ML_CPP_LINEARSYSTEM_H
