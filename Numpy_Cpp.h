//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_NUMPY_CPP_H
#define NEW_ML_CPP_NUMPY_CPP_H

#include <iostream>
#include <ctime>
#include "../LinReg/LinearSystem.h"

using namespace std;


template <typename T>
class Numpy_Cpp{
private:
    vector<vector<T>> vec;
    vector<T> vec2;
    MinVector<T> minVector;
    MinMatrix<T> matrix;

public:
    Numpy_Cpp(){

    }
    Numpy_Cpp(MinMatrix<T> &vec,MinVector<T> &vec2){
        matrix = vec;
        minVector = vec2;
    }

    MinVector<T> argSort(MinVector<T> &x,vector<T> &num_index){
        return x.argsorted(num_index);
    }

    MinVector<T> _Match_Num(MinVector<T> &nearest,MinVector<T> &Y_train){

        auto size = nearest._vector().size();
        vector<T> vec(size);
        for(int i = 0 ; i < size; ++i){
            vec[i] = Y_train[nearest[i]];
        }
        return MinVector<T>(vec);
    }

    MinVector<T> shuffle_indexes(int num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> r(num);
        for(int i = 0; i < num; ++i){
            r[i] = rand()%num;

        }
        return MinVector<T>(r);
    }

    MinVector<T> test_indexes(MinVector<T> &shuffle,int start = 0, int _end = 0){
        vector<T> temp;
        for(int i = start; i < _end; ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    MinVector<T> train_indexes(MinVector<T> &shuffle,int start = 0, int _end = 0){
        vector<T> temp;
        for(int i = start; i < (_end); ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    T sum(MinVector<T> &vec){
        T ret = 0.0;
        auto size = vec._size();
        for(int i = 0; i < size; ++i){
            ret += vec[i];
        }

        return ret;
    }

    T mean(MinVector<T> vec){
        return sum(vec)/vec._size();
    }

    T var(MinVector<T> vec){
        auto x = mean(vec);
        auto ret = 0.0;
        auto size = vec._size();
        for( int i = 0; i < size;++i){
            ret+=pow(vec.getitem(i)-x,2);
        }
        return ret/(size-1);
    }

    T std(MinVector<T> &vec){
        return sqrt(var(vec));
    }


};

#endif //NEW_ML_CPP_NUMPY_CPP_H
