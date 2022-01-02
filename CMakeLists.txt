
cmake_minimum_required(VERSION 3.16.3)

# set the project name
project(tetris)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include everything under 'include'
include_directories(include)

# recursively get cpp files
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)

# find SDL2 libraries from the system
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2 includes from ${SDL2_INCLUDE_DIRS}")

# find OpenGL libraries from the system
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)


# executable
add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall -Wextra ) #-Werror 
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARY})


find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
message(STATUS "GLEW includes from ${GLEW_INCLUDE_DIRS}")

