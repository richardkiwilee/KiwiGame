#include "QuadMap.h"
#include "Character.h"
#include "Building.h"
#include "RandomSeed.h"
#include "Inventory.h"
#include <iostream>
#include <string>
inline bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

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


class GameManager
{
public:
    GameManager(std::string name) {
        archiveName = name;
        if (fileExists(name))
        {
            this->Deserialize(name);
        }
		else
		{
			this->New(name);
		}
	};
    std::string archiveName;
    
    void Open(std::string name)
    {
        if (archiveName != "") {
            Logger::getInstance().Warn("Open fail, no file name given.");
            return;
        }
        this->Deserialize(archiveName);
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
    };
    void Save()
    {
        this->Serialize(archiveName);
    };
    void Serialize() {
        Serialize(archiveName);
    };
    void Deserialize() {
        this->Deserialize(archiveName);
    };

    void PlaceBuilding(int x, int y, int64_t building_id)
    {

    };

    void RemoveBuilding(int x, int y)
	{

	};

    void MoveCharacter(int64_t character_id, int x, int y)
	{

	};

    void SettlementSkill(int64_t caster_id, int64_t skill_id, int64_t target_id)
	{

	};

    void EndTurn()
    {
    
    };

    void StartTurn()
    {
    
    };

private:
    QuadGridMap* map = nullptr;
    Inventory* inventory = nullptr;
    ObjectsManager<Character>* alias = nullptr;
    ObjectsManager<Character>* neutrals = nullptr;
    ObjectsManager<Character>* emeries = nullptr;
    ObjectsManager<Building>* buildings = nullptr;
    RandomSeed* randomBuffer = nullptr;
    void Serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            Logger::getInstance().Error("Failed to open file for serialization.");
            return;
        }
        // 序列化版本和名称
        ofs.write(VERSION.data(), VERSION.size()); ofs.put('\0');
        // 序列化mod列表
        // module->Serialize(ofs);
        // 
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
        randomBuffer = new RandomSeed(255);
        inventory = new Inventory();
        buildings = new ObjectsManager<Building>();
        alias = new ObjectsManager<Character>();
        neutrals = new ObjectsManager<Character>();
        emeries = new ObjectsManager<Character>();
        map = new QuadGridMap();


        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            Logger::getInstance().Error("Failed to open file for deserialization.");
            return;
        }
        // 反序列化版本和名称
        std::getline(ifs, VERSION, '\0');  // 读取直至 null terminator
        // module->Deserialize(ifs);
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

    void New(std::string name)
    {
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
};
