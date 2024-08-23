cmake_minimum_required(VERSION 3.28)
project(Img2Video)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED core base) # Und andere Module
include(${wxWidgets_USE_FILE})

add_executable(Img2Video WIN32
        src/main.cpp
        src/AbstractConverterFrame.cpp
        src/ConverterFrame.cpp
)
target_link_libraries(Img2Video ${wxWidgets_LIBRARIES})
