#pragma once
#include <cstdint>
#include <unordered_map>
#include <functional>
#include <pybind11/embed.h>  // pybind11 嵌入 Python 的头文件
#include <pybind11/pybind11.h>
#include "Structs.h"

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
            std::cerr << "ID " << skillId << " not found in SkillMap!" << std::endl;
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
			std::cerr << "Unsupported script file format: " << script_name << std::endl;
		}
	}

private:
	std::unordered_map<int64_t, std::function<double(DamageCalcuteInfo*)>> SkillMap;
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
            std::cerr << "Python interpreter is not initialized!" << std::endl;
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
                std::cout << "Python function '" << func_name << "' registered successfully!" << std::endl;
            }
            else {
                std::cerr << "Function '" << func_name << "' not found or not callable in Python script." << std::endl;
            }
            Py_XDECREF(pFunc);
        }
        else {
            std::cerr << "Failed to load Python script: " << script_name << std::endl;
        }
        Py_XDECREF(pModule);
    }
};