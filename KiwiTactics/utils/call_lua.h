#include <iostream>
#include <sol/sol.hpp>  // ���� sol2 ��

// ���� C++ ��
class AIModel_Lua {
public:
    std::string model_name;
    int a;  // ������ public ��Ա

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

    // �� C++ ���󴫵ݸ� Lua
    lua.set("model", &model);

    // ע�� AIModel_Lua ���͵� Lua��ʹ�� Lua ������ȷ���� C++ ��
    lua.new_usertype<AIModel_Lua>("AIModel_Lua",
        "train", &AIModel_Lua::train,
        "predict", &AIModel_Lua::predict,
        "a", &AIModel_Lua::a,  // ��¶��Ա����
        "model_name", &AIModel_Lua::model_name  // ��¶��Ա����
    );

    // ִ�� Lua �ű�
    try {
        lua.script_file(script);
        // �ڽű�ִ�к���� C++ �����Ա���� a ��ֵ
        std::cout << "C++ value of 'a' after Lua modification: " << model.a << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error running Lua script: " << e.what() << std::endl;
    }
}


/*
-- script.lua
print("Before modification: " .. model.a)

-- �޸� C++ �����Ա���� a
model.a = 42

print("After modification: " .. model.a)
*/


int testLua() {
    // ���� C++ ����ʵ��
    AIModel_Lua model("AI Model", 10);

    // ����޸�ǰ�� 'a'
    std::cout << "Initial value of 'a' in C++: " << model.a << std::endl;

    // ���� Lua �ű������ݶ���
    runLua(model, "script.lua");

    return 0;
}

int add(int a, int b) {
    return 2 * a + b;
}


void runLuaFromFile(sol::state& lua, const std::string& filename) {
    try {
        lua.script_file(filename);  // ִ�� Lua �ļ�
    }
    catch (const std::exception& e) {
        std::cerr << "Error running Lua script: " << e.what() << std::endl;
    }
}
