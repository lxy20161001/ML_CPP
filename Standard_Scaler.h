//
// Created by john on 2018-9-6.
//

#ifndef ML_CPP_STANDARDSCALER_H
#define ML_CPP_STANDARDSCALER_H

#include "Numpy_Cpp.h"
#include <iostream>
#include <vector>

template <typename T>
class StandardScaler{
private:
    MinVector<T> mean;
    MinVector<T> scale;
    Numpy_Cpp<T> np;

public:
    StandardScaler(){

    }

    StandardScaler fit(MinMatrix<T> X){
        assert(X.Dim() == 2);
        auto mSize = X.shape()[1];
        for(int i = 0; i < mSize; ++i ){
            this->mean._push_back(np.mean(X.col_vector(i)));
            this->scale._push_back(np.std(X.col_vector(i)));
        }

        return *this;
    }

    MinMatrix<T> tranform(MinMatrix<T> X){
        assert(X.Dim() == 2);
        assert(X.shape()[1] == this->mean.len());
        MinMatrix<T> resX(X.shape());

        auto cSize = X.shape()[1];
        for( int i = 0 ;i < cSize;++i){
            resX.col_value_Change(i,(X.col_vector(i)-this->mean[i])/this->scale[i]);
        }

        return resX;

    }
};

#endif //ML_CPP_STANDARDSCALER_H
