#pragma once
#include <cstdint>

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

struct SkillInfo
{
	int64_t id;
	int8_t DamageType;
	bool TargetType;
	bool NeedSight;
	int funcAddress;
};


struct SpatialRelationship
{
	bool inSight = false;
	bool inAttackRange = false;
	bool isBackStrike = false;
	bool isSideStrike = false;
};

struct DamageCalcuteInfo	// 嵌套的结构体 用以传递计算伤害
{
	CharacterInfo Attacker;
	CharacterInfo Defender;
	SpatialRelationship Relative;
};

struct BuffInfo
{
    int64_t id = 0;
    int8_t BuffType = 0;
    double value = 0;
    int64_t remainTurn = 0;
    int funcAddress = 0;
};
