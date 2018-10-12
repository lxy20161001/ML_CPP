#include <iostream>
#include <vector>
#include <windows.h>
#include "LinearSystem.h"
#include "dataSet.h"
#include "data_split.h"
#include "StandardSDcaler.h"


int main() {

    double time=0;
    double counts=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//开始计时



        auto data_Set=dataSet();
        auto X=MinMatrix<double>(data_Set.load_digits_data());
        auto y=MinVector<double>(data_Set.load_digits_target());

        auto new_Data=train_test_split(X, y);

        auto X_tr=get<0>(new_Data);
        auto X_test=get<1>(new_Data);
        auto y_tr=get<2>(new_Data);
        auto y_test=get<3>(new_Data);

        //数据归一化
        //auto std_fit = StandardScaler<double>();
        //auto fit_ = std_fit.fit(X_tr);
        //auto std_x_tr = fit_.tranform(X_tr);
        //auto std_x_test = fit_.tranform(X_test);
    
        auto knn_test=Knn_Ang<double>(3);
        auto fit=knn_test.fit(X_tr, y_tr);

        auto res_=fit.sum_Sorces(X_test, y_test);
        cout<<res_<<endl;



    QueryPerformanceCounter(&nEndTime);//停止计时
    time=(double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart;//计算程序执行时间单位为s
    cout << "time:" << time * 1000 << "ms" << endl;


    return 0;
}
