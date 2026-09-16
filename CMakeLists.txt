cmake_minimum_required(VERSION 3.16)
project(ndr VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# GLFW (FetchContent)
# ------------------------------------------------------------
include(FetchContent)

fetchcontent_declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

fetchcontent_makeavailable(glfw)

fetchcontent_declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v2.0.6
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
    SOURCE_SUBDIR  cmake
)

fetchcontent_makeavailable(glad)

glad_add_library(
    glad
    REPRODUCIBLE
    LOADER
    API gl:core=4.6
)

find_package(OpenGL REQUIRED)

file(GLOB NDR_SOURCES CONFIGURE_DEPENDS
  app/*.cpp
  src/app/*.cpp
  src/platform/*.cpp
  src/render/*.cpp
)

add_executable(ndr ${NDR_SOURCES})

target_link_libraries(ndr
PRIVATE glfw
PRIVATE OpenGL::GL
PRIVATE glad
)

target_include_directories(ndr
PRIVATE ${CMAKE_SOURCE_DIR}/include
PRIVATE ${CMAKE_SOURCE_DIR}/external
)
