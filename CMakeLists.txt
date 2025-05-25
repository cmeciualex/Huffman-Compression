cmake_minimum_required(VERSION 3.28.3)
project(Extra_Credit_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Extra_Credit_2 main.cpp
        Huffman.cpp
        Huffman.h
        Node.cpp
        Node.h
        DataReader.cpp
        DataReader.h
        PriorityQueue.cpp
        PriorityQueue.h
        Code.cpp
        Code.h
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

