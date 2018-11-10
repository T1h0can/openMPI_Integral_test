# OpenMPI Integral test

МФТИ生物系大三下学期信息考试第二题，用OpenMPI并发编程框架写程序计算定积分

[考试题链接](https://github.com/fufler/mipt-cs-samples)

MPI_Integral_wa1 - вариант 1

MPI_Integral3 - вариант 2

MPI_Integral-wa3 - вариант 3

以上三题只用到 `MPI_Send` 和 `MPI_Recv` 两个函数，思路类似 [这里](http://mpitutorial.com/tutorials/mpi-send-and-receive/)的例子 `ring.c` 

MPI_newIntegral 算法更简单，用到 `MPI_Bcast` 和 `MPI_Reduce` 广播和数据归约函数