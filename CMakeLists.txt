cmake_minimum_required(VERSION 3.5)
project(KiwiGameProject VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Force Release build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(PYTHON_LIB_DIR "D:/Python36/libs")
set(PYTHON_INCLUDE_DIR "D:/Python36/include")
set(PYBIND11_INCLUDE_DIR "D:/Python36/Lib/site-packages/pybind11/include")
set(LUA_DIR "${CMAKE_SOURCE_DIR}/lua-5.4.2")
set(SOL2_DIR "${CMAKE_SOURCE_DIR}/sol2-3.3.0")
set(KiwiTactics_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/KiwiTactics/include")

# 启用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/KiwiTactics
    ${KiwiTactics_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIR}
    ${PYBIND11_INCLUDE_DIR}
    ${LUA_DIR}/include
    ${SOL2_DIR}/include
)

add_compile_options("/Zi")
add_link_options("/DEBUG:FULL")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTOPRY ${CMAKE_BINARY_DIR}/lib)
set(rc_flags "/I 0x809")
set(CMAKE_RC_FLAGS ${rc_flags})

add_subdirectory(KiwiTactics)
add_subdirectory(Demo)
add_subdirectory(test-lua)