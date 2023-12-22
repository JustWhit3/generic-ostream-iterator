# CMake settings
cmake_minimum_required(VERSION 3.15)

# Project settings
project(generic-ostream-iterator-build
    VERSION 1.0
    DESCRIPTION "Build system for generic-ostream-iterator."
    LANGUAGES CXX
)

# Info about the build type
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message( STATUS "Build type: DEBUG" )
    add_compile_definitions( DEBUG_GENOSIT )
else()
    message( STATUS "Build type: RELEASE" )
endif()

# Set compiler options
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Include directories
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd /Oy /Gw" )
else()
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fno-omit-frame-pointer -fdata-sections -g" )
    else()
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fdata-sections" )
    endif()
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

# Create interface library
add_library(genosit INTERFACE)
add_library(genosit::genosit ALIAS genosit)

# Compiling examples
set( EXAMPLE "genosit_example" )
add_executable( ${EXAMPLE} example.cpp )
find_program( CPPCHECK_FOUND cppcheck )
if ( CPPCHECK_FOUND AND CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( cppcheck_options "--enable=warning" "--inconclusive" "--force" "--inline-suppr" )
    set_target_properties( ${EXAMPLE} PROPERTIES CXX_CPPCHECK "${CPPCHECK_FOUND}" )
endif()

# Compile tests
option(GENOSIT_TESTS "Enable / disable tests." ON)
if( CMAKE_BUILD_TYPE STREQUAL "Debug" AND GENOSIT_TESTS )
    add_subdirectory( tests )
else()
    message( STATUS "Skipping tests." )
endif()

# Format the code
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    option(FORMAT "Format the code using clang-format" ON)
    if(FORMAT)
        find_program(CLANG_FORMAT_EXECUTABLE clang-format)
        if(CLANG_FORMAT_EXECUTABLE)
            message(STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}")
            file(GLOB_RECURSE SOURCE_FILES
                ${CMAKE_SOURCE_DIR}/include/generic/ostream_iterator.hpp
                ${CMAKE_SOURCE_DIR}/tests/*.cpp
                ${CMAKE_SOURCE_DIR}/example.cpp
            )
            add_custom_target(format
                COMMAND ${CLANG_FORMAT_EXECUTABLE}
                -i
                ${SOURCE_FILES}
            )
            add_dependencies(${EXAMPLE} format)
        else()
            message(STATUS "clang-format not found. Skipping code formatting.")
        endif()
    endif()
endif()

# Setting installation paths
target_include_directories(genosit INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY include/generic
    DESTINATION include
)

# Creating the package files
install(
    TARGETS genosit
    EXPORT genositTargets
    DESTINATION lib
)

install(
    EXPORT genositTargets
    FILE genositTargets.cmake
    NAMESPACE genosit::
    DESTINATION lib/cmake/genosit
)

# Configure package files
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/genositConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/genosit"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/genositConfigVersion.cmake"
    VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/genositConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/genositConfigVersion.cmake
    DESTINATION lib/cmake/genosit
)

export(EXPORT genositTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/genositTargets.cmake"
)