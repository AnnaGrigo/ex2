cmake_minimum_required(VERSION 3.20)
project(ex2)

set(CMAKE_CXX_STANDARD 11)
add_executable(ex2 rankTreeTester.cpp hashTable.h UnionFind.h UnionFind.cpp RankTree.h wet2util.h rankTreeTester.cpp)
set_target_properties(ex2 PROPERTIES LINKER_LANGUAGE CXX)




