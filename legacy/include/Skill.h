#pragma once
#include <cstdint>
#include <unordered_map>
#include <functional>
#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include <sol/sol.hpp>
#include "Structs.h"
#include "Logger.h"
namespace py = pybind11;

const int8_t DAMAGE_TYPE_PHYSICAL = 1;
const int8_t DAMAGE_TYPE_MAGICAL = 2;
const int8_t DAMAGE_TYPE_PURE = 3;
const int8_t DAMAGE_TYPE_HEAL = 4;

const int8_t BUFF_TYPE_BUFF = 1;
const int8_t BUFF_TYPE_DEBUFF = 2;
const int8_t BUFF_TYPE_BOOST = 3;
const int8_t BUFF_TYPE_RESIST_BOOST = 4;



inline bool ends_with(const std::string& script_name, const std::string& suffix) {
    return script_name.size() >= suffix.size() &&
        script_name.compare(script_name.size() - suffix.size(), suffix.size(), suffix) == 0;
}

double _defaultSkill(DamageCalcuteInfo* info) {
	return 0.0;
}

inline void push_CharacterInfo_to_lua(lua_State* L, CharacterInfo* info, std::string name)
{
    // Push Attacker to Lua table
    lua_pushstring(L, name.c_str());
    lua_newtable(L);  // 创建 Attacker 表
    std::cout << "Pushed " << name << " table" << std::endl;
    lua_pushstring(L, "id");
    lua_pushinteger(L, info->id);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".id: " << info->id << std::endl;

    lua_pushstring(L, "position_x");
    lua_pushinteger(L, info->position_x);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".position_x: " << info->position_x << std::endl;

    lua_pushstring(L, "position_y");
    lua_pushinteger(L, info->position_y);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".position_y: " << info->position_y << std::endl;

    lua_pushstring(L, "position_height");
    lua_pushinteger(L, info->position_height);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".position_height: " << info->position_height << std::endl;

    lua_pushstring(L, "direction");
    lua_pushinteger(L, info->direction);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".direction: " << info->direction << std::endl;

    lua_pushstring(L, "MaxHealth");
    lua_pushinteger(L, info->MaxHealth);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MaxHealth: " << info->MaxHealth << std::endl;

    lua_pushstring(L, "Health");
    lua_pushinteger(L, info->Health);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Health: " << info->Health << std::endl;

    lua_pushstring(L, "MaxMana");
    lua_pushinteger(L, info->MaxMana);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MaxMana: " << info->MaxMana << std::endl;

    lua_pushstring(L, "Mana");
    lua_pushinteger(L, info->Mana);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Mana: " << info->Mana << std::endl;

    lua_pushstring(L, "MaxArmor");
    lua_pushinteger(L, info->MaxArmor);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MaxArmor: " << info->MaxArmor << std::endl;

    lua_pushstring(L, "Armor");
    lua_pushinteger(L, info->Armor);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Armor: " << info->Armor << std::endl;

    lua_pushstring(L, "MaxActionPoint");
    lua_pushinteger(L, info->MaxActionPoint);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MaxActionPoint: " << info->MaxActionPoint << std::endl;

    lua_pushstring(L, "ActionPoint");
    lua_pushinteger(L, info->ActionPoint);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".ActionPoint: " << info->ActionPoint << std::endl;

    lua_pushstring(L, "MaxMovement");
    lua_pushinteger(L, info->MaxMovement);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MaxMovement: " << info->MaxMovement << std::endl;

    lua_pushstring(L, "Movement");
    lua_pushinteger(L, info->Movement);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Movement: " << info->Movement << std::endl;

    lua_pushstring(L, "Strength");
    lua_pushinteger(L, info->Strength);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Strength: " << info->Strength << std::endl;

    lua_pushstring(L, "PhyDef");
    lua_pushinteger(L, info->PhyDef);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".PhyDef: " << info->PhyDef << std::endl;

    lua_pushstring(L, "Intelligence");
    lua_pushinteger(L, info->Intelligence);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Intelligence: " << info->Intelligence << std::endl;

    lua_pushstring(L, "MagDef");
    lua_pushinteger(L, info->MagDef);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".MagDef: " << info->MagDef << std::endl;

    lua_pushstring(L, "Dexterity");
    lua_pushinteger(L, info->Dexterity);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Dexterity: " << info->Dexterity << std::endl;

    lua_pushstring(L, "CriticalRate");
    lua_pushinteger(L, info->CriticalRate);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".CriticalRate: " << info->CriticalRate << std::endl;

    lua_pushstring(L, "CriticalStrength");
    lua_pushinteger(L, info->CriticalStrengh);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".CriticalStrength: " << info->CriticalStrengh << std::endl;

    lua_pushstring(L, "Luck");
    lua_pushinteger(L, info->Luck);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Luck: " << info->Luck << std::endl;

    lua_pushstring(L, "Will");
    lua_pushinteger(L, info->Will);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Will: " << info->Will << std::endl;

    lua_pushstring(L, "HitRate");
    lua_pushinteger(L, info->HitRate);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".HitRate: " << info->HitRate << std::endl;

    lua_pushstring(L, "Evasion");
    lua_pushinteger(L, info->Evasion);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Evasion: " << info->Evasion << std::endl;

    lua_pushstring(L, "Jump");
    lua_pushinteger(L, info->Jump);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".Jump: " << info->Jump << std::endl;

    lua_settable(L, -3);  // 将 Attacker 表插入 DamageCalcuteInfo 表
    std::cout << "Pushed " << name << " to DamageCalcuteInfo table" << std::endl;

}
inline void push_SpatialRelationship_to_lua(lua_State* L, SpatialRelationship* info, std::string name)
{
    // 将 Relative 转换为 Lua 表
    lua_pushstring(L, name.c_str());
    lua_newtable(L);  // 创建 Relative 表

    lua_pushstring(L, "inSight");
    lua_pushboolean(L, info->inSight);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".inSight: " << info->inSight << std::endl;
    lua_pushstring(L, "inAttackRange");
    lua_pushboolean(L, info->inAttackRange);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".inAttackRange: " << info->inAttackRange << std::endl;
    lua_pushstring(L, "isBackStrike");
    lua_pushboolean(L, info->isBackStrike);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".isBackStrike: " << info->isBackStrike << std::endl;
    lua_pushstring(L, "isSideStrike");
    lua_pushboolean(L, info->isSideStrike);
    lua_settable(L, -3);
    std::cout << "Pushed " << name << ".isSideStrike: " << info->isSideStrike << std::endl;

    // lua_settable(L, -3);
}
inline void push_damage_info_to_lua_(lua_State* L, DamageCalcuteInfo* info) {
    // 创建一个新的表来表示 DamageCalcuteInfo
    lua_newtable(L);
    push_CharacterInfo_to_lua(L, &info->Attacker, "Attacker");
    push_CharacterInfo_to_lua(L, &info->Defender, "Defender");
    push_SpatialRelationship_to_lua(L, &info->Relative, "Relative");
    // lua_settable(L, -1);    // Lua after push info: 1
    // lua_settable(L, -2);    // crash
    lua_settable(L, -3);    // Lua after push info: 1 栈顶table
    // lua_settable(L, -4);    // crash
}


