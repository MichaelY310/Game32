cmake_minimum_required(VERSION 3.10)
project(Game32)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the source files to the project
file(GLOB SOURCES "src/Core/*.cpp" "src/Render/*.cpp" "src/*.cpp" "Dependeicies/Glad/*.c")

# Set the path to the GLUT headers
include_directories("Dependencies/" "Dependencies/Glad" "src")

# Find the necessary packages (OpenGL and GLUT)
find_package(OpenGL REQUIRED)
find_library(GLUT_LIBRARY NAMES glut PATHS Dependencies/Glut)

# Make sure the packages are found
if (NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

if (NOT GLUT_LIBRARY)
    message(FATAL_ERROR "GLUT library not found")
endif()

# Create the executable
add_executable(Game32 ${SOURCES})

# Link the executable with the OpenGL and GLUT libraries
target_link_libraries(Game32 PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
