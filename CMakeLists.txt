# Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved #

cmake_minimum_required(VERSION 3.20)

project(DennisEnhanced)

set(DENNIS_SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(DENNIS_LIB_DIR ${DENNIS_SRC_DIR}/lib)

add_subdirectory(dectalk/dapi/src)
add_subdirectory(dennis)
add_subdirectory(dennis_watcher)
add_subdirectory(say)
