//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_NUMPY_CPP_H
#define NEW_ML_CPP_NUMPY_CPP_H

#include <iostream>
#include <ctime>
#include <random>
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

    MinVector<T> shuffle_indexes(const unsigned int &num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> r(num);
        for(int i = 0; i < num; ++i){
            r[i] = rand()%num;

        }
        return MinVector<T>(r);
    }

    MinVector<T> test_indexes(MinVector<T> &shuffle,const int start = 0, const int _end = 0){
        vector<T> temp;
        for(int i = start; i < _end; ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    MinVector<T> train_indexes(MinVector<T> &shuffle,const int start = 0, const int _end = 0){
        vector<T> temp;
        for(int i = start; i < (_end); ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    T sum(MinVector<T> &vec) {
        T ret = 0.0;
        auto size = vec._size();
        for(int i = 0; i < size; ++i){
            ret += vec[i];
        }

        return ret;
    }

    T sum(MinVector<T> &&vec) {
        T ret = 0.0;
        auto size = vec._size();
        for(int i = 0; i < size; ++i){
            ret += vec[i];
        }

        return ret;
    }

    T mean(MinVector<T> &vec){
        return sum(vec)/vec._size();
    }

    T var(MinVector<T> &vec)  {
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

    MinVector<T> line_space_rand(T &&st,T &&en,T size){
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<double > dist(st,en);
        vector<T> vec(size);
        for( int i = 0; i < size;++i){
            vec[i] = dist(rng);
        }
        return MinVector<T>(vec);
    }

    MinVector<T> random_(T &&num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> vec(num);
        for(int i = 0;i<num;++i){
            vec[i] = (rand()%100/(double)101);
        }

        return MinVector<T>(vec);
    }

    MinVector<T> randint(const unsigned &size){
        //srand(static_cast<unsigned int>(time(NULL)));
        vector<T> vec;
        for(int i = 0;i<size;++i){
            vec.push_back(rand()%size);
        }

        return MinVector<T>(vec);
    }


    MinMatrix<T> hstack(MinMatrix<T> &&a,MinMatrix<T> &b){
        MinMatrix<T> h_stack;
        for( int i = 0; i < a.col_num();++i){
            h_stack.addVector(a.col_vector(i));
        }

        for( int i = 0; i < b.col_num();++i){
            h_stack.addVector(b.col_vector(i));
        }

        return h_stack._T();
    }

    MinMatrix<T> vec_to_mat(MinVector<T> &vec){
        MinMatrix<T> matrix1;
        matrix1.addVector(vec);
        return matrix1._T();
    }



};

#endif //NEW_ML_CPP_NUMPY_CPP_H
