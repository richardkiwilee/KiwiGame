#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <string>
#include "QuadMap.h"
#include "Character.h"
#include "Building.h"
#include "RandomSeed.h"
#include "Inventory.h"
#include "../version.h"
#include "../extern/ModuleManager.h"

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
    std::string archive_name;
    ArchiveManager(std::string archive_name)
    {
        this->archive_name = archive_name;
    };
    ~ArchiveManager() {};
    ModuleManager* module;
	QuadGridMap* map;
    Inventory* inventory;
    ObjectsManager<Character>* alias;
    ObjectsManager<Character>* neutrals;
    ObjectsManager<Character>* emeries;
    ObjectsManager<Building>* buildings;
    RandomSeed* randomBuffer;
    
    void Serialize() {
        Serialize(archive_name);
    }

    void Serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            std::cerr << "Failed to open file for serialization." << std::endl;
            return;
        }
        // 序列化版本和名称
        ofs.write(VERSION.data(), VERSION.size()); ofs.put('\0');
        ofs.write(archive_name.data(), archive_name.size()); ofs.put('\0');
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
        std::cout << "Serialization successful." << std::endl;
    }

    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            std::cerr << "Failed to open file for deserialization." << std::endl;
            return;
        }

        // 反序列化版本和名称
        std::getline(ifs, VERSION, '\0');  // 读取直至 null terminator
        std::getline(ifs, archive_name, '\0');     // 读取直至 null terminator

        module->Deserialize(ifs);
        randomBuffer->Deserialize(ifs);
        map->Deserialize(ifs);
        inventory->Deserialize(ifs);
        buildings->Deserialize(ifs);
        alias->Deserialize(ifs);
        neutrals->Deserialize(ifs);
        emeries->Deserialize(ifs);

        ifs.close();
        std::cout << "Deserialization successful." << std::endl;
    }
};

