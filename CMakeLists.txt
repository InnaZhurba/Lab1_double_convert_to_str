# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.16)
project(Lab1_double_convert_to_str)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "/mnt/d/UCU/AKS/boost_1_78_0")
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.78.0 COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Lab1_double_convert_to_str main.cpp)
target_link_libraries(Lab1_double_convert_to_str ${Boost_LIBRARIES})
#add_executable(Lab1_double_convert_to_str main.cpp)