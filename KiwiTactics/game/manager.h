#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include <sol/sol.hpp>      // lua依赖
#include "extern/Logger.h"
#include "data/SQLiteManager.h"
#include "QuadMap.h"
#include "Character.h"
#include "Building.h"
#include "RandomSeed.h"
#include "Inventory.h"
#include "../version.h"
#include "../extern/ModuleManager.h"
#include "Skill.h"

template <typename T>
class ObjectsManager
{
public:
    ObjectsManager() {};
    ~ObjectsManager() {
        // 清理动态分配的内存
        for (auto& pair : _class) {
            delete pair.second;
        }
    }

    void Serialize(std::ofstream& ofs) {
        int8_t size = static_cast<int8_t>(_class.size());
        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (auto iter = _class.begin(); iter != _class.end(); ++iter) {
            iter->second->Serialize(ofs);
        }
    }

    void Deserialize(std::ifstream& ifs) {
        int8_t size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (int i = 0; i < size; ++i) {
            T* t = new T();
            t->Deserialize(ifs); 
            _class[t->id] = t;
        }
    }

private:
    std::unordered_map<int64_t, T*> _class;
};


class ArchiveManager
{
public:
    std::string opened_sav;
    ArchiveManager()
    {
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

        skillmgr->Register(nullptr, 1, "register.py", "FireBall");

        return;
            
    };
    ~ArchiveManager()
    {
        lua_close(L);
        Logger::getInstance().Info("Lua interpreter closed.");
        Py_Finalize();
        Logger::getInstance().Info("Python interpreter closed.");        
    };
    void New(std::string name)
    {
        opened_sav = name;
        randomBuffer = new RandomSeed(255);
        inventory = new Inventory();
        buildings = new ObjectsManager<Building>();
        alias = new ObjectsManager<Character>();
        neutrals = new ObjectsManager<Character>();
        emeries = new ObjectsManager<Character>();
        int64_t seed = randomBuffer->GetInt64();
        map = new QuadGridMap(1, 50, 50, seed);        
        this->Save();
    };
    void Open(std::string name)
	{
        if (opened_sav != "") {
            Logger::getInstance().Warn("Open fail, no file name given.");
            return;
		}
		opened_sav = name;
        this->Deserialize(opened_sav);
	};
    void Close()
    {
        delete map; map = nullptr;
        delete inventory; inventory = nullptr;
        delete alias; alias = nullptr;
        delete neutrals; neutrals = nullptr;
        delete emeries; emeries = nullptr;
        delete buildings; buildings = nullptr;
        delete randomBuffer; randomBuffer = nullptr;
        opened_sav = "";
    };
    void Save()
	{
        if (opened_sav == "") {
            Logger::getInstance().Warn("No sav opened.");
			return;
		}
		this->Serialize(opened_sav);
	};
    SQLiteManager* database = nullptr;
    SkillManager* skillmgr = nullptr;
    ModuleManager* module = nullptr;
	QuadGridMap* map = nullptr;
    Inventory* inventory = nullptr;
    ObjectsManager<Character>* alias = nullptr;
    ObjectsManager<Character>* neutrals = nullptr;
    ObjectsManager<Character>* emeries = nullptr;
    ObjectsManager<Building>* buildings = nullptr;
    RandomSeed* randomBuffer = nullptr;
    lua_State* L = nullptr;
private:
    void Serialize() {
        Serialize(opened_sav);
    };

    void Serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            Logger::getInstance().Error("Failed to open file for serialization.");
            return;
        }
        // 序列化版本和名称
        ofs.write(VERSION.data(), VERSION.size()); ofs.put('\0');
        ofs.write(opened_sav.data(), opened_sav.size()); ofs.put('\0');
        // 序列化mod列表
        module->Serialize(ofs);
        // 序列化 RandomBuffer 的数据
        randomBuffer->Serialize(ofs);
        // 序列化地图数据
        map->Serialize(ofs);
        // 序列化物品数据
        inventory->Serialize(ofs);
        // 序列化建筑数据
        buildings->Serialize(ofs);
        // 序列化友方数据
        alias->Serialize(ofs);
        // 序列化中立单位数据
        neutrals->Serialize(ofs);
        // 序列化敌方数据
        emeries->Serialize(ofs);
        ofs.close();
        Logger::getInstance().Info("Serialization successful.");
    };

    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            Logger::getInstance().Error("Failed to open file for deserialization.");
            return;
        }
        // 反序列化版本和名称
        std::getline(ifs, VERSION, '\0');  // 读取直至 null terminator
        std::getline(ifs, opened_sav, '\0');     // 读取直至 null terminator

        module->Deserialize(ifs);
        randomBuffer->Deserialize(ifs);
        map->Deserialize(ifs);
        inventory->Deserialize(ifs);
        buildings->Deserialize(ifs);
        alias->Deserialize(ifs);
        neutrals->Deserialize(ifs);
        emeries->Deserialize(ifs);

        ifs.close();
        Logger::getInstance().Info("Deserialization successful.");
    };
};

