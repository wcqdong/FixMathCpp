cmake_minimum_required(VERSION 3.20)
project(FMath)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_DIR)


add_executable(${PROJECT_NAME} ${SRC_DIR})

