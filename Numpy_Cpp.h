#ifndef ML_CPP_NUMPY_CPP_H
#define ML_CPP_NUMPY_CPP_H

#include <istream>
#include <cmath>
#include <vector>
#include <ctime>
#include <tuple>
#include "MinVector.h"
#include "MinMatrix.h"
#include "SortList.h"
#include "MinStatistics.h"
#include "LinearSystem.h"
#include "Heap/RBTree.h"

using namespace std;

template<typename A>
class Numpy_Cpp {
private:
    vector<vector<A>> vec;
    vector<A> vec2;
    MinSta<A> *minSta;
    MinVector<A> *minVector;
    MinMatrix<A> *minMatrix;
    LinearSystem<A> *linearSystem;

public:
    Numpy_Cpp() {
        minVector = new MinVector<A>();
        minMatrix = new MinMatrix<A>();
        minSta = new MinSta<A>();

    }

    explicit Numpy_Cpp(vector<vector<A>> vec) : vec(vec) {
        minMatrix = new MinMatrix<A>(vec);
        minSta = new MinSta<A>();
    }

    explicit Numpy_Cpp(vector<A> vec2) : vec2(vec2) {
        minVector = new MinVector<A>(vec2);
        minSta = new MinSta<A>();

    }

    Numpy_Cpp(vector<vector<A>> vec,vector<A> vec2):vec(vec),vec2(vec2){
       // minMatrix = new MinMatrix<A>(vec);
       // minVector = new MinVector<A>(vec2);
       // minSta = new MinSta<A>();

    }

    Numpy_Cpp(MinMatrix<A> *vec,MinVector<A> *vec2){
        minMatrix = vec;
        minVector = vec2;
       // minSta = new MinSta<A>();
    }

    Numpy_Cpp(MinMatrix<A> &vec,MinVector<A> &vec2){
        minMatrix = &vec;
        minVector = &vec2;
       // minSta = new MinSta<A>();
    }

   //Numpy_Cpp(MinMatrix<A> *vec,MinVector<A> *vec2,LinearSystem<A> *linearSystem1){
   //    minMatrix = vec;
   //    minVector = vec2;
   //    linearSystem = linearSystem1;
   //   // minSta = new MinSta<A>();

   //}

   //Numpy_Cpp(MinMatrix<A> vec,MinVector<A> vec2,LinearSystem<A> *linearSystem1){
   //    minMatrix = &vec;
   //    minVector = &vec2;
   //    linearSystem = linearSystem1;
   //    //minSta = new MinSta<A>();

   //}




    ~Numpy_Cpp() {
        // delete(initTemp);
        if(!minMatrix)
            delete minMatrix;
            minMatrix = nullptr;
        if(!minVector)
            delete minVector;
            minVector = nullptr;
        if(!minSta)
            delete minSta;
            minVector = nullptr;
        if(!linearSystem)
            delete[] linearSystem;
            linearSystem = nullptr;
    }


    MinVector<A> zero(int num) {
        return minVector->zero(num);
    }

    MinMatrix<A> zero(int r, int c) {
        return minMatrix->zero(static_cast<unsigned int>(r), static_cast<unsigned int>(c));
    }

    MinMatrix<A> ones(int r, int c) {
        vector<vector<A>> newVec(r);
        for (int i = 0; i < r; i++) {
            newVec[i] = vector<double>(c);
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                newVec[i][j] = 0.0;
            }
        }
        return MinMatrix<A>(newVec);
    }

    MinMatrix<A> full(int r, int c, A num) {
        vector<vector<A>> newVec(r);
        for (int i = 0; i < r; i++) {
            newVec[i] = vector<double>(c);
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                newVec[i][j] = num;
            }
        }
        return MinMatrix<A>(newVec);
    }


    MinVector<A> array(int num) {

        return minVector->array(num);
    };

    MinVector<A> array(vector<A> vec) {

        return MinVector<A>(vec);
    }

    MinVector<A> arange(int start, int last, A step = 0) {

        return minVector->arange(start, last, step);
    }

    MinVector<A> linspace(A start, A last, A num, bool endpoint = true) {
        return minSta->linspace(start, last, num, endpoint);
    }

    template<typename T>
    MinVector<A> concatone(T vec) {
        return minVector->concatone(vec);
    }


    MinMatrix<A> concatMatrix(MinMatrix<A> a, MinMatrix<A> b, int axis = 0) {
        assert(a.size() == b.size());
        vector<vector<A>> tempVec;
        if (axis == 0) {
            tempVec = conAxita(a, b);
        } else {
            tempVec = conAxitb(a, b);
        }

        return MinMatrix<A>(tempVec);
    }

    MinMatrix<A> concatMatrix(MinMatrix<A> a, int axis = 0) {
        assert(a.size() == this->vec.size());
        vector<vector<A>> tempVec;
        auto b = MinMatrix<A>(this->vec);
        if (axis == 0) {
            tempVec = conAxita(a, b);
        } else {
            tempVec = conAxitb(a, b);
        }

        return MinMatrix<A>(tempVec);
    }

