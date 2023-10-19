cmake_minimum_required(VERSION 3.24)

project(TriglavPluginSDK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CLIP_STUDIO_PAINT_SDK_HEADERS
  TriglavPlugInDefine.h
  TriglavPlugInExtern.h
  TriglavPlugInMain.h
  TriglavPlugInRecord.h
  TriglavPlugInRecordFunction.h
  TriglavPlugInSDK.h
  TriglavPlugInServer.h
  TriglavPlugInService.h
  TriglavPlugInType.h
)

add_library(${PROJECT_NAME} OBJECT ${CLIP_STUDIO_PAINT_SDK_HEADERS})
