
#ifndef ML_CPP_SORTLIST_H
#define ML_CPP_SORTLIST_H

#include <iostream>
#include <vector>
#include "MinVector.h"

using namespace std;

template<typename T>
class Sort {
    vector<T> vector1;

public:
    Sort() {
    }


    vector<T> insertionSort(vector<T> vec, int n) {
        for (int i = 0; i < n; ++i) {
            T e = vec[i];
            int j;
            for (j = i; j > 0 && e < vec[j - 1]; j--) {
                vec[j] = vec[j - 1];
            }
            vec[j] = e;
        }
        return vec;
    }



    MinVector<T> insertionSort(MinVector<T> vec, int n) {

        vector<T> vec1;
        for (int i = 0; i < n; ++i) {
            vec1.push_back(vec[i]);
        }

        for (int i = 0; i < n; ++i) {
            T e = vec1[i];
            int j;
            for (j = i; j > 0 && e < vec1[j - 1]; j--) {
                vec1[j] = vec1[j - 1];
            }
            vec1[j] = e;
        }
        return MinVector<T>(vec1);
    }




};


#endif //ML_CPP_SORTLIST_H
