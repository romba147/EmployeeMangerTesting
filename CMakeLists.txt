cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp AVLtree.cpp AVLtree.h employee.cpp employee.h Company.cpp Company.h EmployeeManager.cpp EmployeeManager.h)
