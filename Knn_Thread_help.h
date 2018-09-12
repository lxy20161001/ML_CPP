#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <future>
#include <tuple>
#include <functional>
#include <algorithm>
#include "Knn_Ang.h"


using namespace std;

template<typename T>
class Par_best_K {
    dataSet datasets;
    MinMatrix<T> x;
    MinVector<T> y;
    promise<T> &p;
    int i;
public:

    Par_best_K(int i, promise<T> &p) : i(i), p(p) {
        x = MinMatrix<double>(datasets.load_digits_data());
        y = MinVector<double>(datasets.load_digits_target());

    }

    void operator()() {

        Knn_Ang<T> knn_ang(i);
        p.set_value_at_thread_exit(knn_ang.Socore(x, y));
    }

};

template<typename T>
class thread_guard {
    std::thread &t;
public:
    explicit thread_guard(std::thread &t_) : t(t_) {

    }

    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(thread_guard const &) = delete;

    thread_guard &operator=(thread_guard const &) = delete;
};


MinVector<double > oops(int i) {

    std::promise<double> p,p1,p2,p3;
    std::future<double> f,f1,f2,f3;
    f = p.get_future();
    f1 = p1.get_future();
    f2 = p2.get_future();
    f3 = p3.get_future();
    Par_best_K<double> pa(i+0,p),pa1(i+1,p1),pa2(i+2,p2),pa3(i+3,p3);
    std::thread t(pa),t1(pa1),t2(pa2),t3(pa3);
    thread_guard<double> g(t),g1(t1),g2(t2),g3(t3);

    double get=f.get(),get1=f1.get(),get2=f2.get(),get3=f3.get();

    vector<vector<double>> temp;
    temp.push_back({get,double(i)});
    temp.push_back({get1,double(i+1)});
    temp.push_back({get2,double(i+2)});
    temp.push_back({get3,double(i+3)});

    return MinMatrix<double>(temp).sorted()[0];

}

MinVector<double> best_K(int i,int j=0, int z=0){
        MinMatrix<double> mat;
        if(j == 0) j = i+4;
        if(z == 0) z = i + j + 4;

        mat.addMinVector(oops(i));
        mat.addMinVector(oops(j));
        mat.addMinVector(oops(z));

        return mat.sorted()[0];

}