class SkillManager
{
public:
	SkillManager() {
	}
	void Set(int64_t skillId, std::function<double(DamageCalcuteInfo*)> func) {
		SkillMap[skillId] = func;
	}	

	std::function<double(DamageCalcuteInfo*)> Get(int64_t skillId) {
        auto it = SkillMap.find(skillId);
        if (it != SkillMap.end()) {
            return SkillMap[skillId];
        }
        else {
            Logger::getInstance().Error("ID " + std::to_string(skillId) + " not found in SkillMap.");
            return _defaultSkill;
        }
        return SkillMap[skillId];
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
    void RegisterFromVector(lua_State* L, std::vector<int64_t> skillid, std::vector<std::string> script, std::vector<std::string> func) {
        auto ids = skillid.begin();
        auto scripts = script.begin();
        auto funcs = func.begin();
        while (ids != skillid.end() && scripts != script.end() && funcs != func.end()) {
            Register(L, *ids, *scripts, *funcs);
            ++ids;
            ++scripts;
            ++funcs;
        }
    }

private:
	std::unordered_map<int64_t, std::function<double(DamageCalcuteInfo*)>> SkillMap;
	std::unordered_map<int64_t, SkillInfo*> SkillInformation;
    PyObject* convert_damage_info_to_py(DamageCalcuteInfo* info) {
        PyObject* damage_info = PyDict_New();
        PyObject* attacker = PyDict_New();
        PyDict_SetItemString(attacker, "id", PyLong_FromLong(info->Attacker.id));
        PyDict_SetItemString(attacker, "position_x", PyLong_FromLong(info->Attacker.position_x));
        PyDict_SetItemString(attacker, "position_y", PyLong_FromLong(info->Attacker.position_y));
        PyDict_SetItemString(attacker, "position_height", PyLong_FromLong(info->Attacker.position_height));
        PyDict_SetItemString(attacker, "direction", PyLong_FromLong(info->Attacker.direction));
        PyDict_SetItemString(attacker, "MaxHealth", PyLong_FromLong(info->Attacker.MaxHealth));
        PyDict_SetItemString(attacker, "Health", PyLong_FromLong(info->Attacker.Health));
        PyDict_SetItemString(attacker, "MaxMana", PyLong_FromLong(info->Attacker.MaxMana));
        PyDict_SetItemString(attacker, "Mana", PyLong_FromLong(info->Attacker.Mana));
        PyDict_SetItemString(attacker, "MaxArmor", PyLong_FromLong(info->Attacker.MaxArmor));
        PyDict_SetItemString(attacker, "Armor", PyLong_FromLong(info->Attacker.Armor));
        PyDict_SetItemString(attacker, "MaxActionPoint", PyLong_FromLong(info->Attacker.MaxActionPoint));
        PyDict_SetItemString(attacker, "ActionPoint", PyLong_FromLong(info->Attacker.ActionPoint));
        PyDict_SetItemString(attacker, "MaxMovement", PyLong_FromLong(info->Attacker.MaxMovement));
        PyDict_SetItemString(attacker, "Movement", PyLong_FromLong(info->Attacker.Movement));
        PyDict_SetItemString(attacker, "Strength", PyLong_FromLong(info->Attacker.Strength));
        PyDict_SetItemString(attacker, "PhyDef", PyLong_FromLong(info->Attacker.PhyDef));
        PyDict_SetItemString(attacker, "Intelligence", PyLong_FromLong(info->Attacker.Intelligence));
        PyDict_SetItemString(attacker, "MagDef", PyLong_FromLong(info->Attacker.MagDef));
        PyDict_SetItemString(attacker, "Dexterity", PyLong_FromLong(info->Attacker.Dexterity));
        PyDict_SetItemString(attacker, "CriticalRate", PyLong_FromLong(info->Attacker.CriticalRate));
        PyDict_SetItemString(attacker, "CriticalStrength", PyLong_FromLong(info->Attacker.CriticalStrengh));
        PyDict_SetItemString(attacker, "Luck", PyLong_FromLong(info->Attacker.Luck));
        PyDict_SetItemString(attacker, "Will", PyLong_FromLong(info->Attacker.Will));
        PyDict_SetItemString(attacker, "HitRate", PyLong_FromLong(info->Attacker.HitRate));
        PyDict_SetItemString(attacker, "Evasion", PyLong_FromLong(info->Attacker.Evasion));
        PyDict_SetItemString(attacker, "Jump", PyLong_FromLong(info->Attacker.Jump));
        PyDict_SetItemString(damage_info, "Attacker", attacker);
        Py_XDECREF(attacker);
        PyObject* defender = PyDict_New();
        PyDict_SetItemString(defender, "id", PyLong_FromLong(info->Defender.id));
        PyDict_SetItemString(defender, "position_x", PyLong_FromLong(info->Defender.position_x));
        PyDict_SetItemString(defender, "position_y", PyLong_FromLong(info->Defender.position_y));
        PyDict_SetItemString(defender, "position_height", PyLong_FromLong(info->Defender.position_height));
        PyDict_SetItemString(defender, "direction", PyLong_FromLong(info->Defender.direction));
        PyDict_SetItemString(defender, "MaxHealth", PyLong_FromLong(info->Defender.MaxHealth));
        PyDict_SetItemString(defender, "Health", PyLong_FromLong(info->Defender.Health));
        PyDict_SetItemString(defender, "MaxMana", PyLong_FromLong(info->Defender.MaxMana));
        PyDict_SetItemString(defender, "Mana", PyLong_FromLong(info->Defender.Mana));
        PyDict_SetItemString(defender, "MaxArmor", PyLong_FromLong(info->Defender.MaxArmor));
        PyDict_SetItemString(defender, "Armor", PyLong_FromLong(info->Defender.Armor));
        PyDict_SetItemString(defender, "MaxActionPoint", PyLong_FromLong(info->Defender.MaxActionPoint));
        PyDict_SetItemString(defender, "ActionPoint", PyLong_FromLong(info->Defender.ActionPoint));
        PyDict_SetItemString(defender, "MaxMovement", PyLong_FromLong(info->Defender.MaxMovement));
        PyDict_SetItemString(defender, "Movement", PyLong_FromLong(info->Defender.Movement));
        PyDict_SetItemString(defender, "Strength", PyLong_FromLong(info->Defender.Strength));
        PyDict_SetItemString(defender, "PhyDef", PyLong_FromLong(info->Defender.PhyDef));
        PyDict_SetItemString(defender, "Intelligence", PyLong_FromLong(info->Defender.Intelligence));
        PyDict_SetItemString(defender, "MagDef", PyLong_FromLong(info->Defender.MagDef));
        PyDict_SetItemString(defender, "Dexterity", PyLong_FromLong(info->Defender.Dexterity));
        PyDict_SetItemString(defender, "CriticalRate", PyLong_FromLong(info->Defender.CriticalRate));
        PyDict_SetItemString(defender, "CriticalStrength", PyLong_FromLong(info->Defender.CriticalStrengh));
        PyDict_SetItemString(defender, "Luck", PyLong_FromLong(info->Defender.Luck));
        PyDict_SetItemString(defender, "Will", PyLong_FromLong(info->Defender.Will));
        PyDict_SetItemString(defender, "HitRate", PyLong_FromLong(info->Defender.HitRate));
        PyDict_SetItemString(defender, "Evasion", PyLong_FromLong(info->Defender.Evasion));
        PyDict_SetItemString(defender, "Jump", PyLong_FromLong(info->Defender.Jump));
        PyDict_SetItemString(damage_info, "Defender", defender);
        Py_XDECREF(defender);

        // 将 Relative 添加到字典中
        PyObject* relative = PyDict_New();
        PyDict_SetItemString(relative, "inSight", PyBool_FromLong(info->Relative.inSight));
        PyDict_SetItemString(relative, "inAttackRange", PyBool_FromLong(info->Relative.inAttackRange));
        PyDict_SetItemString(relative, "isBackStrike", PyBool_FromLong(info->Relative.isBackStrike));
        PyDict_SetItemString(relative, "isSideStrike", PyBool_FromLong(info->Relative.isSideStrike));
        PyDict_SetItemString(damage_info, "Relative", relative);
        Py_XDECREF(relative);
        return damage_info;
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
                    PyObject* damage_info = convert_damage_info_to_py(x);
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
                push_damage_info_to_lua_(L, info);
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
};
