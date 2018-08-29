

#ifndef LINEARALGEBRA2_MINMATRIX_H
#define LINEARALGEBRA2_MINMATRIX_H

#include "MinVector.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template<typename A>
class MinMatrix {
private:
private:
    vector<vector<A>> vec;
    vector<vector<A>> vec2;
public:
    MinMatrix(vector<vector<A>> vec) : vec(vec) {

    }

    MinMatrix() {
        vec = {};
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


    MinVector<A> row_vector(int index) {
        return MinVector<A>(vec[index]);
    }

    MinVector<A> col_vector(int index) {
        vector<A> newVec;
        for (int i = 0; i < vec.size(); i++) {
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

    MinVector<int> shape() {

        int r = vec.size();
        int c = row_vector(0).len();;
        return MinVector<int>({r, c});
    }


    MinMatrix<A> add(MinMatrix<A> matrix) {
        assert(this->size() == matrix.size());
        vector<vector<A>> newVec(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            newVec[i] = vector<double>(matrix.row_vector(0).len());
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) + matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator+(MinMatrix<A> &matrix) {
        assert(this->size() == matrix.size());
        vector<vector<A>> newVec(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            newVec[i] = vector<double>(matrix.row_vector(0).len());
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) + matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);
    }


    MinMatrix<A> sub(MinMatrix<A> matrix) {
        assert(this->size() == matrix.size());
        vector<vector<A>> newVec(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            newVec[i] = vector<double>(matrix.row_vector(0).len());
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) - matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator-(MinMatrix<A> &matrix) {
        assert(this->size() == matrix.size());
        vector<vector<A>> newVec(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            newVec[i] = vector<double>(matrix.row_vector(0).len());
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) - matrix.getitem({i, j});
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> mul(A k) {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) * k;
            }
        }
        return MinMatrix<A>(newVec);

    }

    MinMatrix<A> operator*(A k) {
        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
                newVec[i][j] = this->getitem({i, j}) * k;
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> rmul(A k) {

        vector<vector<A>> newVec(static_cast<unsigned int>(this->size()));
        for (int i = 0; i < this->size(); i++) {
            newVec[i] = vector<double>(this->row_vector(0).len());
        }
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->row_vector(0).len(); j++) {
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

        out << "Matrix : (";
        for (int i = 0; i < matrix.size(); i++) {
            if (i != matrix.size() - 1) {
                out << matrix.row_vector(i) << ',';
            } else {
                out << matrix.row_vector(i);
            }
        }

        out << ")";
        return out;
    }


    MinVector<A> operator[](int k) {
        assert(k < vec.size() && k >= 0);

        return MinVector<A>(this->row_vector(k));
    }

    MinMatrix<A> dot(MinMatrix<A> &a) {
        assert(col_num() == a.row_num());
        vector<vector<A>> newVec;
        for (int i = 0; i < col_num(); i++) {
            newVec.push_back(vector<double>());
        }
        for (int i = 0; i < row_num(); i++) {
            for (int j = 0; j < a.col_num(); j++) {
                newVec[i].push_back(row_vector(i).dot(a.col_vector(j)));
            }
        }
        return MinMatrix(newVec);
    }


    MinVector<A> dot(MinVector<A> a) {
        assert(col_num() == a.len());
        vector<double> vecTemp;
        for (int i = 0; i < col_num(); i++) {
            vecTemp.push_back(row_vector(i).dot(a));
        }
        return MinVector<A>(vecTemp);
    }

    MinMatrix<A> T() {

        vector<vector<A>> newVec;
        for (int i = 0; i < col_num(); i++) {
            newVec.push_back(vector<double>());
        }
        for (int i = 0; i < this[0].size(); i++) {
            for (int j = 0; j < col_num(); j++) {
                newVec[i].push_back(col_vector(i)[j]);
            }
        }
        return MinMatrix(newVec);
    }

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
        for (int i = 0; i < minVector.len(); ++i) {
            vec.push_back(minVector[i]);
        }
        this->vec.push_back(vec);
        return MinMatrix<A>(this->vec);
    }

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

    MinMatrix<A> indexFancy(MinVector<A> temp, MinMatrix<A> vec) {
        MinMatrix<A> indexMinMatrix;
        int size = temp.len();
        for (int i = 0; i < size; ++i) {

            indexMinMatrix.addMinVector(vec[temp[i]]);
        }
        return indexMinMatrix;
    }

   // MinVector<A> operator()(MinVector<A> a, MinVector<A> b) {
   //     return indexFancy(a, b);
   // }
//
   // MinVector<A> indexFancy(A a, MinVector<A> b) {
   //     vector<A> temp;
   //     for (int i = 0; i < b.len(); ++i) {
   //         temp.push_back(getitem(MinVector<A>({a, b.getitem(i)})));
   //     }
   //     return MinVector<A>(temp);
   // }
//
   // MinVector<A> operator()(A a, MinVector<A> b) {
   //     return indexFancy(a, b);
   // }
//
   // MinVector<A> indexFancy(vector<A> a, vector<A> b) {
   //     vector<A> temp;
   //     for (int i = 0; i < a.size(); ++i) {
   //         temp.push_back(getitem(MinVector<A>({a[i], b[i]})));
   //     }
   //     return MinVector<A>(temp);
   // }
//
   // MinVector<A> operator()(vector<A> a, vector<A> b) {
   //     return indexFancy(a, b);
   // }


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
        for (int i = 0; i < T.len(); ++i) {
            this->vec[num][i] = T[i];
        }
    }

    void  swap(int i,int j , MinVector<A> J,MinVector<A> I){
        for (int r = 0; r < J.len(); ++r) {
            this->vec[i][r] = J[r];
            this->vec[j][r] = I[r];
        }
      
    }

};

#endif //LINEARALGEBRA2_MINMATRIX_H
