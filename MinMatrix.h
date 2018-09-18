//
// Created by john on 2018-8-1.
//

#ifndef LINEARALGEBRA2_MINMATRIX_H
#define LINEARALGEBRA2_MINMATRIX_H

#include "MinVector.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>

using namespace std;

template<typename A>
class MinMatrix {
private:
private:
    vector<vector<A>> vec;
public:
    MinMatrix(vector<vector<A>> vec) : vec(vec) {

    }

    MinMatrix(MinVector<A> shape){

        auto row_size = shape[0];
        auto col_size = shape[1];
        vector<A> cec(col_size);
        for(int i = 0; i < row_size; ++i){
            this->vec.push_back(cec);
        }

        for(int i = 0; i < row_size;++i){
            for(int j = 0; j < col_size;++j){
                this->vec[i][j] = 0;
            }
        }
    }


    MinMatrix() {
        vec = {};
    }

    MinMatrix(int num,MinVector<A> vec){
        for(int i = 0; i < num;++i){
            this->vec.push_back(vec.ThisVec());
        }
    }

    A getitem(vector<int> pos) {
        int r = pos[0];
        int c = pos[1];
        return vec[r][c];
    }

    A getitem(MinVector<A> pos) {
        int r = pos.getitem(0);
        int c = pos.getitem(1);
        return vec[r][c];
    }

    MinMatrix<A> zero(unsigned r, unsigned c) {
        vector<vector<A>> newVec(r);
        for (int i = 0; i < r; i++) {
            newVec[i] = vector<double>(c);
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                newVec[i][j] = 0.0;
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> ones(unsigned r, unsigned c) {
        vector<vector<A>> newVec(r);
        for (int i = 0; i < r; i++) {
            newVec[i] = vector<double>(c);
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                newVec[i][j] = 1.0;
            }
        }
        return MinMatrix<A>(newVec);
    }

    A Dim(){
        return 2;
    }

    MinVector<A> row_vector(A index) {
        return MinVector<A>(vec[index]);
    }

    MinVector<A> col_vector(int index) {
        vector<A> newVec;
        auto size = vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(vec[i][index]);
        }
        return MinVector<A>(newVec);
    }

    int size() {
        return vec.size();
    }


    int row_num() {
        return this->shape()[0];
    }

    int col_num() {
        return this->vec[0].size();
    }

    MinVector<A> shape() {
        A r = vec.size();
        A c = row_vector(0).len();
        return MinVector<A>({r, c});
    }


