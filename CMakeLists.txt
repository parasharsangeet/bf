cmake_minimum_required(VERSION 3.10)

project(bf)

add_executable(bf src/bf.c)

set_target_properties(bf PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin/Debug/
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin/Release/
)