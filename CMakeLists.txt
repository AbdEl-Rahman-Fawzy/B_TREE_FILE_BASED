cmake_minimum_required(VERSION 3.23)
project(B_TREE_FILE_BASED)

set(CMAKE_CXX_STANDARD 14)

add_executable(B_TREE_FILE_BASED
        .idea/.gitignore
        .idea/B_TREE_FILE_BASED.iml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        BTree.cpp
        main.cpp BTRE.h)
