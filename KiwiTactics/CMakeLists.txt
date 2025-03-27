set(PNAME KiwiTactics)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
else()
    set(ARCH_DIR "x86")
endif() 

# 递归搜索源文件
file(GLOB_RECURSE SRC_FILES 
    main.cpp 
    version.h 
    data/*.*
    endian/*.*
    plugin/*.*
    include/*.h
    src/*.*
) 

# 为源文件生成源组
source_group(TREE ${CMAKE_SOURCE_DIR}/${PNAME} FILES ${SRC_FILES})

# 包含 Python 和 pybind11 头文件目录
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${PYBIND11_INCLUDE_DIR})
include_directories("${SOL2_DIR}/include")
include_directories("${LUA_DIR}/include")
include_directories(${KiwiTactics_INCLUDE_DIR})

# 这地方让根目录可以被系统include找到
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}")


# 链接 Python 库目录
link_directories(${PYTHON_LIB_DIR})


# 创建可执行文件目标
add_executable(${PNAME} ${SRC_FILES})

# 排除不需要的CRT库
target_link_options(${PNAME} PRIVATE /NODEFAULTLIB:LIBCMT)

# 链接 SQLite 库到 KiwiTactics
target_link_libraries(${PNAME} PRIVATE "${CMAKE_SOURCE_DIR}/dll/x64/sqlite3.lib")
target_link_libraries(${PNAME} PRIVATE "${LUA_DIR}/lua54.lib")

set_target_properties(${PNAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PNAME}>"
)

# 可选：在构建后复制共享库（如 DLL）到目标输出目录
add_custom_command(TARGET ${PNAME} POST_BUILD
    # 打印即将执行的命令
    COMMAND ${CMAKE_COMMAND} -E echo "Copying sqlite3.dll from: ${CMAKE_SOURCE_DIR}/dll/${ARCH_DIR}/sqlite3.dll to: $<TARGET_FILE_DIR:${PNAME}>/sqlite3.dll"
    
    # 执行复制命令，确保路径格式正确
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/dll/${ARCH_DIR}/sqlite3.dll"
    "$<TARGET_FILE_DIR:${PNAME}>/sqlite3.dll"

    COMMAND ${CMAKE_COMMAND} -E echo "Copying sqlite3.lib from: ${CMAKE_SOURCE_DIR}/dll/${ARCH_DIR}/sqlite3.lib to: $<TARGET_FILE_DIR:${PNAME}>/sqlite3.lib"
    
    # 执行复制命令，确保路径格式正确
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/dll/${ARCH_DIR}/sqlite3.lib"
    "$<TARGET_FILE_DIR:${PNAME}>/sqlite3.lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Database
        $<TARGET_FILE_DIR:${PNAME}>/Database

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Data
        $<TARGET_FILE_DIR:${PNAME}>/Data

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Mods
        $<TARGET_FILE_DIR:${PNAME}>/Mods

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/scripts/register.py"
    "$<TARGET_FILE_DIR:${PNAME}>/register.py"

)
