# ML_CPP
以bobo老师的python代码为原本，修改而成的C++简单版本KNN邻近算法，网址：https://coding.imooc.com/class/169.html

 
按照 bobo老师的机器算法入门课程的python代码进行C++的改编，完全是为了学习C++而做，所以代码质量比较LOW，还请见谅；
 
同时代码会随着学习和眼界的提高，慢慢修改。

 
 
 1、线性代数的线性系统部分：
    老师在_forward的部分进行了判断是否最大主元，然后再进行交换；而改成C++后，由于矩阵中的每一行实际都是一个向量，而且不是lvalue，限于技术问题，我未找到方法交换行数，于是我就选择使用插入排序，由于在下并没有接触到更大的矩阵，暂时工作中遇到的都是1000-10000，插入排序在进行一次排序后，每次循环再排序，属于接近有序的情况下排序，速度是非常快的，于是就改用这个折中方法暂时替代老师的方法。
    
    
    MinMatrix<T> _forward(){
        int n = this->_m;
        this->Ab = this->Ab.sorted();//这里先进行一次排序，找到最大的第一个主元
        for( int i = 0 ; i < n; ++i){
            this->Ab = this->Ab.sorted();//这里会进行排序，第一主元已经完成，所以第一列除了第一行都是0，于是自动地就面向其他行数进行排序
            this->Ab.elimination(i,this->Ab[i]/this->Ab[i][i]);
            for( int j = i+1;j<n;++j){
                this->Ab.elimination(j,this->Ab[j].sub(this->Ab[i]*this->Ab[j][i]));
            }
        }

        return this->Ab;

    }
  
    public:
    MinMatrix<A> sorted() {
        return insertionSort();
    }

    private:
    //考虑到暂时使用的矩阵比较小，于是使用插入算法
    MinMatrix<A> insertionSort() {
        for (int i = 0; i < this->vec.size(); ++i) {
            vector<A> e = this->vec[i];
            int j;
            for (j = i; j > 0 && e > this->vec[j - 1]; j--) {
                this->vec[j] = this->vec[j - 1];
            }
            this->vec[j] = e;
        }
        return MinMatrix(this->vec);
    }
    
    
    public:
    //高斯消元部件
    void elimination(int num, MinVector<A> T) {
        for (int i = 0; i < T.len(); ++i) {
            this->vec[num][i] = T[i];
        }
    }
    
 以上是线性系统的一些主要部分。
 
 2、线性代数Vector类、Martix类，基本都是模拟Numpy，只是方法可能有些low，请大家包含。
 
 
 
 
   
    
    
    
   
 
 
 
