#include <iostream>
#include <sol/sol.hpp>  // 引入 sol2 库

// 定义 C++ 类
class AIModel_Lua {
public:
    std::string model_name;
    int a;  // 新增的 public 成员

    AIModel_Lua(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

void runLua(AIModel_Lua& model, const std::string& script) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);

    // 将 C++ 对象传递给 Lua
    lua.set("model", &model);

    // 注册 AIModel_Lua 类型到 Lua，使得 Lua 可以正确处理 C++ 类
    lua.new_usertype<AIModel_Lua>("AIModel_Lua",
        "train", &AIModel_Lua::train,
        "predict", &AIModel_Lua::predict,
        "a", &AIModel_Lua::a,  // 暴露成员变量
        "model_name", &AIModel_Lua::model_name  // 暴露成员变量
    );

    // 执行 Lua 脚本
    try {
        lua.script_file(script);
        // 在脚本执行后，输出 C++ 对象成员变量 a 的值
        std::cout << "C++ value of 'a' after Lua modification: " << model.a << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error running Lua script: " << e.what() << std::endl;
    }
}


/*
-- script.lua
print("Before modification: " .. model.a)

-- 修改 C++ 对象成员变量 a
model.a = 42

print("After modification: " .. model.a)
*/


int testLua() {
    // 创建 C++ 对象实例
    AIModel_Lua model("AI Model", 10);

    // 输出修改前的 'a'
    std::cout << "Initial value of 'a' in C++: " << model.a << std::endl;

    // 运行 Lua 脚本并传递对象
    runLua(model, "script.lua");

    return 0;
}

int add(int a, int b) {
    return 2 * a + b;
}


void runLuaFromFile(sol::state& lua, const std::string& filename) {
    try {
        lua.script_file(filename);  // 执行 Lua 文件
    }
    catch (const std::exception& e) {
        std::cerr << "Error running Lua script: " << e.what() << std::endl;
    }
}
