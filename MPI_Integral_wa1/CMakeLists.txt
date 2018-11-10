cmake_minimum_required(VERSION 3.10)
project(MPI_Integral_wa1)

set(CMAKE_CXX_STANDARD 11)

IF (APPLE)
    set(CMAKE_C_COMPILER /usr/local/Cellar/open-mpi/3.1.2/bin/mpicc)
    set(CMAKE_CXX_COMPILER /usr/local/Cellar/open-mpi/3.1.2/bin/mpic++)
ELSEIF (LINUX)
    set(CMAKE_C_COMPILER /usr/local/bin/mpicc)
    set(CMAKE_CXX_COMPILER /usr/local/bin/mpic++)
ENDIF()

add_executable(MPI_Integral_wa1 main.cpp)