cmake_minimum_required(VERSION 3.28)
project(Img2Video)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED net core base) # Und andere Module
include(${wxWidgets_USE_FILE})

include_directories(src)

if(WIN32)
add_compile_definitions(I2V_WINDOWS)
endif()

add_executable(Img2Video WIN32
        src/main.cpp
        src/UI/AbstractConverterFrame.h
        src/UI/AbstractConverterFrame.cpp
        src/UI/ConverterFrame.hpp
        src/UI/ConverterFrame.cpp
        src/Worker/ProgressServer.cpp
        src/Worker/ProgressServer.hpp
        src/Worker/ProcessHandler.cpp
        src/Worker/ProcessHandler.hpp
)
target_link_libraries(Img2Video ${wxWidgets_LIBRARIES})
