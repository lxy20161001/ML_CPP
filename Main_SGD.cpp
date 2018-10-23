#include <iostream>
#include <utility>
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
      auto data=data_Set.load_boston_data();
      auto target=data_Set.load_boston_target();
      auto X=MinMatrix<double>(data);
      auto y=MinVector<double>(target);
      X=X(y, 50);
      y=y(y, 50);
      auto new_Data=train_test_split(X, y);
      auto X_tr=get<0>(new_Data);
      auto X_test=get<1>(new_Data);
      auto y_tr=get<2>(new_Data);
      auto y_test=get<3>(new_Data);

      auto std_Sca=StandardScaler<double>();
      auto fit_std=std_Sca.fit(X_tr);
      auto X_tr_std=fit_std.tranform(X_tr)._T();//先转至
      auto x_test_std=fit_std.tranform(X_test)._T();

      auto leg=LinearRegression<double>();
      cout << X_tr_std.shape() << endl;
      cout << y_tr._size() << endl;
      auto fit_sgd_=leg.fit_sgd(X_tr_std, y_tr,100);


      auto gd_score=fit_sgd_.score(x_test_std, y_test);

      if(gd_score>0.75){
          cout << gd_score << endl;
          cout << fit_sgd_.coef<<endl;
      }
      
    QueryPerformanceCounter(&nEndTime);//停止计时
    time=(double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart;//计算程序执行时间单位为s
    cout << "time:" << time * 1000 << "ms" << endl;


    return 0;
