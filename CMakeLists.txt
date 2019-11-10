
cmake_minimum_required(VERSION 3.13.4)
project(sparse-matrix-AlejandroMamaniAndia199802)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)


add_executable(sparse-matrix-AlejandroMamaniAndia199802  main.cpp node.h mocker/mocker.cpp mocker/mocker.h tester/tester.cpp tester/tester.h matrix.h)