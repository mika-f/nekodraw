cmake_minimum_required(VERSION 3.24)

project(
  NekoBridgeSample
  VERSION 1.0
  DESCRIPTION ""
  LANGUAGES CXX
)

set(TARGET_NAME NekoBridgeSample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES_DIR "Header Files")
set(SOURCE_FILES_DIR "Source Files")

set(REPOSITORY_ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_library(${TARGET_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/src/NekoBridgeExample)
target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/extern/TriglavPlugInSDK)
target_link_libraries(${TARGET_NAME} PRIVATE NekoBridge)
target_precompile_headers(${TARGET_NAME} PRIVATE pch.h)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".cpm")
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if((WIN32))
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND copy /Y "$(TargetDir)$(ProjectName).cpm" "$(APPDATA)\\CELSYSUserData\\CELSYS\\CLIPStudioModule\\PlugIn\\PAINT\\$(ProjectName).cpm" VERBATIM)
endif()

if((MSVC) AND(MSVC_VERSION GREATER_EQUAL 1914))
  # use __cpluscplus
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:__cplusplus")

  # use wchar_t
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:wchar_t")
endif()
