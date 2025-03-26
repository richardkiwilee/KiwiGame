#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include <iostream>
#include <fstream>
#include <ostream>
#include "Property.h"
#include "Buff.h"
#include "GameEvent.h"

enum FaceDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum CharacterType { PLAYER = 1, ENEMY = 2, Neutral = 3 };
#define MAX_INT16 65535;
#define MAX_INT8 255;

struct CharacterInfo
{
    int64_t id = -1;
    int16_t position_x = -1;
    int16_t position_y = -1;
    int16_t position_height = -1;
    int8_t direction = 0;
    int16_t MaxHealth = -1;
    int16_t Health = -1;
    int16_t MaxMana = -1;
    int16_t Mana = -1;
    int16_t MaxArmor = -1;
    int16_t Armor = -1;
    int16_t MaxActionPoint = -1;
    int16_t ActionPoint = -1;
    int16_t MaxMovement = -1;
    int16_t Movement = -1;
    int16_t Strength = -1;     // 物理攻击
    int16_t PhyDef = -1;     // 物理防御
    int16_t Intelligence = -1;     // 魔法攻击
    int16_t MagDef = -1;     // 魔法防御
    int16_t Dexterity = -1;        // 敏捷
    int16_t CriticalRate = -1;           // 暴击率
    int16_t CriticalStrengh = -1;    // 暴击力量
    int16_t Luck = -1;       // 幸运
    int16_t Will = -1;       // 意志
    int16_t HitRate = -1;    // 命中率
    int16_t Evasion = -1;    // 闪避率
    int16_t Jump = -1;       // 跳跃力

};

class Character
{
public:
    Character() = default;
	~Character() = default;
	FaceDirection face;
	CharacterType _character_type;
    int64_t id;
	// 基础属性
    Property<int16_t> hp;
    Property<int16_t> mana;
    Property<int8_t> movement;
    Property<int8_t> ap;
    Property<int16_t> armor;
    std::map<int64_t, BuffInfo*> buffs;
    EventSystem OnAttack;
    EventSystem OnAttacked;
    EventSystem OnTurnStart;
    EventSystem OnTurnEnd;
    EventSystem OnDeath;
    void attack(Character& target);
    void attacked(Character& attacker);
    void startTurn();
    void endTurn();
    void death();
    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);
    CharacterInfo* GetCharacterInfo();
};
