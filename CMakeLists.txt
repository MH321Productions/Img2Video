cmake_minimum_required(VERSION 3.16)

project(img-2-video LANGUAGES CXX)

include_directories(include)

#System-dependent settings
if (WIN32)
    add_compile_definitions(I2V_WINDOWS)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)

#Main program
add_executable(Program src/Main.cpp src/Img2Windows.cpp src/Img2Unix.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "img2video")

#Release build
if(CMAKE_BUILD_TYPE MATCHES Release)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    elseif()
        target_link_libraries(Program -static-libgcc -static-libstdc++)
    endif()
endif()