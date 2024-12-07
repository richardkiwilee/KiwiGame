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

void register_lua_function(lua_State* L, const std::string& func_name) {
    // ȷ�� Lua �������ѳ�ʼ��
    if (!L) {
        std::cerr << "Lua interpreter is not initialized!" << std::endl;
        return;
    }

    // ��ȡ Lua ����
    lua_getglobal(L, func_name.c_str());
    if (lua_isfunction(L, -1)) {
        // �� Lua ������װΪ C++ ����
        A1_dynamic = [L, func_name](int x) {
            // ������ѹջ
            lua_pushnumber(L, x);

            // ���� Lua ����
            if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);  // ������
            }
            };

        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
    }
    else {
        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
    }

    // ����ջ
    lua_pop(L, 1);
}
