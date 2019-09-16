# Copyright(c) 2019-present, Anton Lilja.
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.2)

project(
	xcb_wrapper
	VERSION 1.0.0
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

# Options
option(XCB_WRAPPER_BUILD_EXAMPLES "Builds examples" FALSE)

find_package(XCB MODULE REQUIRED xcb xcb-cursor)

# Targets
add_library(xcb_wrapper 
    src/connection.cpp
    src/screen.cpp
    src/window.cpp
    src/event.cpp
    src/atom.cpp
    src/cursor.cpp
    src/drawable.cpp
)

add_library(xcb::wrapper ALIAS xcb_wrapper)

target_include_directories(xcb_wrapper 
	PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${X11_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(xcb_wrapper PRIVATE ${XCB_LIBRARIES})

target_compile_features(xcb_wrapper PUBLIC cxx_std_17)

if(XCB_WRAPPER_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
