#include <iostream>
#include <vector>
#include <cmath>
#include "RBTree.h"
#include "Numpy_Cpp.h"
#include "LinearSystem.h"

using namespace std;

int main() {
    dataSet datasets;

    auto x = MinMatrix<double>(datasets.load_digits_data());
    auto y = MinVector<double>(datasets.load_digits_target());


    ML_Ang<double > ml_ang(3);
    cout<<ml_ang.Socore(x,y)<<endl;
   
    return 0;
}
