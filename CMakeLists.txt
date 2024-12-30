cmake_minimum_required(VERSION 3.28)
project(OpenGL_Project VERSION 1.0.0 LANGUAGES CXX C)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Testing
include(CTest)
enable_testing()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Glob for source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
src/*.cpp 
src/*.c 
)

# Create exe
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} 
PRIVATE 
    deps 
    src
    src/controller
    src/view
    src/components
    src/entity
    src/systems
    src/meshes
    )

# Link the GLFW library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/libs/libglfw3dll.a OpenGL::GL)

# Create a list of compiler warning flags for GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wattributes)
endif()

# Add MSVC specific warnings (optional)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)  # Equivalent to high warning level and treat warnings as errors
endif()

# Packaging configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)