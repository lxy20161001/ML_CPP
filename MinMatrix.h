//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_CONMATRIX_H
#define NEW_ML_CPP_CONMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "ConVector.h"

using namespace std;

template<typename T>
class MinMatrix {
    vector<vector<T>> vec;
public:
    MinMatrix(vector<vector<T>> vec) : vec(vec) {

    }

    MinMatrix() {
        vec={};
    }

    MinMatrix(int num, MinVector<T> &vec) {
        for (int i=0; i < num; ++i) {
            this->vec.push_back(vec._vector());
        }
    }

    MinMatrix(T &r, T &c) {
        for (int i=0; i < r; ++i) {
            this->vec.push_back(vector<T>(c));
        }
    }

    MinMatrix(const MinMatrix &matrix) {
        this->vec=matrix.vec;
    }

    MinMatrix &operator=(const MinMatrix &matrix) {
        this->vec=matrix.vec;
        return *this;
    }

    T dim() const {
        return 2;
    }

    MinMatrix &addVector(MinVector<T> &vec) {
        this->vec.push_back(vec._vector());
        return *this;
    }

    MinMatrix &addVector(MinVector<T> &&vec) {
        this->vec.push_back(vec._vector());
        return *this;
    }

    MinMatrix &addVector(vector<T> &vec) {
        this->vec.push_back(vec);
        return *this;
    }

    MinMatrix &addMatrix(MinMatrix<T> &&m){
        assert(this->vec[0].size() == m[0]._size());
        auto size = m.size();
        for( int i = 0; i < size; ++i){
            this->vec.push_back(m.vec[i]);
        }
        return *this;
    }

    MinMatrix addEle(int &index, MinVector<T> &vec) {
        auto size=vec._size();
        for (int i=0; i < size; ++i) {
            this->vec[index].push_back(vec[i]);
        }
        return *this;
    }

    vector<vector<T>> &_Matrix() {
        return this->vec;
    }

    MinMatrix zero(const int &&r, const int &&c) {
        MinMatrix matrix;
        for (int i=0; i < r; ++i) {
            auto zero_=MinVector<T>().zero(c);
            matrix.addVector(zero_);
        }
        return matrix;
    }

    MinMatrix zero(const int &r, const int &c) {
        MinMatrix matrix;
        for (int i=0; i < r; ++i) {
            auto zero_=MinVector<T>().zero(c);
            matrix.addVector(zero_);
        }
        return matrix;
    }

    MinMatrix ones(const int &&r, const int &&c) {
        MinMatrix matrix;
        for (int i=0; i < r; ++i) {
            auto one_=MinVector<T>().one(c);
            matrix.addVector(one_);
        }
        return matrix;
    }

    MinMatrix zero(const vector<T> &shape) {
        int r=shape[0];
        int c=shape[1];
        MinMatrix matrix;
        for (int i=0; i < r; ++i) {
            auto zero_=MinVector<T>().zero(c);
            matrix.addVector(zero_);
        }
        return matrix;
    }

    MinMatrix zero(const MinVector<T> &shape) {
        int r=shape[0];
        int c=shape[1];
        MinMatrix matrix;
        for (int i=0; i < r; ++i) {
            auto zero_=MinVector<T>().zero(c);
            matrix.addVector(zero_);
        }
        return matrix;
    }


    MinMatrix identiry(const int &&n) {
        auto _zero=this->zero(n, n);
        for (int i=0; i < n; ++i) {
            _zero.vec[i][i]=1;
        }
        return _zero;
    }


    MinVector<T> row_vector(const int &index) {
        return this->vec[index];
    }

    MinVector<T> row_vector(const int &&index) {
        return this->vec[index];
    }

    MinVector<T> col_vector(const int &index) const {
        auto const size=vec.size();
        vector<T> col(size);
        for (int i=0; i < size; ++i) {
            col[i]=vec[i][index];
        }
        return MinVector<T>(col);
    }

    MinVector<T> col_vector(const int &&index) {
        auto const size=vec.size();
        vector<T> col(size);
        for (int i=0; i < size; ++i) {
            col[i]=vec[i][index];
        }
        return MinVector<T>(col);
    }

