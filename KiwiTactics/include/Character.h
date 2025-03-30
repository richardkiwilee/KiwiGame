#pragma once
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <limits>
#include <iostream>
#include <fstream>
#include <ostream>
#include "Property.h"
#include "Buff.h"
#include "GameEvent.h"
#include "Skill.h"
#include "CharacterInfo.h"
#include "Equipment.h"

class CharacterAttribute
{
public:
    CharacterAttribute() = default;
    ~CharacterAttribute() = default;
    int32_t Get();
    int32_t GetBase();
    void Update();
private:
    int32_t value;
    int32_t base_value;
    std::map<int64_t, int32_t> adj;
};

class CharacterRecoverableAttribute
{
public:
    CharacterRecoverableAttribute() = default;
    ~CharacterRecoverableAttribute() = default;
    int32_t Get();
    int32_t GetBase();
    void Update();
private:
    int32_t value;
    int32_t base_max_value;
    std::map<int64_t, int32_t> adj;
};


class Character
{
public:
    Character() = default;
	~Character() = default;
    int64_t id;
    int8_t character_type;  // 角色类型 领袖 可操作友方 不可操作友方 中立 普通敌人 精英敌人 boss
	// 基础属性
    int8_t face;    // 角色朝向
    CharacterRecoverableAttribute hp; // 生命
    CharacterRecoverableAttribute mana;   // 魔法
    CharacterRecoverableAttribute movement; // 移动力
    CharacterRecoverableAttribute ap; // 行动点
    CharacterRecoverableAttribute armor; // 护甲
    CharacterAttribute hp_regen; // 生命回复
    CharacterAttribute mana_regen; // 魔法回复
    CharacterAttribute str; // 力量
    CharacterAttribute dex; // 敏捷
    CharacterAttribute intelligence; // 智力
    CharacterAttribute jump; // 跳跃力
    CharacterAttribute sight; // 视野
    CharacterAttribute dmg_boost; // 攻击力增强
    CharacterAttribute critical_chance; // 暴击率
    CharacterAttribute critical_boost; // 暴击增强
    CharacterAttribute evasion; // 闪避
    CharacterAttribute def; // 护甲
    CharacterAttribute parry; // 数值伤害减免
    CharacterAttribute dmg_reduce; // 百分比伤害减免
    CharacterAttribute ac; // 韧性 影响抵抗负面状态与暴击的概率

    std::map<int64_t, BuffInfo*> buffs; // buff or debuff
    std::map<int64_t, Skill*> skills;   // 角色节能
    std::map<int64_t, Skill*> equipped_skills;   // 装备技能
    std::set<int64_t> actions; // 因为可以进行的动作
    std::set<int64_t> traits; // 角色常驻特性

    Helmet* helmet = nullptr;
    Chest* chest = nullptr;
    Gloves* gloves = nullptr;
    Leg* leg = nullptr;
    Foot* foot = nullptr;
    Cloak* cloak = nullptr; 
    Jewelry* jewelry1 = nullptr;
    Jewelry* jewelry2 = nullptr;
    Consumable* consumable1 = nullptr;
    Consumable* consumable2 = nullptr;
    MainWeapon* main_weapon = nullptr;
    SubWeapon* sub_weapon = nullptr;
    
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
private:
};
