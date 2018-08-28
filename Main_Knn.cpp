#include <iostream>
#include <vector>
#include <cmath>
#include "RBTree.h"
#include "Numpy_Cpp.h"
#include "LinearSystem.h"

using namespace std;

int main() {
    dataSet datasets;

    auto x = MinMatrix<double>(datasets.load_iris_data());
    auto y = MinVector<double>(datasets.load_iris_target());

    ML_Ang<double > ml_ang(3);
    auto Mix = ml_ang.train_test_split(x,y,0.2);
    auto X_train = Mix[0];
    auto X_test = Mix[1];
    auto Y_train = Mix[2][0];
    auto Y_test = Mix[2][1];

    auto fit = ml_ang.fit(X_train,Y_train);

    cout<<fit<<endl;

    auto predict_y = fit.predict(X_test);

    cout<<predict_y<<endl;
    cout<<Y_test<<endl;
    
    auto t = fit.Test_Res(predict_y,Y_test);
    cout<<t<<endl;
   
    return 0;
}
