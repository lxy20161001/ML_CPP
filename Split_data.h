//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_DATA_SPLIT_H
#define NEW_ML_CPP_DATA_SPLIT_H


#include "Knn_Ang.h"

using namespace std;


template<typename T>
tuple<MinMatrix<T>, MinMatrix<T>, MinVector<T>, MinVector<T>>
train_test_split(MinMatrix<T> X, MinVector<T> y, T test_ratio=0.2) {
    assert(X._Matrix().size() == y._size());

    Numpy_Cpp<T> np;

    MinVector<T> shuffle_indexes=np.shuffle_indexes(X._Matrix().size());

    auto test_size=int(X._Matrix().size() * test_ratio);

    MinVector<T> test_indexes=np.test_indexes(shuffle_indexes, 0, test_size);

    MinVector<T> train_indexes=np.train_indexes(shuffle_indexes, test_size, shuffle_indexes._size());


    MinMatrix<T> X_train=X.indexFancy(train_indexes, X);
    MinMatrix<T> X_test=X.indexFancy(test_indexes, X);
    MinVector<T> Y_train=y.indexFancy(train_indexes, y);
    MinVector<T> Y_test=y.indexFancy(test_indexes, y);
//
    tuple<MinMatrix<T>, MinMatrix<T>, MinVector<T>, MinVector<T>> newT;
    newT=make_tuple(X_train, X_test, Y_train, Y_test);


    return newT;
}

template<typename T>
tuple<MinVector<T>, MinVector<T>, MinVector<T>, MinVector<T>>
train_test_split(MinVector<T> X, MinVector<T> y, T test_ratio=0.2) {
    assert(X._size() == y._size());

    Numpy_Cpp<T> np;

    MinVector<T> shuffle_indexes=np.shuffle_indexes(X._size());

    auto test_size=int(X._size() * test_ratio);


    MinVector<T> test_indexes=np.test_indexes(shuffle_indexes, 0, test_size);
    MinVector<T> train_indexes=np.train_indexes(shuffle_indexes, test_size, shuffle_indexes._size());


    MinVector<T> X_train=X.indexFancy(train_indexes, X);

    MinVector<T> X_test=X.indexFancy(test_indexes, X);

    MinVector<T> Y_train=y.indexFancy(train_indexes, y);

    MinVector<T> Y_test=y.indexFancy(test_indexes, y);


    tuple<MinVector<T>, MinVector<T>, MinVector<T>, MinVector<T>> newT;
    newT=make_tuple(X_train, X_test, Y_train, Y_test);


    return newT;
}

#endif //NEW_ML_CPP_DATA_SPLIT_H
