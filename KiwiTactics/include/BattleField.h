#pragma once
#include "QuadMap.h"
#include "Character.h"
#include "Building.h"
#include "Seed.h"
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

    void Serialize(std::ofstream& ofs);
    void Deserialize(std::ifstream& ifs);

private:
    std::unordered_map<int64_t, T*> _class;
};

class BattleField
{
public:
    BattleField(std::string name);
    std::string archiveName;
    
    void Open(std::string name);
    void Close();
    void Save();
    void Serialize();
    void Deserialize();
    void PlaceBuilding(int x, int y, int64_t building_id);
    void RemoveBuilding(int x, int y);
    void MoveCharacter(int64_t character_id, int x, int y);
    void SettlementSkill(int64_t caster_id, int64_t skill_id, int64_t target_id);
    void EndTurn();
    void StartTurn();

private:
    QuadGridMap* map = nullptr;
    Inventory* inventory = nullptr;
    ObjectsManager<Character>* alias = nullptr;
    ObjectsManager<Character>* neutrals = nullptr;
    ObjectsManager<Character>* emeries = nullptr;
    ObjectsManager<Building>* buildings = nullptr;
    Seed* randomBuffer = nullptr;
    void Serialize(const std::string& filename);
    void Deserialize(const std::string& filename);
    void New(std::string name);
};
