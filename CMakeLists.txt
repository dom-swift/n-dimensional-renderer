cmake_minimum_required(VERSION 3.16)
project(ndr VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v2.0.6
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(
  glad
  REPRODUCIBLE
  LOADER
  API gl:core=4.6
)

find_package(OpenGL REQUIRED)

add_executable(ndr
  app/main.cpp
  src/app/Application.cpp
  src/platform/Window.cpp
  src/render/Renderer.cpp
  src/render/ShaderProgram.cpp
)

target_link_libraries(ndr PRIVATE glfw OpenGL::GL glad)

target_include_directories(ndr
  PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

add_custom_command(
  TARGET ndr POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/shaders"
          "$<TARGET_FILE_DIR:ndr>/shaders"
  VERBATIM
)
