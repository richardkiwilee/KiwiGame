cmake_minimum_required(VERSION 3.2)
project(KiwiGameProject VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(PYTHON_LIB_DIR "D:/Python36/libs")
set(PYTHON_INCLUDE_DIR "D:/Python36/include")
set(PYBIND11_INCLUDE_DIR "D:/Python36/Lib/site-packages/pybind11/include")

add_compile_options("/Zi")
add_link_options("/DEBUG:FULL")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(rc_flags "/I 0x809")
set(CMAKE_RC_FLAGS ${rc_flags})

#include_directories(include)
#include_directories(src)

#link_libraries(${KIWITACTICS})

add_subdirectory(KiwiTactics)
add_subdirectory(Demo)