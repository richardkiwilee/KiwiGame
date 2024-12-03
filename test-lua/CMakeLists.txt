cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(AIModelLuaIntegration VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)


# 设置 Sol2 库的本地路径
#set(SOL2_DIR "D:/sol2-3.3.0")
set(LUA_DIR "D:/lua-5.4.2")

# 设置 Sol2 库路径
include_directories("D:/sol2-3.3.0/include")
# include_directories("${LUA_DIR}/include")
include_directories(D:/lua-5.4.7/src)

# 设置源文件
set(SOURCE_FILES
    main.cpp
)

# 添加可执行文件
add_executable(AIModelLuaIntegration ${SOURCE_FILES})

# 链接 Lua 库
target_link_libraries(AIModelLuaIntegration PRIVATE ${LUA_LIBRARIES})

# 如果 Lua 库需要链接特定的依赖，手动添加链接
target_link_libraries(AIModelLuaIntegration PRIVATE "D:/lua-5.4.2/lua54.lib")

# 链接 Sol2 库
#target_link_libraries(AIModelLuaIntegration PRIVATE "${SOL2_DIR}/lib/sol2.lib")

# 包含 Lua 头文件
target_include_directories(AIModelLuaIntegration PRIVATE ${LUA_INCLUDE_DIR})

