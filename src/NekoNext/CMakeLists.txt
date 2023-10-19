cmake_minimum_required(VERSION 3.24)

project(
  NekoNext
  VERSION 1.0
  DESCRIPTION "NekoNext is a framework for CLIP STUDO PAINT SDK"
  LANGUAGES CXX
)

set(TARGET_NAME NekoNext)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES_DIR "Header Files")
set(SOURCE_FILES_DIR "Source Files")

set(REPOSITORY_ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/src/NekoNext)
target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/extern/TriglavPlugInSDK)
target_include_directories(${TARGET_NAME} INTERFACE ${REPOSITORY_ROOT_DIR}/src/NekoNext/include)
target_precompile_headers(${TARGET_NAME} PRIVATE pch.h)

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

if((MSVC) AND(MSVC_VERSION GREATER_EQUAL 1914))
  # use __cpluscplus
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:__cplusplus")

  # use wchar_t
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:wchar_t")
endif()
