# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( generic-ostream-iterator-tests
    VERSION 1.0
    DESCRIPTION "Build system for generic-ostream-iterator tests."
    LANGUAGES CXX
)

# Other settings for paths
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )

# Set c++ standard options
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Executables names
set( SYSTEM "genosit_system_tests" )
set( UNIT "genosit_unit_tests" )
set( THREAD "genosit_threading_tests" )

# Create executables
add_executable( ${UNIT} unit_tests.cpp )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic" )
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Fetching doctest
find_package( doctest )

if( NOT doctest_FOUND )
    include(FetchContent)
    FetchContent_Declare(
      doctest
      GIT_REPOSITORY "https://github.com/doctest/doctest"
      GIT_TAG master
    )
    message( STATUS "Fetching doctest..." )
    FetchContent_MakeAvailable( doctest )
endif()

# Adding specific linker flags
target_link_libraries( ${UNIT} PRIVATE doctest::doctest )

