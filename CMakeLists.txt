project(bitvec)

cmake_minimum_required(VERSION 3.0.2)

include_directories("${PROJECT_SOURCE_DIR}")

# find_package(Boost)
find_package(Boost REQUIRED COMPONENTS container unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# find_package(OpenMP)
# if (OPENMP_FOUND)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# endif()

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(WARNING "CMAKE_BUILD_TYPE is not provided. We use Debug mode.")
	message(STATUS "To specify build type, for example,
	$ cmake -DCMAKE_BUILD_TYPE=Debug or Release .")
endif()

message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Enable testing")
enable_testing()
add_subdirectory(test)
