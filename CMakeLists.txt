cmake_minimum_required(VERSION 3.10)

project(pyRTSS)

# rtss
message(STATUS "RTSS")
add_library(rtss INTERFACE)
#target_include_directories(rtss INTERFACE "C:/Program Files (x86)/RivaTuner Statistics Server/SDK/Include")
find_path(RTSS_INCLUDE
	NAMES
		RTSSSharedMemory.h
	PATHS
		"C:/Program Files (x86)/RivaTuner Statistics Server/SDK/Include"
		"C:/Program Files/RivaTuner Statistics Server/SDK/Include"
)
target_include_directories(rtss INTERFACE ${RTSS_INCLUDE})
message(STATUS "	INCLUDE ${RTSS_INCLUDE}")

# Find the Python interpreter and the development files
if (CMAKE_CROSSCOMPILING AND NOT (APPLE AND "$ENV{CIBUILDWHEEL}" STREQUAL "1"))
    find_package(Python3 REQUIRED COMPONENTS Development.Module)
else()
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
endif()

include(cmake/QueryPythonForPybind11.cmake)
find_pybind11_python_first()

pybind11_add_module(pyRTSS 
	src/ext/pyRTSS.cpp
	src/ext/RTSS.hpp
	src/ext/RTSS.cpp
)
target_link_libraries(pyRTSS PUBLIC rtss)
