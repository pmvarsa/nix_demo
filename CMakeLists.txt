cmake_minimum_required (VERSION 2.8)
project (nix_demo)

# Default to Release build
if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE Release)
endif()

# Documenation build
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Build the API docs" ${DOXYGEN_FOUND})
if (DOXYGEN_FOUND)
	set (DOXYGEN_INPUT Doxyfile)
endif (DOXYGEN_FOUND)

add_custom_target( docs
	command ${DOXYGEN_EXECUTABLE} Doxyfile
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMENT "Generating API documentation."
	VERBATIM )

# Build with C++ 14
set (CMAKE_CXX_STANDARD 14)

# For code coverage analysis, define this variable.
# Taken from here: https://texus.me/2015/09/06/cmake-and-gcov/
# See also: https://jhbell.com/using-cmake-and-gcov
#set (CODE_COVERAGE TRUE)
if (CODE_COVERAGE)
	set (CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
	set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
else ()
	set (CMAKE_CXX_FLAGS "-Wall -Wextra")
	set (CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
	set (CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(CODE_COVERAGE)

include(ExternalProject)
include(3rdparty/lua53.cmake)

# Test for Mac OS X or Linux
if(UNIX AND NOT APPLE)
	add_definitions(-DLINUX)
elseif(UNIX AND APPLE)
	add_definitions(-DOSX)
endif()

include_directories(src)

# Build the project
add_subdirectory(src)

