#include <sol/sol.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

struct NestedData {
    int a;
    float b;
};

struct ComplexData {
    int id;
    std::string name;
    NestedData nested;
};

void stack_struct(lua_State* L, const ComplexData& data) {
    lua_newtable(L); 

    lua_pushstring(L, "id");
    lua_pushinteger(L, data.id);
    lua_settable(L, -3);

    lua_pushstring(L, "name");
    lua_pushstring(L, data.name.c_str());
    lua_settable(L, -3);

    lua_pushstring(L, "nested");
    {
        lua_newtable(L);

        lua_pushstring(L, "a");
        lua_pushinteger(L, data.nested.a);
        lua_settable(L, -3);

        lua_pushstring(L, "b");
        lua_pushnumber(L, data.nested.b);
        lua_settable(L, -3);

        lua_settable(L, -3);
    }
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    std::unordered_map<int64_t, std::function<double(ComplexData*)>> SkillMap;
    std::string script_name = "register.lua";
    std::string func_name = "WaterBall";
    int64_t id = 100;
    if (!L) {
        std::cerr << "Lua interpreter is not initialized!" << std::endl;
        return 0;
    }
    if (luaL_dofile(L, script_name.c_str()) != LUA_OK) {
        std::cerr << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return 0;
    }
    lua_getglobal(L, func_name.c_str()); // anonymity function at the top of the stack
    if (lua_isfunction(L, -1)) {
        
        SkillMap[id] = [L, func_name](ComplexData* info) -> double {
            stack_struct(L, *info);
            // print table here, values are correct
            if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
                return 0.0;
            }
            double result = 0.0;
            if (lua_isnumber(L, -1)) {
                result = lua_tonumber(L, -1);
            }
            else {
                std::cerr << "Lua function did not return a number!" << std::endl;
            }
            lua_pop(L, 1);
            return result;
            };
        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
    }
    else {
        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
    }
    lua_pop(L, 1);

    ComplexData data = { 1, "example", {10, 3.14f} };

    auto _func1 = SkillMap.find(id)->second;
    double damage1 = _func1(&data);

    lua_close(L);

    std::wcout << damage1 << std::endl;
    return 0;
}