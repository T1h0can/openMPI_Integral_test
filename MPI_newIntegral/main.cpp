/*
 * 通过MPI_Bcast函数广播local_size，
 * 然后通过MPI_Reduce快速回收所有local_result并求和存入result为定积分结果
*/

#include <iostream>
#include <cmath>
#include <unistd.h>
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
    double local_size, local_min, local_max, local_result;
    double result;
    int pid = getpid();
    max = pow(pid, 1.0/3.0);
//    max = 5;
    cout << "Processor " << world_rank << ", pid: " << pid << " max: " << max << endl;
    local_size = (max - min) / world_size;

    MPI_Bcast(&local_size, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    local_min = min + world_rank * local_size;
    local_max = local_min + local_size;
    local_result = integral(func, local_min, local_max);

    cout << "Processor " << world_rank << " local_min = " << local_min << " local_max = " << local_max << " local_result = " << local_result << endl;

    MPI_Reduce(&local_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0c, MPI_COMM_WORLD);

    if(world_rank == 0){
        cout << "Result = " << result << endl;
    }

    MPI_Finalize();
    return 0;
}