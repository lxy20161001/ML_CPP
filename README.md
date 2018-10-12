# ML_CPP
以bobo老师的python代码为原本，修改而成的C++简单版本KNN邻近算法，网址：https://coding.imooc.com/class/169.html

 
现在sklearn的自带数据做测试用例，经过测试是可以运行的，但速度有待提高；

1、 DataSets 是数据集，主要来源于sklearn；

2、Knn_Ang Knn分类算法的简单实现

3、LinearSystem 提供线性方程组的功能，例如求逆等，暂时还比较少功能

4、MinMatrix 实现矩阵功能，以及矩阵运算等，还比较简陋；

5、MinVector 实现向量功能，暂时和矩阵一样，用到再新写方法；

6、Numpy_Cpp 实现一些python Numpy的功能，模仿和学习未目的；

7、RbTree 简单的红黑树，用于帮助Knn分类

8、 Split_data 创造训练集和测试集

9、 Standard_Scaler 数据归一化


对现有项目进行了小小的重构，把暂时不需要的部分去掉，运行速度接近个人满意的方向；
