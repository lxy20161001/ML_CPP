#include <iostream>
#include <vector>
#include <windows.h>
#include "ML_Cpp/LinReg/LinearSystem.h"
#include "ML_Cpp/dataSet/dataSet.h"
#include "ML_Cpp/data_split/data_split.h"
#include "ML_Cpp/StandardSDcaler.h"
#include "ML_Cpp/SimpleLinearRegression/Simp_Linear_Reg.h"


int main() {

    double time=0;
    double counts=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//开始计时


   auto data_Set=dataSet();
   auto X=MinMatrix<double>(data_Set.load_boston_data());
   auto y=MinVector<double>(data_Set.load_boston_target());
   X = X(y,50);
   y = y(y,50);


   auto new_Data=train_test_split(X, y);
   auto X_tr=get<0>(new_Data);
   auto X_test=get<1>(new_Data);
   auto y_tr=get<2>(new_Data);
   auto y_test=get<3>(new_Data);
   auto reg = LinearRegression<double>();
   auto _fit = reg.fit_normal(X_tr,y_tr);
   cout<<_fit.coef<<endl;
   cout<<_fit.interception_<<endl;
   cout<<_fit.score(X_test,y_test)<<endl;


    QueryPerformanceCounter(&nEndTime);//停止计时
    time=(double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart;//计算程序执行时间单位为s
    cout << "time:" << time * 1000 << "ms" << endl;


    return 0;
}

