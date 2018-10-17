//
// Created by john on 2018-10-12.
//

#ifndef NEW_ML_CPP_STANDARDSDCALER_H
#define NEW_ML_CPP_STANDARDSDCALER_H

#include "Numpy_Cpp/Numpy_Cpp.h"

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
        assert(X.dim() == 2);
        auto mSize = X.shape()[1];
        for(int i = 0; i < mSize; ++i ){
            auto X_col_i = X.col_vector(i);
            this->mean._push_back(np.mean(X_col_i));
            this->scale._push_back(np.std(X_col_i));
        }

        return *this;
    }

    MinMatrix<T> tranform(MinMatrix<T> X){
        assert(X.dim() == 2);
        assert(X.shape()[1] == this->mean._size());


        auto cSize = X.shape()[1];
        auto res_x = vector<vector<T>>(cSize);

        for( int i = 0 ;i < cSize;++i){
            res_x[i] = ((X.col_vector(i)-this->mean[i])/this->scale[i])._vector();
        }

        return MinMatrix<T>(res_x);

    }
};

#endif //NEW_ML_CPP_STANDARDSDCALER_H
