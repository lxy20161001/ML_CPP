#include <iostream>
#include <vector>
#include <cmath>
#include "RBTree.h"
#include "Numpy_Cpp.h"
#include "LinearSystem.h"

using namespace std;

int main() {
    vector<vector<double>> raw_data_X = {{3.393533211, 2.331273381},
                                         {3.110073483, 1.781539638},
                                         {1.343808831, 3.368360954},
                                         {3.582294042, 4.679179110},
                                         {2.280362439, 2.866990263},
                                         {7.423436942, 4.696522875},
                                         {5.745051997, 3.533989803},
                                         {9.172168622, 2.511101045},
                                         {7.792783481, 3.424088941},
                                         {7.939820817, 0.791637231}};
    vector<double> raw_data_y = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

    MinMatrix<double> minMatrix(raw_data_X);
    MinVector<double> minVector(raw_data_y);

    vector<double> te = {8.093607318, 3.365731514};
    MinVector<double> x(te);

    Numpy_Cpp<double> np(minMatrix, minVector);

    vector<double> distances(static_cast<unsigned int>(minMatrix.size()));

    for (int i = 0; i < minMatrix.size(); ++i) {
        distances[i] = sqrt(np.sum((minMatrix[i] - x) ^ 2));
    }

    MinVector<double> d(distances);

    cout << d << endl;
    cout << d.sorted() << endl;
    auto nearest = np.argSort(d);
    int k = 6;

    RBtree<double, double> rBtree;
    double ret = 0.0;
    for (int i = 0; i < k; ++i) {
        ret = minVector[nearest[i]];
        if (rBtree.contains(ret)) {
            rBtree.set(ret, rBtree.get(ret) + 1);
        } else {
            rBtree.add(ret, 1);
        }
    }

    rBtree.toString();
    cout<<endl;
    MinMatrix<double> counter(rBtree.Counter());
    cout<<counter[1][0]<<endl;


    return 0;
}
