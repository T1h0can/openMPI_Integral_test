cmake_minimum_required(VERSION 3.10)
project(MPI_Integral3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_COMPILER /usr/local/bin/mpicc)
set(CMAKE_CXX_COMPILER /usr/local/bin/mpic++)

add_executable(MPI_Integral3 main.cpp)