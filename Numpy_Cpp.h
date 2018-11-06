//
// Created by john on 2018-10-11.
//

#ifndef NEW_ML_CPP_NUMPY_CPP_H
#define NEW_ML_CPP_NUMPY_CPP_H

#include <iostream>
#include <ctime>
#include <random>
#include "../LinReg/LinearSystem.h"

using namespace std;


template <typename T>
class Numpy_Cpp{
private:
    vector<vector<T>> vec;
    vector<T> vec2;
    MinVector<T> minVector;
    MinMatrix<T> matrix;

public:
    Numpy_Cpp(){

    }
    Numpy_Cpp(MinMatrix<T> &vec,MinVector<T> &vec2){
        matrix = vec;
        minVector = vec2;
    }

    explicit Numpy_Cpp(MinVector<T> &_vec):minVector(_vec){

    }

    explicit Numpy_Cpp(MinMatrix<T> vec):matrix(vec){

    }

    MinVector<T> argSort(MinVector<T> &x,vector<T> &num_index){
        return x.argsorted(num_index);
    }

    MinVector<T> _Match_Num(MinVector<T> &nearest,MinVector<T> &Y_train){

        auto size = nearest._vector().size();
        vector<T> vec(size);
        for(int i = 0 ; i < size; ++i){
            vec[i] = Y_train[nearest[i]];
        }
        return MinVector<T>(vec);
    }

    MinVector<T> shuffle_indexes(const unsigned int &num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> r(num);
        for(int i = 0; i < num; ++i){
            r[i] = rand()%num;

        }
        return MinVector<T>(r);
    }

