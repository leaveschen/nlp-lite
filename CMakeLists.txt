cmake_minimum_required(VERSION 3.0.1)

project(nlp CXX)

# check language support
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
set(NLP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlp)
include_directories(${NLP_DIR})

# source
set(PROJECT_SRC
	${NLP_DIR}/analyser/sample_metrics.cc)

# executable
add_executable(classifier ${NLP_DIR}/apps/classifier.cc ${PROJECT_SRC})

