#include <iostream>
#include <sol/sol.hpp>  // 引入 sol2 库

// 定义 C++ 类
class AIModel {
public:
    std::string model_name;
    int a;  // 新增的 public 成员

    AIModel(const std::string& name, int value = 0) : model_name(name), a(value) {}

    void train() {
        std::cout << "Training model: " << model_name << std::endl;
    }

    std::string predict(const std::string& input) {
        return "Prediction for '" + input + "' using model: " + model_name;
    }
};

void runLua(AIModel& model, const std::string& script) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);

    // 将 C++ 对象传递给 Lua
    lua.set("model", &model);

    // 执行 Lua 脚本
    try {
        lua.script_file(script);
        // 在脚本执行后，输出 C++ 对象成员变量 a 的值
        std::cout << "C++ value of 'a' after Lua modification: " << model.a << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error running Lua script: " << e.what() << std::endl;
    }
}

int main() {
    // 创建 C++ 对象实例
    AIModel model("AI Model", 10);

    // 输出修改前的 'a'
    std::cout << "Initial value of 'a' in C++: " << model.a << std::endl;

    // 运行 Lua 脚本并传递对象
    runLua(model, "script.lua");

    return 0;
}