    MinVector<T> test_indexes(MinVector<T> &shuffle,const int start = 0, const int _end = 0){
        vector<T> temp;
        for(int i = start; i < _end; ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    MinVector<T> train_indexes(MinVector<T> &shuffle,const int start = 0, const int _end = 0){
        vector<T> temp;
        for(int i = start; i < (_end); ++i){
            temp.push_back(shuffle[i]);
        }
        return MinVector<T>(temp);
    }

    T sum(MinVector<T> &vec) {
        T ret = 0.0;
        auto size = vec._size();
        for(int i = 0; i < size; ++i){
            ret += vec[i];
        }

        return ret;
    }

    T sum(MinVector<T> &&vec) {
        T ret = 0.0;
        //auto size = vec._size();
        //for(int i = 0; i < size; ++i){
        //    ret += vec[i];
        //}
        for(auto &i : vec._vector()){
            ret+=i;
        }

        return ret;
    }

    T mean(MinVector<T> &vec){
        return sum(vec)/vec._size();
    }

    T mean(MinVector<T> &&vec){
        return sum(vec)/vec._size();
    }

    //矩阵均值
    MinVector<T> mean(MinMatrix<T> matrix,int axis=0){
        if(axis == 0){
            return mean_mat_0(matrix);
        } else {
            return mean_mat_1(matrix);
        }
    }

private:
    MinVector<T> mean_mat_0(MinMatrix<T> matrix){
        auto const size = matrix._Matrix()[0].size();
        vector<T> ret(size);
        for( int i = 0; i < size; ++i){
            ret[i] = mean(matrix.col_vector(i));
        }
        return MinVector<T>(ret);
    }
    MinVector<T> mean_mat_1(MinMatrix<T> matrix){

        auto const size = matrix.size();
        vector<T> ret(size);
        for( int i = 0; i < size; ++i){
            ret[i] = mean(matrix.row_vector(i));
        }
        return MinVector<T>(ret);
    }
public:

    T var(MinVector<T> &vec)  {
        auto x = mean(vec);
        auto ret = 0.0;
        auto size = vec._size();
        for( int i = 0; i < size;++i){
            ret+=pow(vec.getitem(i)-x,2);
        }
        return ret/(size-1);
    }

    T std(MinVector<T> &vec){

        return sqrt(var(vec));
    }

    MinVector<T> line_space_rand(T &&st,T &&en,T size){
       std::default_random_engine rd(static_cast<unsigned int>(time(nullptr)));
        std::mt19937 gen{rd()};
       std::uniform_real_distribution<double > dist(st,en);
       vector<T> vec(size);
       for( int i = 0; i < size;++i){
           vec[i] = std::round(dist(gen));
       }
       return MinVector<T>(vec);

    }

    MinVector<T> random_engine_normal(T &&cent,T &&sc, T&&size){
        std::default_random_engine rd(static_cast<unsigned int>(time(nullptr)));
        //std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<> d{cent,sc};
        vector<T> vec(size);
        for( int i = 0; i < size;++i){
            vec[i] = std::round(d(gen));
        }
        return MinVector<T>(vec);
    }

    MinVector<T> random_engine(T &&st,T &&en,T size){
        std::default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
        std::uniform_real_distribution<T> dis(st, en);
        vector<T> vec(size);
        for( int i = 0; i < size;++i){
            vec[i] = dis(engine);
        }
        return MinVector<T>(vec);
    }



    MinVector<T> random(T &num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> vec(num);
        for(int i = 0;i<num;++i){
            vec[i] = (rand()%100/(double)101);
        }

        return MinVector<T>(vec);
    }

    MinVector<T> random(T &&num){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> vec(num);
        for(int i = 0;i<num;++i){
            vec[i] = (rand()%100/(double)101);
        }

        return MinVector<T>(vec);
    }

    MinVector<T> randint(const unsigned &size){
        srand(static_cast<unsigned int>(time(NULL)));
        vector<T> vec;
        for(int i = 0;i<size;++i){
            vec.push_back(rand()%size);
        }

        return MinVector<T>(vec);
    }


    MinMatrix<T> hstack(MinMatrix<T> &&a,MinMatrix<T> &b ,T &&axis = 0){
        MinMatrix<T> h_stack;
        for( int i = 0; i < a.col_num();++i){
            h_stack.addVector(a.col_vector(i));
        }

        for( int i = 0; i < b.col_num();++i){
            h_stack.addVector(b.col_vector(i));
        }

        if( axis == 0)
            return h_stack._T();
        else
            return h_stack;
    }

    MinMatrix<T> hstack(MinMatrix<T> &a,MinMatrix<T> &b ,T &&axis = 0){
        MinMatrix<T> h_stack;
        for( int i = 0; i < a.col_num();++i){
            h_stack.addVector(a.col_vector(i));
        }

        for( int i = 0; i < b.col_num();++i){
            h_stack.addVector(b.col_vector(i));
        }

        if( axis == 0)
            return h_stack._T();
        else
            return h_stack;
    }

    MinMatrix<T> hstack(MinVector<T> &&a, T && size,T &&axis = 0){
        //axis = 0, 矩阵每一行等于a;axis=1，矩阵每一列等于a；
        MinMatrix<T> h_stack;
        for( int i = 0 ; i < size; ++i){
            h_stack.addVector(a);
        }
        if( axis == 0)
            return h_stack._T();
        else
            return h_stack;
    }

    MinMatrix<T> vec_to_mat(MinVector<T> &vec){
        MinMatrix<T> matrix1;
        matrix1.addVector(vec);
        return matrix1._T();
    }

    MinMatrix<T> empty(unsigned int &r, unsigned int &c){
        return MinMatrix<T>(r,c);
    }

    MinMatrix<T> empty(MinVector<T> &&shape){
        auto r = shape[0];
        auto c = shape[1];
        return MinMatrix<T>(r,c);
    }

    MinVector<T> empty(unsigned int size){
        return MinVector<T>(size);
    }

    Numpy_Cpp arange(T &&a,T &&b){
        auto ret = MinVector<T>();
        for( int i = int(a); i < b; ++i){
            ret._push_back(i);
        }
        return Numpy_Cpp(ret);
    }

    Numpy_Cpp reshape( T &&a, T&& b){
        if(a < 0){
            a = this->minVector._size() - a;
        }
        auto size = this->minVector._size()/b;

        vector<vector<T>> ret_mat(size);

        for(int i = 0 ; i < size; ++i){
            for( int j = 0; j < b; ++j ){
                ret_mat[i].push_back(this->minVector[j] + i * b);
            }
        }

        return Numpy_Cpp(MinMatrix<T>(ret_mat));
    }

    void print_str(Numpy_Cpp np){
        if(np.minVector._size() == 0){
            cout<<np.matrix<<endl;
        }else{
            np.minVector.__str__();
        }
    }

    MinMatrix<T> Matrix(){
        return this->matrix;
    }

    MinVector<T> Vector(){
        return this->minVector;
    }




};

template <typename T>
void print(Numpy_Cpp<T> np){
    Numpy_Cpp<T> print_;
    print_.print_str(np);
}




#endif //NEW_ML_CPP_NUMPY_CPP_H
