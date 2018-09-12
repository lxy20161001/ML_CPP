# ML_CPP
以bobo老师的python代码为原本，修改而成的C++简单版本KNN邻近算法，网址：https://coding.imooc.com/class/169.html

 
现在sklearn上的iris和digits经过测试都是可以运行的，但速度有待提高；

1、 DataSets 是数据集，主要来源于sklearn；

2、Knn_Ang Knn分类算法的简单实现

3、knn_Thread_help 面向简单knn算法的多线程帮助文件，但非常low，写死了运行13个线程，运用Thread+promise操作；

4、LinearSystem 提供线性方程组的功能，例如求逆等，暂时还比较少功能

5、MinMatrix 实现矩阵功能，以及矩阵运算等，还比较简陋；

6、MinVector 实现向量功能，暂时和矩阵一样，用到再新写方法；

7、Numpy_Cpp 实现一些python Numpy的功能，模仿和学习未目的；

8、RbTree 简单的红黑树，用于帮助Knn分类

9、SortHelp 简单的排序算法，由于数据量还不是很大，所以就写了选择和希尔排序；

10 Sim_lin_reg 简单的线性回归和多元线性回归；

11 Split_data 创造训练集和测试集

12 Standard_Scaler 数据归一化

