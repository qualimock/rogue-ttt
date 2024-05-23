cmake_minimum_required(VERSION 3.20)
project(rogue-ttt LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(dependencies/rapidjson/include)

add_subdirectory(dependencies)
add_subdirectory(src)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
