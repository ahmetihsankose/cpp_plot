cmake_minimum_required(VERSION 3.16.3)  # CMake version check
project(test)              
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED
COMPONENTS Interpreter Development NumPy)

find_package(PythonLibs     3.8     REQUIRED)
find_package(PythonInterp   3.8     REQUIRED)
find_package (Eigen3 3.4 REQUIRED NO_MODULE)

include_directories(${CMAKE_SOURCE_DIR}/headers
                    ${CMAKE_SOURCE_DIR}/include
                    ${Python3_INCLUDE_DIRS} include
                    ${Python3_NumPy_INCLUDE_DIRS} include
                    /usr/include/python3.8
                    )


add_executable(test main.cpp)

target_link_libraries(test ${Python3_LIBRARIES})
target_link_libraries (test Eigen3::Eigen)
