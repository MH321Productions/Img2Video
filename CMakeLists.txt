cmake_minimum_required(VERSION 3.28)
project(Img2Video)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED net core base) # Und andere Module
include(${wxWidgets_USE_FILE})

include_directories(src)

add_executable(Img2Video WIN32
        src/main.cpp
        src/UI/AbstractConverterFrame.h
        src/UI/AbstractConverterFrame.cpp
        src/UI/ConverterFrame.hpp
        src/UI/ConverterFrame.cpp
        src/Worker/ProcessHandler.cpp
        src/Worker/ProcessHandler.hpp
        src/Worker/WindowsProcessHandler.cpp
        src/Worker/UnixProcessHandler.cpp
)
target_link_libraries(Img2Video ${wxWidgets_LIBRARIES})

if(WIN32)
    add_compile_definitions(I2V_WINDOWS UNICODE _UNICODE)

    # Generate resources
    add_custom_command(
        OUTPUT icon.png
        COMMAND inkscape -o icon.png -C -w 256 -h 256 "${CMAKE_SOURCE_DIR}/res/cinema-7713265.svg"
        DEPENDS res/cinema-7713265.svg
    )

    add_custom_command(
        OUTPUT icon.ico
        COMMAND magick icon.png icon.ico
        DEPENDS ${CMAKE_BINARY_DIR}/icon.png
    )

    add_custom_command(
        OUTPUT icon.rc
        COMMAND echo id ICON icon.ico > icon.rc
        DEPENDS icon.ico
    )

    target_sources(Img2Video PRIVATE ${CMAKE_BINARY_DIR}/icon.rc)
endif()
