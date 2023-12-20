# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( generic-ostream-iterator-build
    VERSION 1.0
    DESCRIPTION "Build system for generic-ostream-iterator."
    LANGUAGES CXX
)

# Create interface library
add_library( genosit INTERFACE )
add_library( genosit::genosit ALIAS genosit )

# Compile tests
option( GENOSIT_TESTS "Enable / disable tests." ON )
if( GENOSIT_TESTS )
    add_subdirectory( tests )
else()
    message( STATUS "Skipping tests." )
endif()

# Setting installation paths
target_include_directories( genosit INTERFACE
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
include( CMakePackageConfigHelpers )

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

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/genositConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/genositConfigVersion.cmake
    DESTINATION lib/cmake/genosit
)

export( EXPORT genositTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/genositTargets.cmake"
)