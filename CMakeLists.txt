cmake_minimum_required(VERSION 3.10)
project(MiniSearchEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine 
    src/main.cpp
    src/document.cpp
    src/search_engine.cpp
    src/indexer.cpp
)

target_include_directories(search_engine PRIVATE include)
