cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -D_GLIBCXX_USE_CXX11_ABI=0")

project(HashTable)
set(SOURCE_FILES
    Flags.h
    Node.h
    HashTable.h
    HashTable.cpp
    catch.hpp
    tests.cpp)

add_executable(HashTable ${SOURCE_FILES})
target_link_libraries(HashTable ${CMAKE_SOURCE_DIR}/libHashTable_${CMAKE_SYSTEM_NAME}.a)
set_target_properties(HashTable PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )
