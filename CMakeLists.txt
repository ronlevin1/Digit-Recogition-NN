cmake_minimum_required(VERSION 3.24)
project(ex4_ron_levin1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(presubmit
        Activation.h
        Dense.h
        Matrix.h
        MlpNetwork.h
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
        Tests1/srcs/presubmit.cpp
#        main.cpp
        )

add_executable(regular_main
        Activation.h
        Dense.h
        Matrix.h
        MlpNetwork.h
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
#        ex4_tests/srcs/presubmit.cpp
        main.cpp)

add_executable(testim
        Activation.h
        Dense.h
        Matrix.h
        MlpNetwork.h
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
        # change file name here -V according to specific test file.
        Tests2/UnitTests/Test_35.cpp
        )