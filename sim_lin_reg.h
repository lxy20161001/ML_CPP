//
// Created by john on 2018-9-7.
//

#ifndef ML_CPP_SIM_LIN_REG_H
#define ML_CPP_SIM_LIN_REG_H

#include <iostream>
#include <vector>
#include <cmath>
#include "MinVector.h"
#include "Numpy_Cpp.h"
#include "split_data.h"

using namespace std;




template<typename T>
T mse_test(MinVector<T> y_predict,MinVector<T> Y_test){
    Numpy_Cpp<T> np;
    return np.sum((y_predict-Y_test)^2)/Y_test.len();
}
template<typename T>
T rmse_test(MinVector<T> y_predict,MinVector<T> Y_test){
    return sqrt(mse_test(y_predict,Y_test));
}

template<typename T>
T mae_test(MinVector<T> y_predict,MinVector<T> Y_test){
    Numpy_Cpp<T> np;
    return np.sum(y_predict.abs_sub(Y_test))/Y_test.len();
}

template<typename T>
T r2_score(MinVector<T> y_predict,MinVector<T> Y_test){
    Numpy_Cpp<T> np;
    return 1-mse_test(y_predict,Y_test)/np.var(Y_test);
}

template<typename T>
class sim_linear_reg {
private:
    MinVector<T> x;
    MinVector<T> y;
public:
    T a, b;

    sim_linear_reg(MinVector<T> x, MinVector<T> y) : x(x), y(y) {

    }

    sim_linear_reg fit() {
        Numpy_Cpp<double> np;

        auto x_mean = np.mean(x);
        auto y_mean = np.mean(y);

        double num = 0.0;
        double d = 0.0;

        for(int i = 0; i < x.len();++i){
            num += (x[i] - x_mean) * (y[i]-y_mean);
            d += pow((x[i]-x_mean),2);
        }

        ////点乘，暂时未找到更快的方法
        //double num = (this->x - x_mean).dot(this->y - y_mean);
        //double d = (this->x - x_mean).dot(this->x - x_mean);

        this->a = num / d;

        this->b = y_mean - a * x_mean;

        return *this;
    }

    MinVector<T> predict(MinVector<T> x_predict) {
        MinVector<T> array;
        auto size = x_predict.len();
        for (int i = 0; i < size; ++i) {
            array._push_back(this->_predict(x_predict[i]));
        }

        return array;
    }

    T score(MinVector<T> x_test,MinVector<T> y_test){
        auto y_predict = this->predict(x_test);
        return r2_score(y_predict,y_test);
    }

private:
    T _predict(T x_single) {
        return this->a * x_single + this->b;
    }
};

template<typename T>
sim_linear_reg<T> Sim_linear_reg(MinVector<T> x, MinVector<T> y) {
    return sim_linear_reg<T>(x, y);
}

template<typename T>
class LinearRegression{
public:
    MinVector<T> coef;
    T interception_;
private:
    MinVector<T> _theta;

public:
    LinearRegression(){

    }

    LinearRegression fit_normal(MinMatrix<T> X_train,MinVector<T> y_train){
        assert(X_train.size() == y_train.len());

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_train.size()), static_cast<unsigned int>(X_train.col_num() + 1));

        auto col_size = X_train.col_num();
        for(int i = 0; i < col_size;++i){
            X_b.col_value_Change(i+1,X_train.col_vector(i));
        }

        MinMatrix<T> one(1,y_train);

        X_b = inv(X_b.T().dot(X_b)).dot(X_b.T()).dot(one.T());

        this->_theta = X_b.col_vector(0);

        this->interception_ = this->_theta[0];

        this->coef = this->_theta.st_vec(1,this->_theta.len());

        return *this;
    }

    MinVector<T> predict(MinMatrix<T> X_predict){
        assert(X_predict.shape()[1] == this->coef.len());

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_predict.size()), static_cast<unsigned int>(X_predict.col_num() + 1));
        auto col_size = X_predict.col_num();
        for(int i = 0; i < col_size;++i){
            X_b.col_value_Change(i+1,X_predict.col_vector(i));
        }

        MinMatrix<T> t(this->_theta.len(),this->_theta);

        return X_b.dot(t.T()).col_vector(0);

    }

    T score(MinMatrix<T> x_test,MinVector<T> y_test){
        auto y_predict = this->predict(x_test);
        return r2_score(y_predict,y_test);

    }
};

void mul_lin_reg_score(){
    dataSet dSet;

    auto x = Matrix(dSet.load_boston_data());
    auto y = minVector(dSet.load_boston_target());

    x = x(y,50);
    y = y(y,50);

    auto Mix = train_test_split(x,y);
    auto X_train = get<0>(Mix);
    auto X_test = get<1>(Mix);
    auto Y_train = get<2>(Mix);
    auto Y_test = get<3>(Mix);

    LinearRegression<double> reg;
    auto fit = reg.fit_normal(X_train,Y_train);

    cout<<reg.score(X_test,Y_test)<<endl;
}


#endif //ML_CPP_SIM_LIN_REG_H
