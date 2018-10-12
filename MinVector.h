//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_CONVECTOR_H
#define NEW_ML_CPP_CONVECTOR_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

const double EPSILON=1e-8;

template<typename T>
class MinVector {
    vector<T> vec;


public:
    MinVector(){
        vec={};
    }

    MinVector(vector<T> vec) : vec(move(vec)) {

    }

    MinVector(int num){
        this->vec = vector<T>(num,0);
    }

    int _size() {
        return this->vec.size();
    }

    vector<T> _vector(){
        return this->vec;
    }

    void _push_back(T k){
        this->vec.push_back(k);
    }

    T &getitem(int index) {
        return vec[index];
    }

    T &operator[](int index) {
        return vec[index];
    }

    void __str__() {
        cout << "Vector : (";
        for (int i=0; i < this->vec.size(); ++i) {
            if (i < vec.size() - 1) {
                cout << vec[i] << ",";
            } else {
                cout << vec[i];
            }
        }
        cout << ")" << endl;
    }

    friend ostream &operator<<(ostream &out, MinVector<T> vec) {

        out << "Vector : (";
        for (int i=0; i < vec.vec.size(); i++) {
            if (i != vec.vec.size() - 1) {
                out << vec.vec[i] << ',';
            } else {
                out << vec.vec[i];
            }
        }

        out << ")";
        return out;
    }

    MinVector &__add__(vector<T> vec) {
        assert(this->_size() == vec.size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) + vec[i];
        }
        return *this;
    }

    MinVector &operator+(vector<T> vec) {
        assert(this->_size() == vec.size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) + vec[i];
        }
        return *this;
    }

    MinVector &__add__(MinVector &vec) {
        assert(this->_size() == vec._size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) + vec[i];
        }
        return *this;
    }

    MinVector &operator+(MinVector &vec) {
        assert(this->_size() == vec._size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) + vec[i];
        }
        return *this;
    }

    MinVector &__sub__(vector<T> vec) {
        assert(this->_size() == vec.size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) - vec[i];
        }
        return *this;
    }

    MinVector &operator-(vector<T> vec) {
        assert(this->_size() == vec.size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) - vec[i];
        }
        return *this;
    }

    MinVector &__sub__(MinVector &vec) {
        assert(this->_size() == vec._size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) - vec[i];
        }
        return *this;
    }

    MinVector &operator-(MinVector &vec) {
        assert(this->_size() == vec._size());
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) - vec[i];
        }
        return *this;
    }

    MinVector &operator-(T k){
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) - k;
        }
        return *this;
    }

    MinVector &__mul__(T k) {
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=k * this->getitem(i);
        }
        return *this;
    }

    MinVector &operator*(T k) {
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) * k;
        }
        return *this;
    }

    MinVector &__rmul__(T k) {
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=k * this->getitem(i);
        }
        return *this;
    }

    T dot(vector<T> vec) {
        assert(this->_size() == vec.size());
        double ret=0;
        auto size=vec.size();
        for (int i=0; i < size; ++i) {
            ret+=(vec[i] * this->vec[i]);
        }
        return ret;
    }

    T dot(MinVector<T> vec) {
        assert(this->_size() == vec._size());
        double ret=0;
        auto size=vec._size();
        for (int i=0; i < size; ++i) {
            ret+=(vec[i] * this->vec[i]);
        }
        return ret;
    }

    T dot(T k) {
        T ret=0.0;
        auto size=this->vec.size();
        for (int i=0; i < size; ++i) {
            ret+=this->vec[i] * k;
        }

        return ret;
    }

    MinVector &__div__(T k) {
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) * 1 / k;
        }
        return *this;
    }

    MinVector &operator/(T k) {
        for (int i=0; i < this->_size(); ++i) {
            this->getitem(i)=this->getitem(i) * 1 / k;
        }
        return *this;
    }

    MinVector<T> &operator/(MinVector<T> k) {


        auto size=this->vec.size();
        for (int i=0; i < size; i++) {
            this->getitem(i)=this->getitem(i) * 1 / k[i];
        }
        return *this;
    }

    MinVector<T> zero(int dim) {
        vector<T> vec(dim, 0);
        return MinVector(vec);
    }

    T norm() {
        auto ret=0.0;
        for (int i=0; i < this->_size(); ++i) {
            ret+=(this->vec[i] * this->vec[i]);
        }

        return sqrt(ret);
    }

    MinVector normalize() {
        if (this->norm() < EPSILON) {
            throw "Normalize error! norm is zero.";
        }

        return MinVector(this->vec) / this->norm();
    }

    MinVector __pos__() {
        return *this * 1;
    }

    MinVector __neg__() {
        return *this * -1;
    }

    T euc_disance(MinVector<T> b){
        auto ol = 0.0;
        auto ol2 = 0.0;
        auto size = b._size();

        for( int i = 0; i < size; i+=2){
            ol += pow(this->vec[i] - b[i] , 2);
            ol2 += pow(this->vec[i+1] - b[i+1] , 2);
        }

        return sqrt(ol+ol2);
    }

