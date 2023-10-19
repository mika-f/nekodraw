cmake_minimum_required(VERSION 3.24)

project(
  NekoBridge
  VERSION 1.0
  DESCRIPTION "NekoBridge is a Python binding API for CLIP STUDIO PAINT."
  LANGUAGES CXX
)

set(TARGET_NAME NekoBridge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES_DIR "Header Files")
set(SOURCE_FILES_DIR "Source Files")

set(REPOSITORY_ROOT_DIR ${PROJECT_SOURCE_DIR}/../..)

file(GLOB_RECURSE BINDINGS_SOURCES bindings/*.cpp)
file(GLOB_RECURSE BINDINGS_HEADERS bindings/*.h)

file(GLOB_RECURSE BRIDGE_SOURCES bridge/*.cpp)
file(GLOB_RECURSE BRIDGE_HEADERS bridge/*.h)

file(GLOB COMPAT_SOURCES compat/*.cpp)
file(GLOB COMPAT_HEADERS compat/*.h)

file(GLOB COMPAT_MACOS_SOURCES compat/macos/*.cpp)
file(GLOB COMPAT_MACOS_HEADERS compat/macos/*.h)

file(GLOB COMPAT_WINDOWS_SOURCES compat/windows/*.cpp)
file(GLOB COMPAT_WINDOWS_HEADERS compat/windows/*.h)

file(GLOB_RECURSE TRIGLAV_SOURCES triglav/*.cpp)
file(GLOB_RECURSE TRIGLAV_HEADERS triglav/*.h)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

if((APPLE))
  list(FILTER SOURCES EXCLUDE REGEX "compat/windows/(.*\.c(pp)?)")
  list(FILTER HEADERS EXCLUDE REGEX "compat/windows/(.*\.h)")
endif()

if((WIN32))
  list(FILTER SOURCES EXCLUDE REGEX "compat/macos/(.*\.c(pp)?)")
  list(FILTER HEADERS EXCLUDE REGEX "compat/macos/(.*\.h)")
endif()

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

source_group(${HEADER_FILES_DIR}\\bindings FILES ${BINDINGS_HEADERS})
source_group(${SOURCE_FILES_DIR}\\bindings FILES ${BINDINGS_SOURCES})

source_group(${HEADER_FILES_DIR}\\bridge FILES ${BRIDGE_HEADERS})
source_group(${SOURCE_FILES_DIR}\\bridge FILES ${BRIDGE_SOURCES})

if((APPLE))
  source_group(${HEADER_FILES_DIR}\\compat\\macos FILES ${COMPAT_MACOS_HEADERS})
  source_group(${SOURCE_FILES_DIR}\\compat\\macos FILES ${COMPAT_MACOS_SOURCES})
endif()

if((WIN32))
  source_group(${HEADER_FILES_DIR}\\compat\\windows FILES ${COMPAT_WINDOWS_HEADERS})
  source_group(${SOURCE_FILES_DIR}\\compat\\windows FILES ${COMPAT_WINDOWS_SOURCES})
endif()

target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/src/NekoBridge)
target_include_directories(${TARGET_NAME} PRIVATE ${REPOSITORY_ROOT_DIR}/extern/TriglavPlugInSDK)
target_include_directories(${TARGET_NAME} INTERFACE ${REPOSITORY_ROOT_DIR}/src/NekoBridge/include)
target_link_libraries(${TARGET_NAME} PRIVATE pybind11::embed)
target_link_libraries(${TARGET_NAME} PRIVATE NekoNext)
target_precompile_headers(${TARGET_NAME} PRIVATE pch.h)

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

if((MSVC) AND(MSVC_VERSION GREATER_EQUAL 1914))
  # use __cpluscplus
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:__cplusplus")

  # use wchar_t
  target_compile_options(${TARGET_NAME} PUBLIC "/Zc:wchar_t")
endif()
