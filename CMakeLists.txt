cmake_minimum_required(VERSION 3.20)
project(ndr VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
  GIT_TAG v2.0.6
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SOURCE_SUBDIR cmake
)

fetchcontent_makeavailable(glad)

glad_add_library(
  glad
  REPRODUCIBLE
  LOADER
  API gl:core=3.3
)

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

fetchcontent_declare(
    glm

    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3

    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    SYSTEM
)

fetchcontent_makeavailable(glm)

find_package(OpenGL REQUIRED)

add_executable(ndr
  app/main.cpp
  src/app/Application.cpp
  src/platform/Paths.cpp
  src/platform/Window.cpp
  src/render/Renderer.cpp
  src/render/Mesh.cpp
  src/render/ShaderProgram.cpp
  src/resources/ResourceLoader.cpp
)

target_link_libraries(ndr PRIVATE glfw OpenGL::GL glad glm)

target_include_directories(ndr
  PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_compile_options(ndr PRIVATE
  "$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Wconversion>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->"
)

add_custom_target(ndr_resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/resources"
          "$<TARGET_FILE_DIR:ndr>/resources"
  COMMENT "Copying runtime resources"
  VERBATIM
)

add_dependencies(ndr_resources ndr)

include(GNUInstallDirs)

install(
  TARGETS ndr
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/resources/"
  DESTINATION "${CMAKE_INSTALL_BINDIR}/resources"
)
