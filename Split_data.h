//
// Created by john on 2018-9-10.
//

#ifndef ML_CPP_SPLIT_DATA_H
#define ML_CPP_SPLIT_DATA_H

#include <vector>
#include <cassert>
#include <tuple>
#include "MinVector.h"
#include "MinMatrix.h"
#include "Numpy_Cpp.h"

using namespace std;

template <typename T>
tuple<MinMatrix<T>,MinMatrix<T>,MinVector<T>,MinVector<T>>  train_test_split(MinMatrix<T> X,MinVector<T> y, T test_ratio = 0.2){
        assert(X.shape()[0] == y.len());
        Numpy_Cpp<T> np;

        MinVector<T> shuffle_indexes = np.shuffle_indexes(X.size());

        auto test_size = int(X.size()*test_ratio);

        MinVector<T> test_indexes = np.test_indexes(shuffle_indexes,0,test_size);

        MinVector<T> train_indexes = np.train_indexes(shuffle_indexes,test_size,shuffle_indexes.len());


        MinMatrix<T> X_train = X.indexFancy(train_indexes,X);
        MinMatrix<T> X_test = X.indexFancy(test_indexes,X);
        MinVector<T> Y_train = y.indexFancy(train_indexes,y);
        MinVector<T> Y_test = y.indexFancy(test_indexes,y);

        tuple<MinMatrix<T>,MinMatrix<T>,MinVector<T>,MinVector<T>> newT;
        newT = make_tuple(X_train,X_test,Y_train,Y_test);


        return newT;
    }
template <typename T>
tuple<MinVector<T>,MinVector<T>,MinVector<T>,MinVector<T>>  train_test_split(MinVector<T> X,MinVector<T> y, T test_ratio = 0.2){
        assert(X.len() == y.len());
    Numpy_Cpp<T> np;
        MinVector<T> shuffle_indexes = np.shuffle_indexes(X.len());

        auto test_size = int(X.len()*test_ratio);
        auto train_size = X.len() - test_size;


        MinVector<T> test_indexes = np.test_indexes(shuffle_indexes,0,test_size);
        MinVector<T> train_indexes = np.train_indexes(shuffle_indexes,test_size,shuffle_indexes.len());


        MinVector<T> X_train = X.indexFancy(train_indexes,X);

        MinVector<T> X_test = X.indexFancy(test_indexes,X);

        MinVector<T> Y_train = y.indexFancy(train_indexes,y);

        MinVector<T> Y_test = y.indexFancy(test_indexes,y);


        tuple<MinVector<T>,MinVector<T>,MinVector<T>,MinVector<T>> newT;
        newT = make_tuple(X_train,X_test,Y_train,Y_test);


        return newT;
    }

#endif //ML_CPP_SPLIT_DATA_H