private:
    vector<vector<A>> conAxita(MinMatrix<A> a, MinMatrix<A> b) {
        vector<vector<A>> tempVec(static_cast<unsigned int>(a.size() * 2));
        for (int i = 0; i < a.size() * 2; ++i) {
            tempVec[i] = vector<double>(static_cast<unsigned int>(a.col_num()));
        }

        for (int i = 0; i < a.size() * 2; ++i) {
            for (int j = 0; j < a.col_num(); j++) {
                if (i < a.size()) {
                    tempVec[i][j] = a.row_vector(i)[j];
                } else {
                    tempVec[i][j] = b.row_vector(i - b.size())[j];
                }
            }
        }
        return tempVec;
    }

    vector<vector<A>> conAxitb(MinMatrix<A> a, MinMatrix<A> b) {
        vector<vector<A>> tempVec(static_cast<unsigned int>(a.size()));
        for (int i = 0; i < a.size(); ++i) {
            tempVec[i] = vector<double>(static_cast<unsigned int>(a.col_num() * 2));
        }

        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a.col_num() * 2; j++) {
                if (j < a.col_num()) {
                    tempVec[i][j] = a.row_vector(i)[j];
                } else {
                    tempVec[i][j] = b.row_vector(i)[j - a.col_num()];
                }
            }
        }
        return tempVec;
    }


public:

    MinVector<A> row_vector(int index) {
        return minMatrix->row_vector(index);
    }

    MinVector<A> col_vector(int index) {
        return minMatrix->col_vector(index);

    }

    template<typename T>
    MinMatrix<A> makeMatrix(T vec, vector<A> pos) {
        vector<A> vecTemp;
        for (int i = 1; i < pos[0]; ++i) {
            vecTemp.push_back(pos[1] * i);
        }

        return split(vec, vecTemp);
    }

    MinMatrix<A> split(MinVector<A> x, vector<A> vec) {
        vector<A> vecTemp;
        vecTemp.push_back(0);
        for (int i = 0; i < vec.size(); ++i) {
            vecTemp.push_back(vec[i]);
        }
        vecTemp.push_back(x.len());
        //以上是把分割数组的参数和0和size信息放入一个新的数组中，用于过后切割数组之用


        vector<vector<A>> vecT(static_cast<unsigned int>(vecTemp.size() - 1));
        for (int i = 0; i < vecT.size() - 1; ++i) {
            vecT[i] = vector<A>();
        }
        for (int i = 0; i < vecTemp.size() - 1; ++i) {
            for (int j = vecTemp[i]; j < vecTemp[i + 1]; ++j) {
                vecT[i].push_back(x[j]);
            }
        }
        return MinMatrix<A>(vecT);
    }

    MinMatrix<A> split(vector<A> x, vector<A> vec) {
        vector<A> vecTemp;
        vecTemp.push_back(0);
        for (int i = 0; i < vec.size(); ++i) {
            vecTemp.push_back(vec[i]);
        }
        vecTemp.push_back(x.size());
        //以上是把分割数组的参数和0和size信息放入一个新的数组中，用于过后切割数组之用


        vector<vector<A>> vecT(static_cast<unsigned int>(vecTemp.size() - 1));
        for (int i = 0; i < vecT.size() - 1; ++i) {
            vecT[i] = vector<A>();
        }
        for (int i = 0; i < vecTemp.size() - 1; ++i) {
            for (int j = vecTemp[i]; j < vecTemp[i + 1]; ++j) {
                vecT[i].push_back(x[j]);
            }
        }
        return MinMatrix<A>(vecT);
    }


    MinMatrix<A> split(MinMatrix<A> x, vector<A> vec, int num = 1, int axis = 0) {
        MinMatrix<A> Ret;
        if (axis == 0) {
            Ret = splitA(x, vec, num);
        } else {
            Ret = splitB(x, vec, num);
        }

        return Ret;
    }

private:
    MinMatrix<A> splitA(MinMatrix<A> x, vector<A> vec, int num = 1) {
        vector<A> vecTemp;
        vecTemp.push_back(0);
        for (int i = 0; i < vec.size(); ++i) {
            vecTemp.push_back(vec[i]);
        }
        vecTemp.push_back(x.size());


        MinMatrix<A> tempA, tempB;
        for (int i = 0; i < vecTemp.size(); ++i) {
            for (int j = vecTemp[i]; j < vecTemp[i + 1]; ++j) {
                if (j < vec[0]) {
                    tempA.addMinVector(x[j]);
                } else {
                    tempB.addMinVector(x[j]);
                }
            }
        }

        if (num == 1) {
            return tempA;
        } else {
            return tempB;
        }
    }

    MinMatrix<A> splitB(MinMatrix<A> x, vector<A> vec, int num = 1) {
        vector<A> vecTemp;
        vecTemp.push_back(0);
        for (int i = 0; i < vec.size(); ++i) {
            vecTemp.push_back(vec[i]);
        }
        vecTemp.push_back(x.size());


        MinMatrix<A> tempA, tempB;
        for (int i = 0; i < vecTemp.size(); ++i) {
            for (int j = vecTemp[i]; j < vecTemp[i + 1]; ++j) {
                if (j < vec[0]) {
                    tempA.addMinVector(x.col_vector(j));
                } else {
                    tempB.addMinVector(x.col_vector(j));
                }
            }
        }

        if (num == 1) {
            return tempA;
        } else {
            return tempB;
        }
    }

