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
T mse_test(MinVector<T> y_predict, MinVector<T> Y_test) {
    Numpy_Cpp<T> np;
    return np.sum((y_predict - Y_test) ^ 2) / Y_test.len();
}

template<typename T>
T rmse_test(MinVector<T> y_predict, MinVector<T> Y_test) {
    return sqrt(mse_test(y_predict, Y_test));
}

template<typename T>
T mae_test(MinVector<T> y_predict, MinVector<T> Y_test) {
    Numpy_Cpp<T> np;
    return np.sum(y_predict.abs_sub(Y_test)) / Y_test.len();
}

template<typename T>
T r2_score(MinVector<T> y_predict, MinVector<T> Y_test) {
    Numpy_Cpp<T> np;
    return 1 - mse_test(y_predict, Y_test) / np.var(Y_test);
}


//简单线性回归
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

        for (int i = 0; i < x.len(); ++i) {
            num += (x[i] - x_mean) * (y[i] - y_mean);
            d += pow((x[i] - x_mean), 2);
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

    T score(MinVector<T> x_test, MinVector<T> y_test) {
        auto y_predict = this->predict(x_test);
        return r2_score(y_predict, y_test);
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



//多元线性回归
template<typename T>
class LinearRegression {
public:
    MinVector<T> coef;
    T interception_;
private:
    MinVector<T> _theta;
    Numpy_Cpp<T> np;

public:
    LinearRegression() {

    }

    LinearRegression fit_normal(MinMatrix<T> X_train, MinVector<T> y_train) {
        assert(X_train.size() == y_train.len());

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_train.size()),
                                               static_cast<unsigned int>(X_train.col_num() + 1));

        auto col_size = X_train.col_num();
        for (int i = 0; i < col_size; ++i) {
            X_b.col_value_Change(i + 1, X_train.col_vector(i));
        }

        MinMatrix<T> one(1, y_train);

        X_b = inv(X_b.T().dot(X_b)).dot(X_b.T()).dot(one.T());

        this->_theta = X_b.col_vector(0);

        this->interception_ = this->_theta[0];

        this->coef = this->_theta.st_vec(1, this->_theta.len());

        return *this;
    }

    T J(MinMatrix<T> theta, MinMatrix<T> X_b, MinMatrix<T> y) {
        try {
            return np.sum((y.sub(X_b.dot(theta))).row_vector(0) ^ 2) / y.shape()[0];
        } catch (exception e) {
            return -1.0 / 0.0;
        }
    }

    MinMatrix<T> dJ(MinMatrix<T> theta, MinMatrix<T> X_b, MinMatrix<T> y) {
        return X_b.T().dot(X_b.dot(theta).sub_b(y)) * 2 / y.shape()[0];
    }

    
    //随机梯度下降
    LinearRegression fit_sgd(MinMatrix<T> X_train, MinMatrix<T> y_train, T n_iters = 100, T t0 = 5, T t1 = 50,T per=1) {
        assert(X_train.shape()[0] == y_train.shape()[1]);

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_train.size()),
                                               static_cast<unsigned int>(X_train.col_num() + 1));

        auto col_size = X_train.col_num();
        for (int i = 0; i < col_size; ++i) {
            X_b.col_value_Change(i + 1, X_train.col_vector(i));
        }

        auto initia = np.zero(X_b.shape()[1]);
        auto initial_theta = Matrix(1, initia).T();

        this->_theta = sgd(X_b, y_train.T(), initial_theta, n_iters, t0, t1 ,per);


        this->interception_ = this->_theta[0];
        this->coef = this->_theta.st_vec(1, this->_theta.len());

        return *this;
    }


    MinVector<T> dJ_sgd(MinVector<T> theta, MinVector<T> X_b_i, T y_i) {
        return X_b_i.mul(X_b_i.dot(theta) - y_i) * 2;
        //由于这里X_b_i是一个向量，而(X_b_i.dot(theta) - y_i)是一个数，而非向量，老师原来的做法
        //是矩阵点乘，我这里就改成向量想法，达到一样的效果。
    }

    T learning_rate(T t, T t0, T t1) {
        return t0 / (t + t1);
    }

    MinVector<T> sgd(MinMatrix<T> X_b, MinMatrix<T> y, MinMatrix<T> initial_theta, T n_iters, T t0, T t1,T per) {

        auto theta = initial_theta.col_vector(0);

        Numpy_Cpp<T> np;

        auto size = X_b.size()/per;
        for (int i = 0; i < n_iters; ++i) {
            auto indexs = np.shuffle_indexes(size);
            auto X_b_i = X_b.indexFancy(indexs,X_b);
            auto y_i = y.indexFancy_vec(indexs,y);
            for(int j = 0 ; j < size ; ++j){
                auto gradient = dJ_sgd(theta, X_b_i[j], y_i[j]);
                theta = theta.sub(gradient * learning_rate(n_iters*size+j, t0, t1));
            }
        }
        return theta;
    }


    MinMatrix<T> gradient_descent(MinMatrix<T> X_b, MinMatrix<T> y, MinMatrix<T> initial_theta, T eta,
                                  T n_iters = 1e4, T epsilon = 1e-8) {
        auto theta = initial_theta;
        T cur_iter = 0;

        while (cur_iter < n_iters) {
            auto gradient = dJ(theta, X_b, y);
            auto last_theta = theta;
            theta = theta.sub_b(gradient * eta);
            if (abs(J(theta, X_b, y) - J(last_theta, X_b, y)) < epsilon) {
                break;
            }
            cur_iter += 1;
        }

        return theta;
    }

    
    //梯度下降法
    LinearRegression fit_gd(MinMatrix<T> X_train, MinMatrix<T> y_train, T eta = 0.01, T n_iters = 100) {
        assert(X_train.shape()[0] == y_train.shape()[1]);

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_train.size()),
                                               static_cast<unsigned int>(X_train.col_num() + 1));

        auto col_size = X_train.col_num();
        for (int i = 0; i < col_size; ++i) {
            X_b.col_value_Change(i + 1, X_train.col_vector(i));
        }

        auto initia = np.zero(X_b.shape()[1]);

        auto initial_theta = Matrix(1, initia).T();


        this->_theta = gradient_descent(X_b, y_train.T(), initial_theta, eta, n_iters).col_vector(0);

        this->interception_ = this->_theta[0];

        this->coef = this->_theta.st_vec(1, this->_theta.len());

        return *this;
    }


    MinVector<T> predict(MinMatrix<T> X_predict) {
        assert(X_predict.shape()[1] == this->coef.len());

        MinMatrix<T> X_b = MinMatrix<T>().ones(static_cast<unsigned int>(X_predict.size()),
                                               static_cast<unsigned int>(X_predict.col_num() + 1));
        auto col_size = X_predict.col_num();
        for (int i = 0; i < col_size; ++i) {
            X_b.col_value_Change(i + 1, X_predict.col_vector(i));
        }

        MinMatrix<T> t(this->_theta.len(), this->_theta);

        return X_b.dot(t.T()).col_vector(0);

    }

    T score(MinMatrix<T> x_test, MinVector<T> y_test) {
        auto y_predict = this->predict(x_test);
        return r2_score(y_predict, y_test);

    }

    MinVector<T> arg_coef() {
        auto arg_num = this->coef;
        return arg_num.argsorted();
    }

    MinVector<string> arg_feature_name() {
        dataSet dSet;
        auto arg_name = this->coef;
        auto str = MinVector<string>(dSet.load_boston_feature_name());
        return str.indexFancy(arg_name.argsorted(), str);
    }
};


