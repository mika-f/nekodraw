cmake_minimum_required(VERSION 3.24)

project(NekoDraw)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/pybind11)
add_definitions(-D_UNICODE -DUNICODE)

# find_package(pybind11 REQUIRED)
add_library(NekoDraw SHARED
  dllmain.cpp
  pch.cpp
  pluginmain.cpp
  PyImage.cpp
  PyStdErrRedirect.cpp
  PyStdOutRedirect.cpp
  PyWith.cpp
  StableDiffusionProcessor.cpp
  StableDiffusionPrompt.cpp
  TriglavBitmapObject.cpp
  TriglavProgress.cpp
)

target_include_directories(NekoDraw PRIVATE extern/TriglavPlugInSDK)
target_link_libraries(NekoDraw PRIVATE pybind11::embed)
target_sources(NekoDraw PRIVATE NekoDraw.rc)