public:
    MinMatrix<A> tile(MinVector<A> v, vector<A> vec) {
        return minMatrix->tile(v, vec);
    }

    A sum(MinVector<A> vec) {
        return minSta->sum(vec);

    }



    // A sum(MinMatrix<A> matrix){
    //     return minSta->sum(matrix);
    // }

    MinVector<A> sum(MinMatrix<A> matrix, int axis = 0) {
        return minSta->sum(matrix, axis);
    }


public:

    template<typename T>
    A min(T vec) {
        return minSta->min(vec);
    }

    //A min(MinVector<A> vec){
    //    return minSta->min(vec);
    //}

    template<typename T>
    A max(T vec) {
        return minSta->max(vec);
    }

    //A max(MinVector<A> vec){
    //    return minSta->max(vec);
    //}

    A mean(MinVector<A> vec) {
        return minSta->mean(vec);
    }

    A median(MinVector<A> vec) {
        return minSta->median(vec);
    }

    double var(MinVector<A> vec) {
        return minSta->var(vec);
    }

    double std(MinVector<A> vec) {
        return minSta->std(vec);
    }

    int argmin(MinVector<A> vec) {
        return minSta->argmin(vec);
    }

    int argmax(MinVector<A> vec) {
        return minSta->argmax(vec);
    }

    template<typename T>
    MinVector<A> minSort(T vec) {
        return minSta->minSort(vec);
    }


    MinMatrix<A> minSort(MinMatrix<A> vec, int axis = 0) {
        return minSta->minSort(vec, axis);
    }

    MinVector<A> argSort(MinVector<A> x){
        return minSta->argsort(x);
    }

    MinVector<tuple<A,A>> argSort(MinVector<tuple<A,A>> x){
        return minSta->argsort(x);
    }

    MinVector<A> MatchNum(MinVector<A> nearest,MinVector<A> Y_TRAIN){
        vector<A> vec;
        auto size = nearest.len();
        for(int i = 0 ; i < size; ++i){
            vec.push_back(Y_TRAIN[nearest[i]]);
        }
        return MinVector<A>(vec);
    }



    MinVector<A> sort(MinVector<A> x){
        vector<A> temp;
        for(int i = 0; i < x.len();++i){
            temp.push_back(x[i]);
        }

        for(int i = 0 ; i < 10;++i){
            auto e = temp[i];
            int j;
            for(j = i;j > 0 && e < temp[j-1];j--){
                temp[j] = temp[j-1];
            }
            temp[j] = e;
        }

        return MinVector<A>(temp);
    }


    template<typename T>
    MinVector<A> partition(T x, A num) {
        return minSta->partition(x, num);
    }

    template<typename T>
    MinVector<A> argpartition(T x, A num) {
        return minSta->argpartition(x, num);
    }

    MinVector<A> Index(vector<A> vec) {
        return minVector->indexFancy(vec);
    }

    MinVector<A> Index(MinVector<A> vec) {
        return minVector->indexFancy(vec);
    }

    template<typename T>
    MinVector<A> operator()(vector<A> vec) {
        return minVector->indexFancy(vec);
    }

    MinVector<A> operator()(MinVector<A> vec) {
        return minVector->indexFancy(vec);
    }


    template<typename T>
    MinMatrix<A> index(T vec) {
        return minMatrix->indexFancy(minVector, vec);
    }

    //MinMatrix<A> index(MinMatrix<A> vec){
    //    return minMatrix->indexFancy(minVector,vec);
    //}

    template<typename T>
    MinMatrix<A> operator()(T vec) {
        return minMatrix->indexFancy(minVector, vec);
    }

    //MinMatrix<A> operator()(MinMatrix<A> vec){
    //    return minMatrix->indexFancy(minVector,vec);
    //}

    //线性代数的高斯消元

    bool Gj_elem(){
        linearSystem->Gj_elem();
    }

    void fancy_print(){
        linearSystem->fancy_print();
    }

    MinVector<A> randint(A start,A end,int size){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<A> vec;
        for(int i = 0;i<size;++i){
            vec.push_back(rand()%(end-start+1)+start);
        }

        return MinVector<A>(vec);
    }


    MinVector<A> shuffle_indexes(int num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<A> r;
        for(int i = 0; i < num; ++i){
            r.push_back(rand()%num);
            //sleep(1);
        }
        return MinVector<A>(r);
    }

    MinVector<A> test_indexes(MinVector<A> shuffle,int start = 0, int _end = 0){
        vector<A> temp;
        for(int i = start; i < _end; ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<A>(temp);
    }

    MinVector<A> train_indexes(MinVector<A> shuffle,int start = 0, int _end = 0){
        vector<A> temp;
        for(int i = start; i < (_end); ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<A>(temp);
    }

};
#endif //ML_CPP_NUMPY_CPP_H
