cmake_minimum_required(VERSION 3.14)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(SnakeGame main.cpp)
target_link_libraries(SnakeGame PRIVATE raylib)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    target_link_options(SnakeGame PRIVATE 
        "-sUSE_GLFW=3"       
        "-sASYNCIFY=1"            
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets@/" 
        "--shell-file" "${CMAKE_CURRENT_SOURCE_DIR}/shell.html"
    )
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()