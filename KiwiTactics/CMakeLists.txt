set(PNAME KiwiTactics)

# 递归搜索源文件
file(GLOB_RECURSE SRC_FILES
    main.cpp
    game/*.*
    data/*.*
    endian/*.*
    extern/*.*
    plugin/*.*
)

# 为源文件生成源组
source_group(TREE ${CMAKE_SOURCE_DIR}/${PNAME} FILES ${SRC_FILES})

# 包含 Python 和 pybind11 头文件目录
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${PYBIND11_INCLUDE_DIR})

include_directories(${PYBIND11_INCLUDE_DIR})

# 链接 Python 库目录
link_directories(${PYTHON_LIB_DIR})

link_directories(${CMAKE_SOURCE_DIR}/spdlog)

# 创建可执行文件目标
add_executable(${PNAME} ${SRC_FILES})

# 链接 SQLite 库到 KiwiTactics
target_link_libraries(${PNAME} PRIVATE "${CMAKE_SOURCE_DIR}/dll/x64/sqlite3.lib")

# 可选：在构建后复制共享库（如 DLL）到目标输出目录
# add_custom_command(TARGET ${PNAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     "${CMAKE_SOURCE_DIR}/../dll/x64/sqlite3.dll"
#     $<TARGET_FILE_DIR:${PNAME}>
# )