public:
    MinVector argsorted(vector<T> num_index){
        auto size = this->vec.size();
        if(size < 100){
            return arg_insertionSort(num_index);
        }else{
            return arg_shellSort(num_index);
            //return Me_Start(num_index);
        }
    }

    MinVector<T> sorted(){
        auto size = this->vec.size();
        if (size < 500) {
            return insertionSort();
        } else {
            return shellSort();
        }
    }

private:
    MinVector<T> arg_insertionSort(vector<T> indexTemp) {
        auto size = this->vec.size();

        for (int i = 0; i < size; ++i) {
            auto e = this->vec[i];
            auto ie = indexTemp[i];
            int j;
            for (j = i; j > 0 && e < this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
                indexTemp[j] = indexTemp[j - 1];
            }
            this->vec[j] = e;
            indexTemp[j] = ie;
        }
        return MinVector(indexTemp);
    }

    MinVector<T> insertionSort() {

        auto size = this->vec.size();

        for (int i = 0; i < size; ++i) {
            auto e = this->vec[i];
            int j;
            for (j = i; j > 0 && e < this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
            }
            this->vec[j] = e;
        }
        return MinVector(this->vec);
    }

    MinVector<T> arg_shellSort(vector<T> indexTemp) {
        auto size = this->vec.size();
        int h = 1, i, j;
        while (h < size / 3) {
            h = 3 * h + 1;
        }

        for (; h > 0; h /= 3) {
            for (i = h; i < size; i++) {
                T temp = this->vec[i];
                T inTemp = indexTemp[i];

                for (j = i - h; j >= 0 && this->vec[j] > temp; j = j - h) {
                    this->vec[j + h] = this->vec[j];
                    indexTemp[j + h] = indexTemp[j];
                }
                this->vec[j + h] = temp;
                indexTemp[j + h] = inTemp;
            }
        }
        return MinVector(indexTemp);
    }

    MinVector<T> shellSort() {

        auto size = this->vec.size();

        int h = 1, i, j;
        while (h < size / 3) {
            h = 3 * h + 1;
        }

        for (; h > 0; h /= 3) {
            for (i = h; i < size; i++) {
                T temp = this->vec[i];
                for (j = i - h; j >= 0 && this->vec[j] > temp; j = j - h) {
                    this->vec[j + h] = this->vec[j];
                }
                this->vec[j + h] = temp;
            }
        }
        return MinVector(this->vec);
    }

public:
    MinVector<T> indexFancy(MinVector<double> a, MinVector<T> b) {

        int size = a._size();
        MinVector<T> temp(size);
        for (int i = 0; i < size; ++i) {
            temp.vec[i] = b[a[i]];
        }
        return temp;
    }

};

#endif //NEW_ML_CPP_CONVECTOR_H
