cmake_minimum_required(VERSION 3.16)

project(img-2-video LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)

#System-dependent settings
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()

#Dependencies

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Debug build
if(NOT CMAKE_BUILD_TYPE MATCHES Release)
endif()

#Libraries
list(APPEND libs
)

#Main program
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "img2video")
target_link_libraries(Program PRIVATE "${libs}")

if (WIN32)
	set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
