/*
 *主要骚思路：
 * 针对вариант 2，上界和最小进程号有关，而最小进程号永远是MPI中rank为0的进程，然后根据击鼓传花那个例子（ring.c）
 * 在0号进程里求出local数组里所有东西，击鼓传花传下去，当重新传回0号进程时，就是最后的结果
*/

#include <iostream>
#include <unistd.h>
#include <cmath>
#include <mpi.h>

using namespace std;

const int PIECE = 10000;

double func(double x){
    double y = sin(x) / log(x);
    return y;
}

double integral(double (*f)(double), double min, double max){
    double delta = (max - min) / PIECE;
    double result = 0;
    for(int i = 0; i < PIECE; i ++){
        result += (* f)(min + i * delta) * delta;
    }
    return result;
}

int main(int argc, char *argv[]) {
//    std::cout << "Hello, World!" << std::endl;
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double min = 2, max;
    double result;// = 0, local_result;
    double local[4];    //local_size, local_min, local_max, local_result;

    if(world_rank != 0){
        MPI_Recv(&local, 4, MPI_DOUBLE, world_rank - 1, 666, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        local[1] = local[2];
        local[2] = local[1] + local[0];
        local[3] += integral(func, local[1], local[2]);
    }else{
        int pid = getpid();
        max = pow(pid, 1.0/3.0);
//        max = 5;
        local[0] = (max - min) / world_size;
        local[1] = min;
        local[2] = local[1] + local[0];
        local[3] = integral(func, local[1], local[2]);
    }

    MPI_Send(&local, 4, MPI_DOUBLE, (world_rank + 1) % world_size, 666, MPI_COMM_WORLD);

    if(world_rank == 0){
        MPI_Recv(&local, 4, MPI_DOUBLE, world_size - 1, 666, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        result = local[3];

        cout << "Final result = " << result << endl;
    }

    MPI_Finalize();
    return 0;
}