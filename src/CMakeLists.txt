add_library(
    uniqueptr
    INTERFACE
    UniquePtr/UniquePtr.hpp
)

target_include_directories(
    uniqueptr
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS uniqueptr
    EXPORT ${CMAKE_PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/UniquePtr/cmake
)

install(
    FILES UniquePtr/UniquePtr.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/UniquePtr
)
