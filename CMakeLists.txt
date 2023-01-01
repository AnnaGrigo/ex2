cmake_minimum_required(VERSION 3.20)
project(ex2)

set(CMAKE_CXX_STANDARD 11)
#add_executable(ex2 rankTreeTester.cpp RankTree.h wet2util.h)
add_executable(ex2 hashTable.h UnionFind.h UnionFind.cpp RankTree.h wet2util.h Player.cpp
        Player.h Team.cpp Team.h worldcup23a2.cpp worldcup23a2.h main23a2.cpp)
set_target_properties(ex2 PROPERTIES LINKER_LANGUAGE CXX)