    T __getitem__(const int &r, const int &c) {
        return this->vec[r][c];
    }

    T __getitem__(const int r, const int c) {
        return this->vec[r][c];
    }

    T __getitem__(const vector<T> &vec) {
        return this->vec[vec[0]][vec[1]];
    }


    T row_num() const {
        return this->vec.size();
    }

    T col_num() const {
        return this->vec[0].size();
    }

    MinVector<T> shape() const {
        return MinVector<T>({this->row_num(), this->col_num()});
    }

    T size() const {
        return this->vec.size();
    }


    friend ostream &operator<<(ostream &out, MinMatrix<T> &matrix) {

        out << "Matrix : (" << endl;
        for (int i=0; i < matrix.vec.size(); i++) {
            if (i != matrix.size() - 1) {
                out << matrix.row_vector(i) << ',' << endl;
            } else {
                out << matrix.row_vector(i) << endl;
            }
        }

        out << ")";
        return out;
    }

    friend ostream &operator<<(ostream &out, MinMatrix<T> &&matrix) {

        out << "Matrix : (" << endl;
        for (int i=0; i < matrix.vec.size(); i++) {
            if (i != matrix.size() - 1) {
                out << matrix.row_vector(i) << ',' << endl;
            } else {
                out << matrix.row_vector(i) << endl;
            }
        }

        out << ")";
        return out;
    }

    MinVector<T> operator[](int index) {
        return this->row_vector(index);
    }


    MinMatrix &__add__(MinMatrix &matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) + matrix[i]._vector())._vector();
        }
        return *this;
    }

    MinMatrix &operator+(MinMatrix &matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) + matrix[i]._vector())._vector();
        }
        return *this;
    }

    MinMatrix &__sub__(MinMatrix &matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) - matrix[i]._vector())._vector();
        }
        return *this;
    }

    MinMatrix sub(MinMatrix &&matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        MinMatrix matrix1;
        for (int i=0; i < this->size(); ++i) {
            matrix1.addVector((this->row_vector(i) - matrix[i]._vector())._vector());
        }
        return matrix1;
    }


    MinMatrix &operator-(MinMatrix &matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) - matrix[i]._vector())._vector();
        }
        return *this;
    }

    MinMatrix &operator-(MinMatrix &&matrix) {
        assert(this->shape()[0] == matrix.shape()[0] && this->shape()[1] == matrix.shape()[1]);
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) - matrix[i]._vector())._vector();
        }
        return *this;
    }

    MinMatrix &__mul__(T k) {
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) * k)._vector();
        }
        return *this;
    }

    MinMatrix &operator*(T k) {
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) * k)._vector();
        }
        return *this;
    }

    MinMatrix &__div__(T k) {
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) * 1 / k)._vector();
        }
        return *this;
    }

    MinMatrix &operator/(T k) {
        for (int i=0; i < this->size(); ++i) {
            this->vec[i]=(this->row_vector(i) * 1 / k)._vector();
        }
        return *this;
    }

    MinMatrix &__pos__() const {
        return *this * 1;
    }

    MinMatrix &__neg__() const {
        return *this * -1;
    }

    MinMatrix dot(MinMatrix &matrix) {
        assert(this->col_num() == matrix.row_num());
        auto const size=row_num();
        auto size2=matrix.col_num();
        vector<vector<T>> vec(size);
        vector<T> vec_c(size2);

        for (int i=0; i < size; ++i) {
            for (int j=0; j < size2; ++j) {
                auto mat_col_vector_j=matrix.col_vector(j);
                vec_c[j]=this->row_vector(i).dot(mat_col_vector_j);
            }
            vec[i]=vec_c;
        }
        return MinMatrix(vec);
    }

    MinMatrix dot(MinMatrix &&matrix) {
        assert(this->col_num() == matrix.row_num());
        auto const size=row_num();
        auto size2=matrix.col_num();
        vector<vector<T>> vec(size);
        vector<T> vec_c(size2);

        for (int i=0; i < size; ++i) {
            for (int j=0; j < size2; ++j) {
                auto mat_col_vector_j=matrix.col_vector(j);
                vec_c[j]=this->row_vector(i).dot(mat_col_vector_j);
            }
            vec[i]=vec_c;
        }
        return MinMatrix(vec);
    }

    MinVector<T> dot(MinVector<T> &vec) {
        assert(this->shape()[1] == vec._size());
        auto const size=this->shape()[0];
        auto _vec=MinVector<T>();
        for (int i=0; i < size; ++i) {
            auto ele=this->row_vector(i).dot(vec);
            _vec._push_back(ele);
        }
        return _vec;
        //矩阵和向量点乘 =》 列 乘以 行
    }

    MinVector<T> dot(MinVector<T> &&vec) {
        assert(this->shape()[1] == vec._size());
        auto const size=this->shape()[0];
        auto _vec=MinVector<T>();
        for (int i=0; i < size; ++i) {
            auto ele=this->row_vector(i).dot(vec);
            _vec._push_back(ele);
        }
        return _vec;
        //矩阵和向量点乘 =》 列 乘以 行
    }

    MinMatrix _T() {
        MinMatrix mat(this->vec);
        MinMatrix matT;
        auto const size=this->vec[0].size();
        for (int i=0; i < size; ++i) {
            auto mat_col_i=mat.col_vector(i);
            matT.addVector(mat_col_i);
        }
        return matT;
    }


    void elimination(const int &num, MinVector<T> &ele) {
        this->vec[num]=ele._vector();
    }

    void col_value_Change(const int &num, MinVector<T> &col_vector) {
        auto const size=this->vec.size();
        for (int i=0; i < size; ++i) {
            this->vec[i][num]=col_vector[i];
        }
    }

    void row_value_Change(const int &num, MinVector<T> &row_vactor) {
        this->vec[num]=row_vactor._vector();
    }

