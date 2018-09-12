
#ifndef ML_CPP_MINSTATISTICS_H
#define ML_CPP_MINSTATISTICS_H

#include <iostream>
#include <cmath>
#include <vector>
#include "MinVector.h"
#include "MinMatrix.h"
#include "SortList.h"
#include "RBTree.h"

using namespace std;

template<typename A>
class MinSta {
private:
    Sort<A> sort;
    RBtree<int, A> rBtree;

public:
    MinSta() {

    }

public:
    MinVector<A> sum(MinMatrix<A> matrix, int axis = 0) {
        MinVector<A> ret;
        if (axis == 0) {
            ret = sumAsix0(matrix);
        } else {
            ret = sumAsix1(matrix);
        }

        return ret;
    }

private:
    MinVector<A> sumAsix0(MinMatrix<A> matrix) {
        A ret = 0;
        vector<A> vector1;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.row_num(); ++j) {
                ret = ret + matrix[i][j];
            }
            vector1.push_back(ret);
            ret = 0;
        }
        return MinVector<A>(vector1);
    }

    MinVector<A> sumAsix1(MinMatrix<A> matrix) {
        A ret = 0;
        vector<A> vector1;
        for (int i = 0; i < matrix.col_num(); ++i) {
            for (int j = 0; j < matrix.col_vector(i).len(); ++j) {
                ret = ret + matrix[j][i];
            }
            vector1.push_back(ret);
            ret = 0;
        }
        return MinVector<A>(vector1);
    }

public:
    A sum(MinMatrix<A> matrix) {
        A ret = 0;
        A ret2 = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.row_num(); ++j) {
                ret = ret + matrix[i][j];
            }
        }
        return ret;
    }

    A sum(MinVector<A> vec) {
        A ret = 0;
        auto size = vec.len();
        for(int i = 0;i < size;++i){
            ret += vec[i];
        }
        return ret;

    }

    A min(MinVector<A> vec) {
        auto v = sort.insertionSort(vec, vec.len());
        return v[0];
    }

    A min(vector<A> vec) {
        auto v = sort.insertionSort(vec, vec.size());
        return v[0];
    }

    MinVector<A> minSort(MinVector<A> vec) {
        //未来加上判断vec大小，选用更高校的排序方法
        auto v = sort.insertionSort(vec, vec.len());
        return v;
    }

    MinVector<A> minSort(vector<A> vec) {
        //未来加上判断vec大小，选用更高校的排序方法
        auto v = sort.insertionSort(vec, vec.size());
        return v;
    }

    MinMatrix<A> minSort(MinMatrix<A> vec, int axis = 0) {
        //未来加上判断vec大小，选用更高校的排序方法
        MinMatrix<A> ret;
        MinMatrix<A> minMatrix;
        MinMatrix<A> minMatrix2;
        if (axis == 0) {
            for (int i = 0; i < vec.size(); ++i) {
                minMatrix.addMinVector(vec.row_vector(i).sorted());
            }
            ret = minMatrix;
        } else {
            for (int i = 0; i < vec.col_num(); ++i) {
                minMatrix2.addMinVector(vec.col_vector(i).sorted());
            }
            ret = minMatrix2;
        }

        return ret;
    }

    A max(vector<A> vec) {
        auto v = sort.insertionSort(vec, vec.size());
        return v[vec.size() - 1];
    }

    A max(MinVector<A> vec) {
        auto v = sort.insertionSort(vec, vec.len());
        return v[vec.len() - 1];
    }

    A median(MinVector<A> vec) {
        auto v = sort.insertionSort(vec, vec.len());
        if (vec.len() % 2 == 0) {
            return (v[vec.len() / 2] + vec[vec.len() / 2 + 1]) / 2;
        } else {
            return v[vec.len() / 2];
        }
    }

    A mean(MinVector<A> vec) {
        return sum(vec) / vec.len();
    }

    double var(MinVector<A> vec) {
        double x = mean(vec);
        double ret = 0;
        auto size = vec.len();
        for (int i = 0; i < size; ++i) {
            ret = ret + pow(vec.getitem(i) - x,2);
        }

        return ret / (size-1);
    }

    double std(MinVector<A> vec) {
        return sqrt(var(vec));
    }

    int argmin(MinVector<A> vec) {
        return argsort(vec)[vec.len()-1];
    }

    int argmax(MinVector<A> vec) {
        return argsort(vec)[0];
    }

    MinVector<A> argsort(MinVector<A> vec){
        return vec.argsorted();
    }



    MinVector<A> linspace(A start, A last, A num, bool endpoint = true) {
        A a;
        vector<A> vec2;

        if (endpoint) {
            a = (last - start) / (num - 1);
        } else {
            a = (last - start) / (num);
        }
        for (int i = 0; i < num; i++) {
            vec2.push_back(start + (a * i));
        }
        return MinVector<A>(vec2);
    }

    MinVector<A> partition(MinVector<A> x, A num) {
        for (int i = 0; i < x.len(); ++i) {
            rBtree.add(i, x[i]);
        }
        vector<A> vector1;

        for (int i = 0; i < rBtree.getSize(); ++i) {
            auto pcut = rBtree.get(i);
            if (pcut <= num) {
                vector1.push_back(pcut);
            }
        }
        for (int i = 0; i < rBtree.getSize(); ++i) {
            auto pcut = rBtree.get(i);
            if (pcut > num) {
                vector1.push_back(pcut);
            }
        }
        return MinVector<A>(vector1);
    }

    MinVector<A> partition(vector<A> x, A num) {
        for (int i = 0; i < x.size(); ++i) {
            rBtree.add(i, x[i]);
        }
        vector<A> vector1;

        for (int i = 0; i < rBtree.getSize(); ++i) {
            auto pcut = rBtree.get(i);
            if (pcut <= num) {
                vector1.push_back(pcut);
            }
        }


        for (int i = 0; i < rBtree.getSize(); ++i) {
            auto pcut = rBtree.get(i);
            if (pcut > num) {
                vector1.push_back(pcut);
            }
        }
        return MinVector<A>(vector1);
    }

    MinVector<A> argpartition(MinVector<A> x, A num) {
        vector<A> vector1;
        for (int i = 0; i < x.len(); ++i) {
            for (int j = 0; j < x.len(); ++j) {
                if (partition(x, num)[i] == x[j]) {
                    vector1.push_back(j);
                }
            }
        }

        return MinVector<A>(vector1);
    }

    MinVector<A> argpartition(vector<A> x, A num) {
        vector<A> vector1;
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                if (partition(x, num)[i] == x[j]) {
                    vector1.push_back(j);
                }
            }
        }
        return MinVector<A>(vector1);
    }

    //数据归一化Normalization
    MinVector<A> NormValue(MinVector<A> v){
        auto size = v.len();
        auto _max = max(v);
        auto _min = min(v);
        auto _max_min = _max-_min;

        vector<A> vector1(static_cast<unsigned int>(size));

        for(int i = 0;i < size ; ++i){
            vector1[i] = v[i]-_min;
        }

        return MinVector<A>(vector1)/_max_min;
    }

   MinVector<A> StandValue(MinVector<A> v){
        auto size = v.len();
        auto _mean = mean(v);
        auto _std = std(v);

       vector<A> vector1(static_cast<unsigned int>(size));

        for(int i = 0; i < size; ++i){
            vector1[i] = v[i] - _mean;
        }

        return MinVector<A>(vector1)/_std;
    }

};
#endif //ML_CPP_MINSTATISTICS_H
