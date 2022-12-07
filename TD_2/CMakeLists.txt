cmake_minimum_required(VERSION 3.23)
project(project_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_2 main.cpp RK4.h RK4.cpp data.cpp linearInterp.cpp linearInterp.h dynamic.cpp dynamic.h data.h gaussRand.cpp gaussRand.h)