public:
    MinMatrix<T> sorted() {
        if (this->vec.size() < 500) {
            return insertionSort();
        } else {
            return shellSort();
        }
    }


private:
    //考虑到暂时使用的矩阵比较小，于是使用插入算法
    MinMatrix<T> insertionSort() {
        for (int i=0; i < this->vec.size(); ++i) {
            vector<T> e=this->vec[i];
            int j;
            for (j=i; j > 0 && e > this->vec[j - 1]; j--) {
                this->vec[j]=this->vec[j - 1];
            }
            this->vec[j]=e;
        }
        return MinMatrix(this->vec);
    }

    MinMatrix<T> shellSort() {
        int h=1, i, j;
        auto const size=this->vec.size();
        vector<T> temp;
        while (h < size / 3) {
            h=3 * h + 1;
        }

        for (; h > 0; h/=3) {
            for (i=h; i < this->vec.size(); i++) {
                temp=this->vec[i];
                for (j=i - h; j >= 0 && this->vec[j] > temp; j=j - h) {
                    this->vec[j + h]=this->vec[j];
                }
                this->vec[j + h]=temp;
            }
        }
        return MinMatrix(this->vec);
    }

public:
    MinMatrix<T> indexFancy(MinVector<T> &temp, MinMatrix<T> &vec) {
        vector<vector<T>> index;
        auto const size=temp._vector().size();
        for (int i=0; i < size; ++i) {
            index.push_back(vec[temp[i]]._vector());
        }
        return MinMatrix(index);
    }


    MinMatrix<T> operator()(MinVector<T> &test, T num) {
        auto const size=test._size();
        MinMatrix<T> newMat;
        for (int i=0; i < size; ++i) {
            if (test[i] < num) {
                newMat.addVector(this->vec[i]);
            }
        }

        return newMat;
    }

    void  matrix_change(const MinMatrix<T> &M){
        this->vec = M.vec;
    }

};

template<typename T>
T len(MinMatrix<T> matrix) {
    return matrix.size();
}

template<typename T>
void print(MinMatrix<T> matrix){
    cout<<matrix<<endl;
}


#endif //NEW_ML_CPP_CONMATRIX_H
