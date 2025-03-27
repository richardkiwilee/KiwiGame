#include "GameManager.h"
#include "Logger.h"
#include "SQLiteManager.h"
#include "version.h"
#include "ModuleManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include <sol/sol.hpp>
#include <filesystem>

GameManager::GameManager()
{
    Logger::getInstance().Info("SYSTEM start.");
    L = luaL_newstate();
    luaL_openlibs(L);
    if (!L) {
        Logger::getInstance().Error("Lua interpreter is not initialized!");
    }
    Py_Initialize();
    if (!Py_IsInitialized()) {
        Logger::getInstance().Error("Python interpreter is not initialized!");
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");
    database = &SQLiteManager::getInstance();
    database->loadDatabase("Database\\data.db");
    for (const auto& entry : fs::recursive_directory_iterator("Data")) {
        if (entry.is_directory()) {
            database->executeFolder(entry.path().string());
        }
    }
    module = new ModuleManager("Mods");
    for (const auto& entry : fs::recursive_directory_iterator("Mods")) {
        if (entry.is_directory()) {
            database->executeFolder(entry.path().string());
        }
    }
    std::vector<std::vector<std::string>> result;
    std::string query = "SELECT * FROM Skill";
    if (database->executeSelectQuery(query, result)) {
        for (const auto& row : result) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    // skillmgr = new SkillManager(L);
    // skillmgr->Register(nullptr, 1, "register.py", "FireBall");
}

GameManager::~GameManager()
{
    lua_close(L);
    Logger::getInstance().Info("Lua interpreter closed.");
    Py_Finalize();
    Logger::getInstance().Info("Python interpreter closed.");        
}

void GameManager::Open(std::string name)
{
    if (!fs::exists("Saves")) {
        if (fs::create_directory("Saves")) {
            Logger::getInstance().Info("Create Saves folder success.");
        }
        else {
            Logger::getInstance().Error("Fail to create Saves folder.");
        }
    }
    if (game == nullptr)
    {
        Logger::getInstance().InitArchiveLogger(name);
        game = new BattleField("Saves/" + name + ".sav");
    }
}

void GameManager::Close()
{
    delete game;
    game = nullptr;
    Logger::getInstance().CloseArchiveLogger();
}

void GameManager::Save()
{
    if (game != nullptr)
        game->Save();
}
