
#ifndef LINEARALGEBRA2_MINVECTOR_H
#define LINEARALGEBRA2_MINVECTOR_H

#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cmath>




using namespace std;

const double EPSILON = 1e-8;

template <typename T>
class MinVector{
private:
    vector<T> vec;

public:
    MinVector(){
        this->vec = {};
    }
    MinVector(vector<T> vector1){
        vector<T> temp;
        for(int i = 0;i < vector1.size();++i){
            temp.push_back(vector1[i]);
        }
        this->vec = temp;
    }


    ~MinVector(){

    }

public:
    vector<T> ThisVec(){
        return this->vec;
    }
    T getitem(int index){
        return this->vec[index];
    }

    int len(){
        return this->vec.size();
    }

    //输出格式
    std::string str(){
        std::string str;
        str.append("Vector(");
        for(int i = 0; i <this->vec.size();i++){
            if(i!=this->vec.size()-1){
                str.append(std::to_string(this->vec[i])+',');
            }else{
                str.append(std::to_string(this->vec[i]));
            }
        }

        str.append(")");
        return str;

    }

    //输出格式
    std::string repr_min(vector<T> vec){
        std::string str;
        str.append("(");
        for(int i = 0; i <vec.size();i++){
            if(i!=this->vec.size()-1){
                str.append(std::to_string(vec[i])+',');
            }else{
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }

    //输出格式
    std::string repr_min(){
        std::string str;
        str.append("(");
        for(int i = 0; i <this->vec.size();i++){
            if(i!=this->vec.size()-1){
                str.append(std::to_string(vec[i])+',');
            }else{
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }


    //重载<<
    friend ostream &operator<<(ostream &out,MinVector<T> vec) {

        out<<"Vector : (";
        for(int i = 0; i <vec.vec.size();i++){
            if(i!=vec.vec.size()-1){
                out<<vec.vec[i]<<',';
            }else{
                out<<vec.vec[i];
            }
        }

        out<<")";
        return out;
    }

public:
    static std::string zero_print(vector<T> vec){
        std::string str;
        str.append("(");
        for(int i = 0; i <vec.size();i++){
            if(i<vec.size()-1){
                str.append(std::to_string(vec[i])+',');
            }else{
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }

public:
    //以下是四则运算
    vector<T> add(vector<T> vec){
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]+vec[i]);
        }

        return newVec;
    }

    MinVector<T> add2(vector<T> vec){
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]+vec[i]);
        }

        return MinVector(newVec);
    }


    MinVector<T> add3(MinVector<T> minVector){
        assert(this->vec.size() == minVector.vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]+minVector.vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator+(MinVector<T>& b) {
        assert(this->vec.size() ==b.vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]+b.vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> operator+(T k) {
        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]+k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    vector<T> sub(vector<T> vec){
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]-vec[i]);
        }

