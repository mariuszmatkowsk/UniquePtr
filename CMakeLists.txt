cmake_minimum_required(VERSION 3.31)

project(
    UniquePtr
    VERSION 1.0.0
    DESCRIPTION "UniquePtr implementation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

add_subdirectory(src)

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
endif()

install(
    FILES cmake/uniqueptr_config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/UniquePtr/cmake
)

install(
    EXPORT ${CMAKE_PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/UniquePtr/cmake
)
