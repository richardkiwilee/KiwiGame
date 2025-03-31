#include "Logger.h"
#include "Character.h"

void Character::startTurn() {
    OnTurnStart.triggerEvent();  // 触发回合开始事件
}

void Character::endTurn() {
    OnTurnEnd.triggerEvent();  // 触发回合结束事件
}

void Character::death() {
    OnDeath.triggerEvent();  // 触发死亡事件
}

void Character::Serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        Logger::getInstance().Error("Error opening file for serialization!");
        return;
    }
    this->Serialize(ofs);
    ofs.close();
}

void Character::Serialize(std::ofstream& ofs) const {
}

void Character::Deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        Logger::getInstance().Error("Error opening file for deserialization!");
        return;
    }
    this->Deserialize(ifs);
    ifs.close();
}

void Character::Deserialize(std::ifstream& ifs) {

}

CharacterInfo* Character::GetCharacterInfo() {
    CharacterInfo* info = new CharacterInfo();
    return info;
}

Skill *Character::GetSkill(int64_t id)
{
    return nullptr;
}

int32_t CharacterAttribute::Get()
{
    return 0;
}

int32_t CharacterAttribute::GetBase()
{
    return 0;
}

void CharacterAttribute::Update()
{
}

int32_t CharacterRecoverableAttribute::Get()
{
    return 0;
}

int32_t CharacterRecoverableAttribute::GetBase()
{
    return 0;
}

void CharacterRecoverableAttribute::Update()
{
}