        return newVec;
    }

    vector<T> sub(MinVector<T> vec){
        assert(this->vec.size() == vec.vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]-vec[i]);
        }

        return newVec;
    }

    MinVector<T> sub2(vector<T> vec){
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]-vec[i]);
        }

        return MinVector(newVec);
    }



    MinVector<T> operator-(MinVector<T>& b) {
        assert(this->vec.size() ==b.vec.size());

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]-b.vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    MinVector<T> operator-(T k) {
        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]-k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    MinVector<T> mul(T k){

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]*k);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator*(T k) {

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(this->vec[i]*k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> operator^(T k) {

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(pow(this->vec[i],k));
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> rmul(T k){

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(k*this->vec[i]);
        }

        return MinVector(newVec);
    }

    friend MinVector<T> operator*(T k,MinVector<T> r) {

        MinVector<T> rmul(r.vec);
        return k*rmul;
    }


    T dot(vector<T> vec){
        assert(this->vec.size() == vec.size());
        double ret = 0;
        for(int i =0;i < this->vec.size();i++){
            ret = ret + (vec[i]*this->vec[i]);
        }
        return ret;
    }

    T dot(MinVector<T> vec){
        assert(this->vec.size() == vec.len());
        double ret = 0;
        for(int i =0;i < this->vec.size();i++){
            ret = ret + (vec[i]*this->vec[i]);
        }
        return ret;
    }


    MinVector<T> truediv(T k){
        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back((1/k)*this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator/(T k) {

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back((1/k)*this->vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> pos(){

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(1*this->vec[i]);
        }

        return MinVector(newVec);
    }
    MinVector<T> neg(){

        vector<T> newVec;
        for(int i =0;i < this->vec.size();i++){
            newVec.push_back(-1*this->vec[i]);
        }

        return MinVector(newVec);
    }

    double norm(){
        auto ret=0;
        for(int i = 0; i < this->vec.size();i++){
            ret=ret+pow(this->vec[i],2);
        }

        return sqrt(ret);
    }

    double norm(vector<T> vec){
        double ret=0;
        for(int i = 0; i < vec.size();i++){
            ret=ret+pow(vec[i],2);
        }

        return sqrt(ret);
    }

    double norm(MinVector<T> minVector){
        double ret=0;
        for(int i = 0; i < minVector.vec.size();i++){
            ret=ret+pow(vec[i],2);
        }

        return sqrt(ret);
    }



    MinVector<T> nomalize(){
        assert(this->norm()>EPSILON);
        vector<T> newVec;
        for(int i = 0; i < this->vec.size();i++){

            newVec.push_back(1/this->norm()*this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> nomalize(vector<T> zero){
        if(this->norm(zero)<EPSILON){
            throw "Division by zero condition!";
        }
        vector<T> newVec;
        for(int i = 0; i < this->vec.size();i++){

            newVec.push_back(1/this->norm()*this->vec[i]);
        }

        return MinVector(newVec);
    }

    static vector<T> zero(int dim){

        vector<T> newVec;
        for(int i =0;i < dim;i++){
            newVec.push_back(0);
        }

        return newVec;
    }

    MinVector<T> ones( int dim){
        vector<T> newVec;
        for(int i =0;i < dim;i++){
            newVec.push_back(1);
        }

        return  MinVector(newVec);
    }

    MinVector<T> full(int dim,T num){
        vector<T> newVec;
        for(int i =0;i < dim;i++){
            newVec.push_back(num);
        }

        return  MinVector(newVec);
    }

    MinVector<T> vecsub(vector<T> vec,int fisrt,int last){
        assert(fisrt>0 && fisrt<vec.size());
        assert(last>0 && last<vec.size());
        vector<T> newVec;
        for(int i = fisrt; i < last;i++){
            newVec.push_back(vec[i]);
        }

        return  MinVector(newVec);
    }

    T operator[](int k) {
        assert(k<=vec.size() && k>=0);
        return getitem(k);
    }

public:
    MinVector<T> sorted(){
        return insertionSort();
    }


private:
    //考虑到暂时使用的参数比较少，于是使用插入算法
    MinVector<T> insertionSort() {
        vector<T> temp ;

        for(int i = 0;i<this->vec.size();++i){
            temp.push_back(this->vec[i]);
        }
        for (int i = 0; i < 10; ++i) {
            auto e = temp[i];
            int j;
            for (j = i; j > 0 && e < temp[j-1]; j--) {
                temp[j] = temp[j - 1];
            }
            temp[j] = e;
        }
        return MinVector(temp);
    }



public:
    //模拟numpy的indexFancy功能,在vec当中找到相应位置的元素的快捷方法
   // MinVector<T> indexFancy(vector<T> vec){
   //     assert(vec[vec.size()]<this->vec.size());
   //     vector<T> temp;
   //     for(auto i : vec){
   //         for(auto j : this->vec){
   //             if(this->vec[i] == j){
   //                 temp.push_back(j);
   //             }
   //         }
   //     }
   //     return MinVector(temp);
   // }
//
   // MinVector<T> operator()(vector<T> vec){
   //     return indexFancy(vec);
   // }

    MinVector<T> indexFancy(MinVector<T> a, MinVector<T> b) {
        vector<T> temp;
        int size = a.len();
        for (int i = 0; i < a.len(); ++i) {
            temp.push_back(b[a[i]]);
        }
        return MinVector<T>(temp);
    }

    //MinVector<T> operator()(MinVector<T> vec){
    //    return indexFancy(vec);
    //}

public:
    //类似python的range
    MinVector<T> array(int num) {
        vector<T> vec2;

        for (int i = 0; i < num; i++) {
            vec2.push_back(i);
        }
        this->vec = vec2;
        return MinVector<T>(vec);
    };

    //有步长的array
    MinVector<T> arange(int start, int last, T step = 0) {
        vector<T> vec2;
        if (step == 0) {
            step = 1;
        }
        for (int i = 0; i < (last / step); i++) {

            vec2.push_back(i * step);
        }
        this->vec = vec2;
        return MinVector<T>(vec2);
    }

    MinVector<T> concatone(vector<vector<T>> vec) {
        int size = vec.size();
        vector<T> tempVec = vec[0];
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < vec[i].size(); ++j) {
                tempVec.push_back(vec[i][j]);
            }
        }
        return MinVector<T>(tempVec);
    }

    MinVector<T> AddElem(T value){
        vector<T> temp = this->ThisVec();
        temp.push_back(value);
        return MinVector<T>(temp);
    }

};

#endif //LINEARALGEBRA2_MINVECTOR_H
