cmake_minimum_required(VERSION 2.8)

project(boost-log-example)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

find_package(Threads REQUIRED)
find_package (Boost COMPONENTS log log_setup system thread REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(Boost_ALL_DYN_LINK           ON)

add_definitions( -DBOOST_LOG_DYN_LINK )

include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} boost-log-example.cpp)

target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})

