cmake_minimum_required(VERSION 3.24)

project(NekoDraw)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE
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

set(HEADER
  data.h
  framework.h
  pch.h
  pluginmain.h
  Processor.h
  PyImage.h
  PyStdErrRedirect.h
  PyStdOutRedirect.h
  resource.h
  StableDiffusionProcessor.h
  StableDiffusionPrompt.cpp
  Strings.h
  TriglavBitmapObject.h
  TriglavProgress.h
)

add_subdirectory(extern/pybind11)
add_definitions(-D_UNICODE -DUNICODE)

# find_package(pybind11 REQUIRED)
add_library(NekoDraw SHARED ${SOURCE} ${HEADER})

target_include_directories(NekoDraw PRIVATE extern/TriglavPlugInSDK)
target_link_libraries(NekoDraw PRIVATE pybind11::embed)
target_sources(NekoDraw PRIVATE NekoDraw.rc)
target_precompile_headers(NekoDraw PRIVATE pch.h)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(NekoDraw PROPERTIES SUFFIX ".cpm")