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

class Character
{
public:
    Character() = default;
	~Character() = default;
    int64_t id;
    int8_t character_type;  // 角色类型 领袖 可操作友方 不可操作友方 中立 普通敌人 精英敌人 boss
	// 基础属性
    int8_t face;    // 角色朝向
    int16_t max_hp; // 最大生命
    int16_t max_mana;   // 最大魔法
    int8_t max_movement; // 最大移动力
    int8_t max_ap; // 最大行动点
    int8_t max_armor; // 最大护甲
    int16_t cur_hp; // 当前生命
    int16_t cur_mana; // 当前魔法
    int8_t cur_movement; // 当前移动力
    int8_t cur_ap; // 当前行动点    
    int8_t cur_armor; // 当前护甲
    int8_t base_hp_regen; // 基础生命回复
    int8_t base_mana_regen; // 基础魔法回复
    int8_t base_str; // 基础力量
    int8_t base_dex; // 基础敏捷
    int8_t base_int; // 基础智力
    int8_t base_jump; // 基础跳跃力
    int8_t base_sight; // 基础视野
    int8_t base_dmg_boost; // 基础攻击力增强
    int8_t base_critical_chance; // 基础暴击率
    int8_t base_critical_boost; // 基础暴击增强
    int8_t base_evasion; // 基础闪避
    int8_t base_def; // 基础护甲
    int8_t base_parry; // 基础数值伤害减免
    int8_t base_dmg_reduce; // 基础百分比伤害减免
    int8_t base_ac; // 基础韧性 影响抵抗负面状态与暴击的概率

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