//这里是多元线性回归的一般方法
void mul_lin_reg_score() {
    dataSet dSet;

    auto x = Matrix(dSet.load_boston_data());
    auto y = minVector(dSet.load_boston_target());

    x = x(y, 50);
    y = y(y, 50);

    auto Mix = train_test_split(x, y);
    auto X_train = get<0>(Mix);
    auto X_test = get<1>(Mix);
    auto Y_train = get<2>(Mix);
    auto Y_test = get<3>(Mix);

    LinearRegression<double> reg;
    auto sta = StandardScaler<double>();
    auto sta_fit = sta.fit(X_train);
    auto sta_X_train_sta = sta_fit.tranform(X_train);
    auto sta_X_test = sta_fit.tranform(X_test);
    auto reg_gd = reg.fit_normal(sta_X_train_sta, Y_train);
    cout << reg_gd.score(sta_X_test, Y_test);

}


//随机梯度下降
double Gradient_Des_Opt(int i,int j){
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

    auto Y_train_Mat = Matrix(1,Y_train);


    LinearRegression<double> reg;
    auto sta = StandardScaler<double>();
    auto sta_fit = sta.fit(X_train);
    auto sta_X_train_sta = sta_fit.tranform(X_train);
    auto sta_X_test = sta_fit.tranform(X_test);

    auto reg_sgd = reg.fit_sgd(sta_X_train_sta,Y_train_Mat,i,j);

    auto ne = reg_sgd.score(sta_X_test,Y_test);

    return ne;
}

//运行多次随机梯度下降，获取最优秀的R方
void best_Gradint_(int start,int size){
    auto big = 0.0;
    for(int i = start ; i < size-1;++i){
        auto a = Gradient_Des_Opt(i,i);
        auto b = Gradient_Des_Opt(i+1,i);
        auto big_ = max(a,b);
        if(big_>big) big = big_;
    }
    cout<<big<<endl;
}


#endif //ML_CPP_SIM_LIN_REG_H
