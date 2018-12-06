cmake_minimum_required(VERSION 3.0.1)

project(prototype CXX)

message(STATUS "CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" SUPPORT_CXX17)
check_cxx_compiler_flag("-msse2"     SUPPORT_MSSE2)
message(STATUS "SUPPORT_CXX17 ${SUPPORT_CXX17}")
message(STATUS "SUPPORT_MSSE2 ${SUPPORT_MSSE2}")

# language options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pipe -Wall -g -fPIC -O3")

# include directory
set(HOME_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${HOME_DIR} ${HOME_DIR}/../)

# source
set(SOURCE ${HOME_DIR}/io.cc)

# executable
add_executable(prototype ${HOME_DIR}/prototype.cc ${SOURCE})

