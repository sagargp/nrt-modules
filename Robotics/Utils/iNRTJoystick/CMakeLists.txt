cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} rapidjson/)

set(CMAKE_MODULE_PATH /usr/share/nrt/CMakeModules)
include(NRTHelpers)

nrt_build_module(iNRTJoystick
  SOURCES iNRTJoystick.C)
