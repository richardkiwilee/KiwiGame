#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <functional>
#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include <sol/sol.hpp>
#include "Logger.h"
#include "CharacterInfo.h"
namespace py = pybind11;

inline bool ends_with(const std::string& script_name, const std::string& suffix) {
    return script_name.size() >= suffix.size() &&
        script_name.compare(script_name.size() - suffix.size(), suffix.size(), suffix) == 0;
};

struct DamageCalcuteInfo
{
    int i;
};


class SkillManager
{
public:
    SkillManager(lua_State* lua_state) : L(lua_state) {
        if (!L) {
            Logger::getInstance().Error("Lua interpreter is not initialized!");
        }
        Py_Initialize();
        if (!Py_IsInitialized()) {
            Logger::getInstance().Error("Python interpreter is not initialized!");
        }
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.')");
    }
    ~SkillManager() {
        Logger::getInstance().Info("Lua interpreter closed.");
        Py_Finalize();
        Logger::getInstance().Info("Python interpreter closed.");        
    }
    void Set(int64_t skillId, std::function<double(DamageCalcuteInfo*)> func) {
        SkillMap[skillId] = func;
    }	
    void Register(lua_State* L, int64_t id, const std::string& script_name, const std::string& func_name) {
        	if (ends_with(script_name, ".lua")) {
 			// Register_lua(L, id, script_name, func_name);
 		}
 		else if (ends_with(script_name, ".py")) {
 			Register_py(id, script_name, func_name);
 		}
 		else {
             Logger::getInstance().Error("Unsupported script file format: " + script_name);
 		}
 	}
    void Register_py(int64_t id, const std::string& script_name, const std::string& func_name) {
         if (!Py_IsInitialized()) {
             Logger::getInstance().Error("Python interpreter is not initialized!");
             return;
         }
 
         std::string module_name = script_name.substr(0, script_name.find_last_of('.'));
 
         PyObject* pName = PyUnicode_DecodeFSDefault(module_name.c_str());
         PyObject* pModule = PyImport_Import(pName);
         Py_XDECREF(pName);
 
         if (pModule) {
             PyObject* pFunc = PyObject_GetAttrString(pModule, func_name.c_str());
 
             if (pFunc && PyCallable_Check(pFunc)) {
                 // 显式捕获 `this`
                 SkillMap[id] = [this, pFunc](DamageCalcuteInfo* x) {
                     // 使用辅助函数将 DamageCalcuteInfo 转换为 Python 字典
                     PyObject* damage_info; //= convert_damage_info_to_py(x);
                     // 将 damage_info 封装成一个元组作为参数
                     PyObject* args = PyTuple_Pack(1, damage_info);
                     // 调用 Python 函数
                     PyObject* result = PyObject_CallObject(pFunc, args);
                     double ret = 0.0;
                     if (result && PyFloat_Check(result)) {
                         ret = PyFloat_AsDouble(result);  // 转换为 double 类型
                     }
                     else {
                         PyErr_Print();  // 如果返回值无效，则打印错误信息
                     }
                     // 清理 Python 对象
                     Py_XDECREF(result);
                     Py_XDECREF(args);
                     Py_XDECREF(damage_info);  // 释放 damage_info
                     return ret;
                     };
                 Logger::getInstance().Info("Python function  '" + func_name + "' registered successfully!");
             }
             else {
                 Logger::getInstance().Error("Function '" + func_name + "' not found or not callable in Python script.");
             }
             Py_XDECREF(pFunc);
         }
         else {
             Logger::getInstance().Error("Failed to load Python script: " + script_name );
         }
         Py_XDECREF(pModule);
     }    
    void Register_lua(lua_State* L, int64_t id, const std::string& script_name, const std::string& func_name)
     {
         if (!L) {
             Logger::getInstance().Error("Lua interpreter is not initialized!");
         }
         if (luaL_dofile(L, script_name.c_str()) != LUA_OK) {
             Logger::getInstance().Error("Error loading Lua script: " + std::string(lua_tostring(L, -1)));
             lua_pop(L, 1);
         }
         lua_getglobal(L, func_name.c_str()); // anonymity function at the top of the stack
         if (lua_isfunction(L, -1)) {
             int func = luaL_ref(L, LUA_REGISTRYINDEX);
             SkillMap[id] = [L, func](DamageCalcuteInfo* info) -> double {
                 lua_rawgeti(L, LUA_REGISTRYINDEX, func); // get function
                 // push_damage_info_to_lua_(L, info);
                 if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
                     Logger::getInstance().Error("Error calling Lua function: " + std::string(lua_tostring(L, -1)));
                     lua_pop(L, 1);
                     return 0.0;
                 }
                 double result = 0.0;
                 if (lua_isnumber(L, -1)) {
                     result = lua_tonumber(L, -1);
                 }
                 else {
                     Logger::getInstance().Error("Lua function did not return a number!");
                 }
                 lua_pop(L, 1);
                 return result;
 
                 };
             Logger::getInstance().Info("Lua function  '" + func_name + "' registered successfully!");
         }
         else {
             Logger::getInstance().Error("Function '" + func_name + "' not found or not callable in Lua script.");
         }
     };
 
    std::function<double(DamageCalcuteInfo*)> Get(int64_t skillId) {
        return SkillMap[skillId];
    };


private:
    lua_State* L;
    PyObject* pModule;
    std::unordered_map<int64_t, std::function<double(DamageCalcuteInfo*)>> SkillMap;
};