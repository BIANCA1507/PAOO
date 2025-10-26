cmake_minimum_required(VERSION 3.0)

# Project name
set(myproject "proiect")
project(${myproject})

# Specify the required C++ standard
if(CMAKE_VERSION GREATER "3.1.2") 
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
else()
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()    
endif()

# List all source and header files
set(myfiles 
    src/Song.cpp 
    src/Playlist.cpp
    inc/Song.hpp 
    inc/Playlist.hpp
)

# Create static library from source files
add_library(lib STATIC ${myfiles})

# Create executable from main.cpp
add_executable(${myproject} src/main.cpp)

# Link the library to the executable
target_link_libraries(${myproject} PUBLIC lib)

# Include directories for headers
target_include_directories(${myproject} 
    PRIVATE src 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:inc>
)

# Include directories for the library itself
target_include_directories(lib 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:inc>
)