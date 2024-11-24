cmake_minimum_required(VERSION 3.29)
project(A3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(A3
    distance_data.csv
    distance_data.xlsx
    main.cpp
    Map.cpp
    Map.h
    priority_provinces.txt
    Queue.cpp
    Queue.h
    RoutePlanner.cpp
    RoutePlanner.h
    Stack.cpp
    Stack.h
    weather_restricted_provinces.txt)
