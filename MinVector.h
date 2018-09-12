
#ifndef LINEARALGEBRA2_MINVECTOR_H
#define LINEARALGEBRA2_MINVECTOR_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


using namespace std;

const double EPSILON = 1e-8;


template<typename T>
class MinVector {
private:
    vector<T> vec;


public:
    MinVector() {
        this->vec = {};
    }

    MinVector(vector<T> vector1) {
        this->vec = vector1;
    }


    ~MinVector() {

    }

public:
    vector<T> ThisVec() {
        return this->vec;
    }

    void _push_back(T n) {
        this->vec.push_back(n);
    }

    T getitem(int index) {
        return this->vec[index];
    }

    int len() {
        return this->vec.size();
    }

    //输出格式
    std::string str() {
        std::string str;
        str.append("Vector(");
        for (int i = 0; i < this->vec.size(); i++) {
            if (i != this->vec.size() - 1) {
                str.append(std::to_string(this->vec[i]) + ',');
            } else {
                str.append(std::to_string(this->vec[i]));
            }
        }

        str.append(")");
        return str;

    }

    //输出格式
    std::string repr_min(vector<T> vec) {
        std::string str;
        str.append("(");
        for (int i = 0; i < vec.size(); i++) {
            if (i != this->vec.size() - 1) {
                str.append(std::to_string(vec[i]) + ',');
            } else {
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }

    //输出格式
    std::string repr_min() {
        std::string str;
        str.append("(");
        for (int i = 0; i < this->vec.size(); i++) {
            if (i != this->vec.size() - 1) {
                str.append(std::to_string(vec[i]) + ',');
            } else {
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }


    //重载<<
    friend ostream &operator<<(ostream &out, MinVector<T> vec) {

        out << "Vector : (";
        for (int i = 0; i < vec.vec.size(); i++) {
            if (i != vec.vec.size() - 1) {
                out << vec.vec[i] << ',';
            } else {
                out << vec.vec[i];
            }
        }

        out << ")";
        return out;
    }

public:
    static std::string zero_print(vector<T> vec) {
        std::string str;
        str.append("(");
        for (int i = 0; i < vec.size(); i++) {
            if (i < vec.size() - 1) {
                str.append(std::to_string(vec[i]) + ',');
            } else {
                str.append(std::to_string(vec[i]));
            }
        }

        str.append(")");
        return str;
    }

public:
    //以下是四则运算
    vector<T> add(vector<T> vec) {
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] + vec[i]);
        }

        return newVec;
    }

    MinVector<T> add2(vector<T> vec) {
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] + vec[i]);
        }

        return MinVector(newVec);
    }


    MinVector<T> add3(MinVector<T> minVector) {
        assert(this->vec.size() == minVector.vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] + minVector.vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator+(MinVector<T> &b) {
        assert(this->vec.size() == b.vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] + b.vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> operator+(T k) {
        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] + k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    vector<T> sub(vector<T> vec) {
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] - vec[i]);
        }

        return newVec;
    }

    vector<T> sub(MinVector<T> vec) {
        assert(this->vec.size() == vec.vec.size());

        vector<T> newVec;
        for (int i = 0; i < this->vec.size(); i++) {
            newVec.push_back(this->vec[i] - vec[i]);
        }

        return newVec;
    }

    MinVector<T> sub2(vector<T> vec) {
        assert(this->vec.size() == vec.size());

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(this->vec[i] - vec[i]);
        }

        return MinVector(newVec);
    }



    MinVector<T> operator-(MinVector<T> &b) {
        assert(this->vec.size() == b.vec.size());

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(this->vec[i] - b.vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> abs_sub(MinVector<T> &b){
        assert(this->vec.size() == b.vec.size());

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(abs(this->vec[i] - b.vec[i]));
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    MinVector<T> operator-(T k) {
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(this->vec[i] - k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }


    MinVector<T> mul(T k) {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(this->vec[i] * k);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator*(T k) {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(this->vec[i] * k);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> operator ^(T k){
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(pow(this->vec[i] , k));
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }



    MinVector<T> rmul(T k) {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(k * this->vec[i]);
        }

        return MinVector(newVec);
    }

    friend MinVector<T> operator*(T k, MinVector<T> r) {

        MinVector<T> rmul(r.vec);
        return k * rmul;
    }


    T dot(vector<T> vec) {
        assert(this->vec.size() == vec.size());
        double ret = 0;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            ret += (vec[i] * this->vec[i]);
        }
        return ret;
    }

    T dot(MinVector<T> vec) {
        assert(this->vec.size() == vec.len());
        T ret = 0;
        T ret2 = 0;

        auto size = this->vec.size();
        for (int i = 0; i < size; i += 2) {
            ret += (vec[i] * this->vec[i]);
            ret2 += (vec[i + 1] * this->vec[i + 1]);

        }
        return ret + ret2;
    }


    MinVector<T> truediv(T k) {
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back((1 / k) * this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> truediv(MinVector<T> k) {
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back((1 / k[i]) * this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> operator/(T k) {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back((1 / k) * this->vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> operator/(MinVector<T> k) {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back((1 / k[i]) * this->vec[i]);
        }
        MinVector<T> box = MinVector<T>(newVec);
        return box;
    }

    MinVector<T> pos() {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(1 * this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> neg() {

        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            newVec.push_back(-1 * this->vec[i]);
        }

        return MinVector(newVec);
    }

    double norm() {
        auto ret = 0;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {
            ret = ret + pow(this->vec[i], 2);
        }

        return sqrt(ret);
    }

    double norm(vector<T> vec) {
        double ret = 0;
        auto size = vec.size();
        for (int i = 0; i < size; i++) {
            ret = ret + pow(vec[i], 2);
        }

        return sqrt(ret);
    }

    double norm(MinVector<T> minVector) {
        double ret = 0;
        auto size = minVector.len();
        for (int i = 0; i < size; i++) {
            ret = ret + pow(vec[i], 2);
        }

        return sqrt(ret);
    }


    MinVector<T> nomalize() {
        assert(this->norm() > EPSILON);
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {

            newVec.push_back(1 / this->norm() * this->vec[i]);
        }

        return MinVector(newVec);
    }

    MinVector<T> nomalize(vector<T> zero) {
        if (this->norm(zero) < EPSILON) {
            throw "Division by zero condition!";
        }
        vector<T> newVec;
        auto size = this->vec.size();
        for (int i = 0; i < size; i++) {

            newVec.push_back(1 / this->norm() * this->vec[i]);
        }

        return MinVector(newVec);
    }

    static vector<T> zero(int dim) {

        vector<T> newVec;
        for (int i = 0; i < dim; i++) {
            newVec.push_back(0);
        }

        return newVec;
    }

    MinVector<T> ones(int dim) {
        vector<T> newVec;
        for (int i = 0; i < dim; i++) {
            newVec.push_back(1);
        }

        return MinVector(newVec);
    }

    MinVector<T> full(int dim, T num) {
        vector<T> newVec;
        for (int i = 0; i < dim; i++) {
            newVec.push_back(num);
        }

        return MinVector(newVec);
    }

    MinVector st_vec(int start,int last){
        assert(start != last);
        MinVector temp;
        for(int i = start;i!=last;++i){
            temp._push_back(this->vec[i]);
        }
        return temp;
    }

    T operator[](int k) {
        assert(k <= vec.size() && k >= 0);
        return getitem(k);
    }

public:
    MinVector<T> argsorted() {
        auto size = this->vec.size();
        if (size < 500) {
            return arg_insertionSort();
        } else {
            return arg_shellSort();
        }
    }

    MinVector<T> sorted(){
        auto size = this->vec.size();
        if (size < 500) {
            return insertionSort();
        } else {
            return shellSort();
        }
    }


private:
    MinVector<T> arg_insertionSort() {
        vector<T> indexTemp;
        auto size = this->vec.size();

        for (int i = 0; i < size; ++i) {
            indexTemp.push_back(i);
        }
        for (int i = 0; i < size; ++i) {
            auto e = this->vec[i];
            auto ie = indexTemp[i];
            int j;
            for (j = i; j > 0 && e < this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
                indexTemp[j] = indexTemp[j - 1];
            }
            this->vec[j] = e;
            indexTemp[j] = ie;
        }
        //MinVector<T> Index = MinVector<T>(indexTemp);
        return MinVector(indexTemp);
    }

    MinVector<T> insertionSort() {

        auto size = this->vec.size();

        for (int i = 0; i < size; ++i) {
            auto e = this->vec[i];
            int j;
            for (j = i; j > 0 && e < this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
            }
            this->vec[j] = e;
        }
        return MinVector(this->vec);
    }

    MinVector<T> arg_shellSort() {
        vector<double> indexTemp;
        auto size = this->vec.size();
        for (int i = 0; i < size; ++i) {
            indexTemp.push_back(i);
        }
        int h = 1, i, j;
        while (h < size / 3) {
            h = 3 * h + 1;
        }

        for (; h > 0; h /= 3) {
            for (i = h; i < size; i++) {
                T temp = this->vec[i];
                T inTemp = indexTemp[i];

                for (j = i - h; j >= 0 && this->vec[j] > temp; j = j - h) {
                    this->vec[j + h] = this->vec[j];
                    indexTemp[j + h] = indexTemp[j];
                }
                this->vec[j + h] = temp;
                indexTemp[j + h] = inTemp;
            }
        }
        return MinVector(indexTemp);
    }

    MinVector<T> shellSort() {

        auto size = this->vec.size();

        int h = 1, i, j;
        while (h < size / 3) {
            h = 3 * h + 1;
        }

        for (; h > 0; h /= 3) {
            for (i = h; i < size; i++) {
                T temp = this->vec[i];
                for (j = i - h; j >= 0 && this->vec[j] > temp; j = j - h) {
                    this->vec[j + h] = this->vec[j];
                }
                this->vec[j + h] = temp;
            }
        }
        return MinVector(this->vec);
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
        for (int i = 0; i < size; ++i) {
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

    MinVector<T> AddElem(T value) {
        vector<T> temp = this->ThisVec();
        temp.push_back(value);
        return MinVector<T>(temp);
    }

    MinVector<T> AddElem(MinVector<T> vec) {
        vector<T> temp = this->ThisVec();
        auto size = vec.len();
        for (int i = 0; i < size; ++i) {
            temp.push_back(vec[i]);
        }

        return MinVector<T>(temp);
    }

    //修改MinVector当中的一个元素
    void valueChange(int i, T num) {
        this->vec[i] = num;
    }

    //修改MinVector修改当前元素
    void valueChange(MinVector<T> vec) {
        auto size = this->vec.size();
        this->vec = move(vec.vec);

    }

    //把MinVector中小于Num的元素加到新的MinVector当中
    MinVector<T> ele_less_than_target(MinVector<T> test,T num) {
        auto size = test.len();
        vector<T> temp;
        for (int i = 0; i < size; ++i) {
            if (test[i]< num)
                temp.push_back(this->vec[i]);
        }

        return MinVector<T>(temp);
    }

    MinVector<T> ele_less_than_target(vector<T> test,T num) {
        auto size = test.size();
        vector<T> temp;
        for (int i = 0; i < size; ++i) {
            if (test[i]< num)
                temp.push_back(this->vec[i]);
        }

        return MinVector<T>(temp);
    }


    MinVector<T> operator()(MinVector<T> test,T num){
        auto size = test.len();
        vector<T> temp;
        for (int i = 0; i < size; ++i) {
            if (test[i]< num)
                temp.push_back(this->vec[i]);
        }

        return MinVector<T>(temp);
    }





    ///欧拉距离+曼哈顿距离
    T euc_distance(MinVector<T> b) {
        T ol;
        auto size = b.len();
        for (int i = 0; i < size; ++i) {
            ol += pow((this->vec[i] - b[i]), 2.0);
        }
        return sqrt(ol);
    }

    T euc_distance2(MinVector<T> b) {
        T ol = 0.0;
        T ol2 = 0.0;
        auto size = b.len();

        for (auto i = 0; i < size; i += 2) {
            ol += pow((this->vec[i] - b[i]), 2.0);
            ol2 += pow((this->vec[i + 1] - b[i + 1]), 2.0);

        }

        return sqrt(ol+ol2);
    }

    T mht_distance2(MinVector<T> b) {
        T ol = 0.0;
        T ol2 = 0.0;
        auto size = b.len();

        for (auto i = 0; i < size; i += 2) {
            ol += abs(this->vec[i] - b[i]);
            ol2 += abs(this->vec[i + 1] - b[i + 1]);

        }
        return ol + ol2;
    }

};

template<typename T>
MinVector<T> minVector(vector<T> vector1) {
    return MinVector<T>(vector1);
}
#endif //LINEARALGEBRA2_MINVECTOR_H
