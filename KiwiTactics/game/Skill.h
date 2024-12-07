#pragma once
#include <cstdint>
#include <unordered_map>
#include <functional>
#include <sol/sol.hpp>		// lua ��ͷ�ļ�
#include <pybind11/embed.h>  // pybind11 Ƕ�� Python ��ͷ�ļ�
#include <pybind11/pybind11.h>
#include "Structs.h"
#include <format>

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
			Register_lua(L, id, script_name, func_name);
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

        // �� Relative ��ӵ��ֵ���
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
                // ��ʽ���� `this`
                SkillMap[id] = [this, pFunc](DamageCalcuteInfo* x) {
                    // ʹ�ø��������� DamageCalcuteInfo ת��Ϊ Python �ֵ�
                    PyObject* damage_info = convert_damage_info_to_py(x);
                    // �� damage_info ��װ��һ��Ԫ����Ϊ����
                    PyObject* args = PyTuple_Pack(1, damage_info);
                    // ���� Python ����
                    PyObject* result = PyObject_CallObject(pFunc, args);
                    double ret = 0.0;
                    if (result && PyFloat_Check(result)) {
                        ret = PyFloat_AsDouble(result);  // ת��Ϊ double ����
                    }
                    else {
                        PyErr_Print();  // �������ֵ��Ч�����ӡ������Ϣ
                    }
                    // ���� Python ����
                    Py_XDECREF(result);
                    Py_XDECREF(args);
                    Py_XDECREF(damage_info);  // �ͷ� damage_info
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
    void push_CharacterInfo_to_lua(lua_State* L, CharacterInfo* info, std::string name)
    {
        // Push Attacker to Lua table
        lua_pushstring(L, name.c_str());
        lua_newtable(L);  // ���� Attacker ��
        std::cout << "Pushed "<< name <<" table" << std::endl;
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

        lua_settable(L, -3);  // �� Attacker ����� DamageCalcuteInfo ��
        std::cout << "Pushed " << name << " to DamageCalcuteInfo table" << std::endl;

    }
    void push_SpatialRelationship_to_lua(lua_State* L, SpatialRelationship* info, std::string name)
    {
        // �� Relative ת��Ϊ Lua ��
        lua_pushstring(L, name.c_str());
        lua_newtable(L);  // ���� Relative ��

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

        lua_settable(L, -3);
    }
    void push_damage_info_to_lua(lua_State* L, DamageCalcuteInfo* info) {
        // ����һ���µı�����ʾ DamageCalcuteInfo
        lua_newtable(L);
        push_CharacterInfo_to_lua(L, &info->Attacker, "Attacker");
        push_CharacterInfo_to_lua(L, &info->Defender, "Defender");
        push_SpatialRelationship_to_lua(L, &info->Relative, "Relative");
        // lua_settable(L, -3);  // �� Relative ����� DamageCalcuteInfo ��
    }
    // ���ڵݹ�ش�ӡ���ĺ���
    void print_table(lua_State* L, int index, int depth) {
        lua_pushnil(L);  // �����еĵ�һ��Ԫ��ѹջ
        while (lua_next(L, index) != 0) {
            // ��ӡ������������ȣ�
            for (int i = 0; i < depth; ++i) {
                std::cout << "  ";  // �����Ӿ�����
            }

            // �����
            int t = lua_type(L, -2);
            if (t == LUA_TSTRING) {
                std::cout << "Key: " << lua_tostring(L, -2) << " -> ";
            }
            else {
                std::cout << "Key (non-string) -> ";
            }

            // ���ֵ
            t = lua_type(L, -1);
            switch (t) {
            case LUA_TSTRING:
                std::cout << "(string) " << lua_tostring(L, -1) << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << "(boolean) " << (lua_toboolean(L, -1) ? "true" : "false") << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << "(number) " << lua_tonumber(L, -1) << std::endl;
                break;
            case LUA_TTABLE:
                std::cout << "(table) {" << std::endl;
                // �ݹ���ã��������
                print_table(L, lua_gettop(L), depth + 1);
                for (int i = 0; i < depth; ++i) {
                    std::cout << "  ";  // ���ڽ����ݹ������
                }
                std::cout << "}" << std::endl;
                break;
            default:
                std::cout << "(unknown type)" << std::endl;
                break;
            }

            lua_pop(L, 1);  // ������ǰֵ��������һ����
        }
    }

    void print_lua_stack(lua_State* L) {
        int stackTop = lua_gettop(L);  // ��ȡջ��������
        for (int i = 1; i <= stackTop; ++i) {
            int t = lua_type(L, i);
            switch (t) {
            case LUA_TSTRING:  // �ַ���
                std::cout << "Stack[" << i << "]: (string) " << lua_tostring(L, i) << std::endl;
                break;
            case LUA_TBOOLEAN:  // ����ֵ
                std::cout << "Stack[" << i << "]: (boolean) " << (lua_toboolean(L, i) ? "true" : "false") << std::endl;
                break;
            case LUA_TNUMBER:  // ����
                std::cout << "Stack[" << i << "]: (number) " << lua_tonumber(L, i) << std::endl;
                break;
            case LUA_TTABLE:  // ��
                std::cout << "Stack[" << i << "]: (table) {" << std::endl;
                print_table(L, i, 1);  // ���õݹ��ӡ��������ʼ���Ϊ1
                std::cout << "}" << std::endl;
                break;
            default:
                std::cout << "Stack[" << i << "]: (unknown type)" << std::endl;
                break;
            }
        }
    }
    void Register_lua(lua_State* L, int64_t id, const std::string& script_name, const std::string& func_name) {
        if (!L) {
            std::cerr << "Lua interpreter is not initialized!" << std::endl;
            return;
        }
        if (luaL_dofile(L, script_name.c_str()) != LUA_OK) {
            std::cerr << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
            return;
        }
        lua_getglobal(L, func_name.c_str());
        if (lua_isfunction(L, -1)) {
            SkillMap[id] = [L, func_name, this](DamageCalcuteInfo* info) -> double {
                // �� DamageCalcuteInfo ת�������͵� Lua ջ
                push_damage_info_to_lua(L, info);
                // print_lua_stack(L);
                // ���� Lua ����
                if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
                    std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
                    lua_pop(L, 1);  // ����������Ϣ
                    return 0.0;  // �����������Ĭ��ֵ
                }

                // ��ȡ Lua �����ķ���ֵ����������һ�����֣�
                double result = 0.0;
                if (lua_isnumber(L, -1)) {
                    result = lua_tonumber(L, -1);  // ��ȡ���ص�����ֵ
                }
                else {
                    std::cerr << "Lua function did not return a number!" << std::endl;
                }

                // ���� Lua ջ
                lua_pop(L, 1);  // ��������ֵ

                return result;
                };

            std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
        }
        else {
            std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
        }
        lua_pop(L, 1);
    }

};