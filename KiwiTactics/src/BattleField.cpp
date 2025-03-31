#include "BattleField.h"
#include "Logger.h"
#include "Timeline.h"

template <typename T>
void ObjectsManager<T>::Serialize(std::ofstream& ofs) {
    int8_t size = static_cast<int8_t>(_class.size());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (auto iter = _class.begin(); iter != _class.end(); ++iter) {
        iter->second->Serialize(ofs);
    }
}

template <typename T>
void ObjectsManager<T>::Deserialize(std::ifstream& ifs) {
    int8_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (int i = 0; i < size; ++i) {
        T* t = new T();
        t->Deserialize(ifs);
        _class[t->id] = t;
    }
}

BattleField::BattleField(std::string name) {
    archiveName = name;
    if (fileExists(name))
    {
        this->Deserialize(name);
    }
    else
    {
        this->New(name);
    }
}

void BattleField::Open(std::string name)
{
    if (archiveName != "") {
        Logger::getInstance().Warn("Open fail, no file name given.");
        return;
    }
    this->Deserialize(archiveName);
}

void BattleField::Close()
{
    delete map; map = nullptr;
    delete inventory; inventory = nullptr;
    delete alias; alias = nullptr;
    delete neutrals; neutrals = nullptr;
    delete emeries; emeries = nullptr;
    delete buildings; buildings = nullptr;
    delete randomBuffer; randomBuffer = nullptr;
}

void BattleField::Save()
{
    this->Serialize(archiveName);
}

void BattleField::Serialize()
{
    Serialize(archiveName);
}

void BattleField::Deserialize()
{
    this->Deserialize(archiveName);
}

void BattleField::PlaceBuilding(int x, int y, int64_t building_id)
{
}

void BattleField::BuildBuilding(int x, int y, int64_t building_id)
{
}

void BattleField::RemoveBuilding(int x, int y)
{
}

void BattleField::MoveCharacter(int64_t character_id, int x, int y)
{
}

void BattleField::SettlementSkill(int64_t caster_id, int64_t skill_id, int64_t target_id)
{
}

void BattleField::CastSkill(int64_t caster_id, int64_t skill_id, uint8_t x, uint8_t y)
{
    if (caster_id != 0)
    {
        Character* caster = GetCharacter(caster_id);
        if (caster == nullptr)
        {
            // TODO: 错误处理   
            return;
        }
        Skill* skill = caster->GetSkill(skill_id);
        if (skill == nullptr)
        {
            // TODO: 错误处理   
            return;
        }
        QuadGrid* target = map->Get(x, y);
        if (target == nullptr)
        {
            // TODO: 错误处理   
            return;
        }
        if (skill->requireTarget)
        {
            if (skill->target_type == 0)
            {

                if (target->unit == nullptr)
                {
                    // TODO: 错误处理   
                    return;
                }
   
            }
            else if (skill->target_type == 1)
            {
                
            }
            else
            {
                
            }
        }
        if (!skill->castable)
        {
            // TODO: 错误处理   
            return;
        }
        // caster->CastSkill(skill, target);
    }
    else
    {
        
    }
    // Timeline timeline = new Timeline();

}

int64_t BattleField::NextActionableCharacter()
{
    return 0;
}

Character *BattleField::GetCharacter(int64_t character_id)
{
    return nullptr;
}

void BattleField::EndTurn()
{
}

void BattleField::StartTurn()
{
}

void BattleField::Serialize(const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        Logger::getInstance().Error("Failed to open file for serialization.");
        return;
    }
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
}

void BattleField::Deserialize(const std::string& filename)
{
    randomBuffer = new Seed(255);
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
}

void BattleField::New(std::string name)
{
    randomBuffer = new Seed(255);
    inventory = new Inventory();
    buildings = new ObjectsManager<Building>();
    alias = new ObjectsManager<Character>();
    neutrals = new ObjectsManager<Character>();
    emeries = new ObjectsManager<Character>();
    int64_t seed = randomBuffer->GetInt64();
    map = new QuadGridMap(1, 50, 50, seed);
    this->Save();
}