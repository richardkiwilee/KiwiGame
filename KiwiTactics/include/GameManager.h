#pragma once
#include <string>
#include <filesystem>
#include <lua.hpp>
#include <Python.h>
#include "SkillManager.h"
#include "ModuleManager.h"
#include "SQLiteManager.h"
#include "BattleField.h"

// Forward declarations
class GameManager
{
public:
    GameManager();
    ~GameManager();
    void Open(std::string name);
    void Close();
    void Save();
    
private:
    SQLiteManager* database;
    SkillManager* skillmgr;
    ModuleManager* module;
    BattleField* game;

protected:
    lua_State* L;
};
