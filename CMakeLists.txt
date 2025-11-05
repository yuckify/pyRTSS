cmake_minimum_required(VERSION 3.10)

project(pyRTSS)

# python
add_library(python INTERFACE)
set(PYTHON_VERSION 3.14)
if(WIN32)
	set(PYTHON_INCLUDE "C:/Users/$ENV{USERNAME}/AppData/Local/Python/pythoncore-${PYTHON_VERSION}-64/include")
	set(PYTHON_LIB "C:/Users/$ENV{USERNAME}/AppData/Local/Python/pythoncore-${PYTHON_VERSION}-64/libs")
	message("PYTHON ${PYTHON_INCLUDE}")
	target_include_directories(python INTERFACE ${PYTHON_INCLUDE})
	target_link_directories(python INTERFACE ${PYTHON_LIB})
else()
	
endif()


add_subdirectory(pybind11)

pybind11_add_module(pyRTSS src/pyRTSS.cpp)
