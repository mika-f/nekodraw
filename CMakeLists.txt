cmake_minimum_required(VERSION 3.24)

project(
  NekoDraw
  VERSION 1.0
  DESCRIPTION "NekoDraw is AI Assistant for CLIP STUDIO PAINT"
  LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# compiled libraries
add_subdirectory(extern/pybind11)

# compiled frameworks
add_subdirectory(src/NekoNext)
add_subdirectory(src/NekoBridge)

# compiled plugin(s)
add_subdirectory(src/NekoDraw)
add_subdirectory(src/NekoBridgeExample)