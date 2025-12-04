cmake_minimum_required(VERSION 3.10)
project(pyRTSS VERSION 7.3.7.0)
#set(PY_VERSION_SUFFIX "")
set(PY_FULL_VERSION ${PROJECT_VERSION}${PY_VERSION_SUFFIX})

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

# Make sure that the Python and CMake versions match
if (DEFINED PY_BUILD_CMAKE_PROJECT_VERSION)
    if (NOT "${PY_BUILD_CMAKE_PROJECT_VERSION}" MATCHES "^${PY_FULL_VERSION}$")
        message(FATAL_ERROR "Version number does not match "
                             "(${PY_BUILD_CMAKE_PROJECT_VERSION} - ${PY_FULL_VERSION}).")
    endif()
endif()

# Find the Python interpreter and the development files
find_package(Python3 REQUIRED COMPONENTS Development.Module)

# Find the pybind11 package
include(cmake/QueryPythonForPybind11.cmake)
find_pybind11_python_first()

# Compile the example Python module
pybind11_add_module(_pyRTSS MODULE 
	src/ext/pyRTSS.cpp 
	src/ext/RTSS.hpp 
	src/ext/RTSS.cpp
)
target_link_libraries(_pyRTSS PRIVATE rtss)
set_target_properties(_pyRTSS PROPERTIES
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}${PYTHON_MODULE_DEBUG_POSTFIX}")
target_compile_definitions(_pyRTSS PRIVATE
    MODULE_NAME=$<TARGET_FILE_BASE_NAME:_pyRTSS>
    VERSION_INFO="${PY_FULL_VERSION}"
)
#message("***** $<TARGET_FILE_BASE_NAME:_pyRTSS>")
#file(GENERATE OUTPUT STDOUT CONTENT "***** $<TARGET_FILE_BASE_NAME:_pyRTSS>")
# Hide all symbols by default
#set_target_properties(_pyRTSS PROPERTIES
#    CXX_VISIBILITY_PRESET "hidden"
#    VISIBILITY_INLINES_HIDDEN true)

#set(PY_BUILD_CMAKE_IMPORT_NAME "_pyRTSS")

# Install the Python module
install(TARGETS _pyRTSS
        EXCLUDE_FROM_ALL
        COMPONENT python_modules
        DESTINATION ${PY_BUILD_CMAKE_IMPORT_NAME})

# Generate stubs for the Python module
set(WITH_PY_STUBS_DEFAULT On)
if (CMAKE_CROSSCOMPILING)
    set(WITH_PY_STUBS_DEFAULT Off)
endif()
option(WITH_PY_STUBS
    "Generate Python stub files (.pyi) for the Python module."
    ${WITH_PY_STUBS_DEFAULT})
if (WITH_PY_STUBS)
    include(cmake/Pybind11Stubgen.cmake)
    pybind11_stubgen(_pyRTSS
        PACKAGE ${PY_BUILD_CMAKE_IMPORT_NAME}
        COMPONENT python_stubs)
endif()
