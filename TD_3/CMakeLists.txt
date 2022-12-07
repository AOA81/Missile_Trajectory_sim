cmake_minimum_required(VERSION 3.23)
project(project_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_3 main.cpp RK4.h RK4.cpp data.cpp linearInterp.cpp linearInterp.h dynamic.cpp dynamic.h data.h missile_dyn.cpp missile_dyn.h controller.h controller.cpp target_motion.cpp target_motion.h guiding.cpp guiding.h programmed_trajectory.h programmed_trajectory.cpp)