    MinMatrix<A> add(MinMatrix<A> matrix) {
        assert(this->size() == matrix.size());
        vector<vector<A>> newVec(matrix.size());
        auto size = matrix.size();
        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(matrix.row_vector(0).len());
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < matrix.row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) + matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator+(MinMatrix<A> &matrix) {
        assert(this->size() == matrix.size());
        auto size = matrix.size();
        auto size2 = matrix.row_vector(0).len();
        vector<vector<A>> newVec(size);

        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i][j] = this->getitem({i, j}) + matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);
    }


    MinMatrix<A> sub(MinMatrix<A> matrix) {
        assert(this->size() == matrix.size());
        auto size = matrix.size();
        auto size2 = matrix.row_vector(0).len();
        vector<vector<A>> newVec(size);
        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i][j] = this->getitem({i, j}) - matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> sub_b(MinMatrix<A> matrix){
        assert(this->shape()[1] == matrix.shape()[1]);
       auto size = this->shape()[0];
       auto size2 = matrix.shape()[0];
       for(int i = 0; i < size; ++i){
           this->vec[i][0] = this->vec[i][0]-matrix[i][0];
       }
        return *this;
    }

    MinMatrix<A> operator-(MinMatrix<A> &matrix) {
        assert(this->size() == matrix.size());
        auto size = matrix.size();
        auto size2 = matrix.row_vector(0).len();
        vector<vector<A>> newVec(size);
        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i][j] = this->getitem({i, j}) - matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> mul(A k) {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        auto size = this->size();
        auto size2 = this->row_vector(0).len();

        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i][j] = this->getitem({i, j}) * k;
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator*(A k) {
        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        auto size = this->size();
        auto size2 = this->row_vector(0).len();

        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i][j] = this->getitem({i, j}) * k;
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> rmul(A k) {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        auto size = this->size();
        auto size2 = this->row_vector(0).len();

        for (int i = 0; i < size; i++) {
            newVec[i] = vector<double>(size2);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                newVec[i][j] = k * this->getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    friend MinMatrix<A> operator*(A k, MinMatrix<A> &r) {
        vector<vector<A>> newVec(static_cast<unsigned int>(r.size()));
        for (int i = 0; i < r.size(); i++) {
            newVec[i] = vector<double>(r.row_vector(0).len());
        }
        for (int i = 0; i < r.size(); i++) {
            for (int j = 0; j < r.row_vector(0).len(); j++) {
                newVec[i][j] = r.getitem({i, j}) * k;
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> trueDiv(A k) {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = 1 / k * this->getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator/(A k) {
        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = 1 / k * this->getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> pos() {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = 1 * this->getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> neg() {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = -1 * this->getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    friend ostream &operator<<(ostream &out, MinMatrix<A> matrix) {

        out << "Matrix : ("<<endl;
        for (int i = 0; i < matrix.size(); i++) {
            if (i != matrix.size() - 1) {
                out << matrix.row_vector(i) << ','<<endl;
            } else {
                out << matrix.row_vector(i)<<endl;
            }
        }

        out << ")";
        return out;
    }


    MinVector<A> operator[](int k) {
        assert(k < vec.size() && k >= 0);

        return this->row_vector(k);
    }

    MinMatrix<A> dot(MinMatrix<A> a) {
        assert(col_num() == a.row_num());
        vector<vector<A>> newVec;
        //新矩阵的行数等于=A矩阵的行数
        auto size = row_num();
        auto size2 = a.col_num();
        for (int i = 0; i < size ; i++) {
            newVec.push_back(vector<double>());
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                newVec[i].push_back(row_vector(i).dot(a.col_vector(j)));
            }
        }
        return MinMatrix(newVec);
    }

    MinMatrix<A> dot_b(MinMatrix<A> a) {
        assert(shape()[0] == a.shape()[0]);

        //新矩阵的行数等于=A矩阵的行数
        auto size = shape()[0];
        auto size2 = a.shape()[1];
        auto ret = 0.0;


        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size2; j++) {
                ret+= this->vec[i][j] * a[j][0];
                this->vec[i] = {ret};
            }
        }


        return *this;
    }

    MinMatrix<A> dot_c(MinMatrix<A> a){
        assert(shape()[0] == a.shape()[0]);
        auto size = shape()[0];
        auto size2 = a.shape()[1];
        auto ret = 0.0;


       //for(int i = 0; i < size;++i){
       //    for(int j = 0 ; j < size2;++j){
       //        ret += this->vec[i][0] * a[j][i];
       //        this->vec[i] = {ret};
       //        cout<<i<<"gg:gg"<<j<<endl;
       //    }
       //}
        return *this;
    }


    //矩阵转至
    MinMatrix<A> T() {

        MinMatrix<A> mat(this->vec);
        MinMatrix<A> matT;
        auto size = mat.col_num();
        for(int i = 0; i < size;++i){
            matT.addMinVector(mat.col_vector(i));
        }

        return matT;
    }

    //单位矩阵I
    MinMatrix<A> indentity(int n) {
        vector<vector<A>> inVec;
        for (int i = 0; i < n; ++i) {
            inVec.push_back(vector<A>());
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inVec[i].push_back(0);
                if (i == j) inVec[i][i] = 1;
            }
        }

        return MinMatrix(inVec);
    }

    MinMatrix<A> addMinVector(MinVector<A> minVector) {
        vector<A> vec;
        auto size = minVector.len();
        for (int i = 0; i < size; ++i) {
            vec.push_back(minVector[i]);
        }
        this->vec.push_back(vec);
        return MinMatrix<A>(this->vec);
    }

    //根据vector的参数，对把v的数据扩展成所有行都一样的矩阵
    MinMatrix<A> tile(MinVector<A> v, vector<A> vec) {
        auto r = vec[0];
        auto c = vec[1];

        vector<A> vector1;

        for (int i = 0; i < c; ++i) {
            for (int j = 0; j < v.len(); ++j) {
                vector1.push_back(v.getitem(j));
            }
        }
        MinMatrix<A> tempA;
        for (int i = 0; i < r; ++i) {
            tempA.addMinVector(vector1);
        }

        return tempA;

    }

public:
   //MinMatrix<A> indexFancy(MinVector<A> *temp, vector<vector<A>> vec) {
   //    MinMatrix<A> indexMinMatrix;
   //    int size = vec.size();
   //    for (int i = 0; i < size; ++i) {
   //        indexMinMatrix.addMinVector(temp->indexFancy(vec[i]));
   //    }
   //    return indexMinMatrix;
   //}

   //MinMatrix<A> indexFancy(MinVector<A> *temp, MinMatrix<A> vec) {
   //    MinMatrix<A> indexMinMatrix;
   //    int size = vec.size();
   //    for (int i = 0; i < size; ++i) {
   //        indexMinMatrix.addMinVector(temp->indexFancy(vec[i]));
   //    }
   //    return indexMinMatrix;
   //}

    //根据参数向量temp，把矩阵中的对应向量输出成一个新的矩阵
    MinMatrix<A> indexFancy(MinVector<A> temp, MinMatrix<A> vec) {
        MinMatrix<A> indexMinMatrix;
        int size = temp.len();
        for (int i = 0; i < size; ++i) {
            indexMinMatrix.addMinVector(vec[temp[i]]);
        }
        return indexMinMatrix;
    }

    MinVector<A> indexFancy_vec(MinVector<A> temp, MinMatrix<A> vec) {
        MinVector<A> vecd;
        int size = temp.len();
        for (int i = 0; i < size; ++i) {
            vecd._push_back(vec[temp[i]].getitem(0));
        }
        return vecd;
    }

    MinMatrix<A> operator()(MinVector<A> test,A num){
        auto size = test.len();
        MinMatrix<A> newMat;
        for(int i = 0;i < size; ++i){
            if(test[i]<num){
                newMat.addMinVector(this->vec[i]);
            }
        }

        return newMat;
    }



    MinVector<A> operator()(MinVector<A> a, MinVector<A> b) {
        return indexFancy(a, b);
    }
//根据a，去遍历MinVector b中的参数，组成新的vector向量参数去获取原有矩阵的元素并输出新的MinVector
    MinVector<A> indexFancy(A a, MinVector<A> b) {
        vector<A> temp;
        for (int i = 0; i < b.len(); ++i) {
            temp.push_back(getitem(MinVector<A>({a, b.getitem(i)})));
        }
        return MinVector<A>(temp);
    }
//
    MinVector<A> operator()(A a, MinVector<A> b) {
        return indexFancy(a, b);
    }

    MinVector<A> indexFancy(vector<A> a, vector<A> b) {
        vector<A> temp;
        for (int i = 0; i < a.size(); ++i) {
            temp.push_back(getitem(MinVector<A>({a[i], b[i]})));
        }
        return MinVector<A>(temp);
    }

    MinVector<A> operator()(vector<A> a, vector<A> b) {
        return indexFancy(a, b);
    }

    /////////////////////////////////////////////////


    MinVector<A> concatone(MinMatrix<A> vec) {
        int size = vec.size();
        vector<A> tempVec(vec.row_num());
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < vec[i].len(); ++j) {
                tempVec.push_back(vec[i][j]);
            }
        }
        return MinVector<A>(tempVec);
    }

public:
    MinMatrix<A> sorted() {
        if(this->vec.size()<500){
            return insertionSort();
        } else{
            return shellSort();
        }
    }



private:
    //考虑到暂时使用的矩阵比较小，于是使用插入算法
    MinMatrix<A> insertionSort() {
        for (int i = 0; i < this->vec.size(); ++i) {
            vector<A> e = this->vec[i];
            int j;
            for (j = i; j > 0 && e > this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
            }
            this->vec[j] = e;
        }
        return MinMatrix(this->vec);
    }

    MinMatrix<A> shellSort(){
        int h = 1,i,j;
        int size = this->vec.size();
        vector<A> temp;
        while(h<size/3){
            h = 3*h+1;
        }

        for(;h>0;h/=3){
            for(i=h;i<this->vec.size();i++){
                temp = this->vec[i];
                for(j = i-h;j>=0 && this->vec[j]>temp;j=j-h){
                    this->vec[j+h] = this->vec[j];
                }
                this->vec[j+h] = temp;
            }
        }
        return MinMatrix(this->vec);
    }

public:
    //高斯消元部件
    void elimination(int num, MinVector<A> T) {
        //for (int i = 0; i < T.len(); ++i) {
            this->vec[num] = T.ThisVec();
        //}
    }

    void  swap(int i,int j , MinVector<A> J,MinVector<A> I){
        //assert(i=j);
        auto size = J.len();
        for (int r = 0; r < size; ++r) {
            this->vec[i][r] = J[r];
            this->vec[j][r] = I[r];
        }
    }

    void swap_v (int i, int j){
        vector<A> temp;
        temp = this->vec[i];
        this->vec[i]=this->vec[j];
        this->vec[j] = temp;
    }

public:
    void valueChange(int num,MinVector<A> temp){
        auto size = temp.len();
        for(int i = 0 ; i < size; ++i){
            this->vec[num][i] = temp[i];
        }
    }

    //用于矩阵求逆
    void valueChange(int num,MinVector<A> temp,int NewSize){
        for(int i = NewSize ; i < 2*NewSize; ++i){
            this->vec[num][i-NewSize] = temp[i];
        }
    }

    void _push_back(int num,int t){
        this->vec[num].push_back(t);
    }


    //矩阵列数据改变
    void col_value_Change(int num,MinVector<A> col_vector){
        auto size = this->vec.size();
        for(int i = 0; i < size; ++i){
            this->vec[i][num] = col_vector[i];
        }
    }


};

template <typename T>
MinMatrix<T> Matrix(vector<vector<T>> vec){
    return MinMatrix<T>(vec);
}

template <typename T>
MinMatrix<T> Matrix(MinVector<T> shape){
    return MinMatrix<T>(shape);
}

template <typename T>
MinMatrix<T> Matrix(int num,MinVector<T> vec){
    return MinMatrix<T>(num,vec);
}




#endif //LINEARALGEBRA2_MINMATRIX_H
