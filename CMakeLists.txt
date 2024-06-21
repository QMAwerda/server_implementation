cmake_minimum_required(VERSION 3.5)
project(NetServer LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17) # - it'll fuck your brain on standarts and constructions

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../NetCommon/src/HeaderFiles)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../NetCommon build)
set_target_properties(NetCommon PROPERTIES LINKER_LANGUAGE CXX)

add_executable(server src/SourceFiles/SimpleServer.cpp)
target_link_libraries(server PUBLIC NetCommon)
