cmake_minimum_required(VERSION 3.9)

#declare project
project(readrope VERSION 0.1 DESCRIPTION "C++ library used to communicate with read rope device and interpret the information coming from it.")

#declare library target
add_library(readrope SHARED
    src/readrope.cpp
)

#set version number for library
set_target_properties(readrope PROPERTIES VERSION 0.1)

#set SO version to major version of project version i.e. 0 of 0.1
set_target_properties(readrope PROPERTIES SOVERSION 0)

#set public API i.e. header file of library
set_target_properties(readrope PROPERTIES PUBLIC_HEADER include/readrope.h)

#set install rule for library
include(GNUInstallDirs)

#add rule to expand @ macros
configure_file(readrope.pc.in readrope.pc @ONLY)

#include src and include directory
target_include_directories(readrope PRIVATE include)
target_include_directories(readrope PRIVATE src)

#declare files to install
install(TARGETS readrope
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#
install(FILES ${CMAKE_BINARY_DIR}/readrope.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
