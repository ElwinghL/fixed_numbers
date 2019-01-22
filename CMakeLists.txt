cmake_minimum_required(VERSION 3.0)
project(fixed)

project(fixedNumbers
        VERSION 0.0.1
        )



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -O0 -g -pthread")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(fixed
        src/main.cpp
        )

add_executable(testFixed
        src/test.cpp
        googletest/googletest/src/gtest-all.cc
        )

target_include_directories(fixed PRIVATE
        include
        )

target_include_directories(testFixed SYSTEM PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_custom_target(report
        mkdir --parents html
        COMMAND gcovr -b -s -j 4 -r .. --exclude-unreachable-branches -e '.*googletest.*' --html-details --html-title 'Théorie des langages' -o html/coverage.html
        )

target_link_libraries(testFixed
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        )

