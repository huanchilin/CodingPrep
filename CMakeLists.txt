cmake_minimum_required(VERSION 3.0.0)

project(mac_CMAKE VERSION 0.1.0)

AUX_SOURCE_DIRECTORY(./src SRC)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(CodingPrep main.cpp ${SRC})

install(TARGETS ${bin} CONFIGURATIONS ${CMAKE_BUILD_TYPE} DESTINATION ${CMAKE_BUILD_TYPE})