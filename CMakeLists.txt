cmake_minimum_required(VERSION 3.29)
project(gps)

set(CMAKE_CXX_STANDARD 20)

add_executable(gps main.cpp
        geo_utils.cpp
        geo_utils.h
        time_utils.cpp
        time_utils.h
        track_data_provider.cpp
        track_data_provider.h
        metric_calculators.cpp
        metric_calculators.h
        reporter.cpp
        reporter.h
        track_analyzer.cpp
        track_analyzer.h)
