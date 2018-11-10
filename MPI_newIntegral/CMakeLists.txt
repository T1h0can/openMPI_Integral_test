cmake_minimum_required(VERSION 3.10)
project(MPI_newIntegral)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_COMPILER /usr/local/Cellar/open-mpi/3.1.2/bin/mpicc)
set(CMAKE_CXX_COMPILER /usr/local/Cellar/open-mpi/3.1.2/bin/mpic++)

add_executable(MPI_newIntegral main.cpp)