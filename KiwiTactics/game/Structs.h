#pragma once
#include <cstdint>

struct CharacterInfo
{
    int64_t id;
    int16_t position_x;
    int16_t position_y;
    int16_t position_height;
    int8_t direction;
    int16_t MaxHealth;
    int16_t Health;
    int16_t MaxMana;
    int16_t Mana;
    int16_t MaxArmor;
    int16_t Armor;
    int16_t MaxActionPoint;
    int16_t ActionPoint;
    int16_t MaxMovement;
    int16_t Movement;
    int16_t Strength;     // 物理攻击
    int16_t PhyDef;     // 物理防御
    int16_t Intelligence;     // 魔法攻击
    int16_t MagDef;     // 魔法防御
    int16_t Dexterity;        // 敏捷
    int16_t CriticalRate;           // 暴击率
    int16_t CriticalStrengh;    // 暴击力量
    int16_t Luck;       // 幸运
    int16_t Will;       // 意志
    int16_t HitRate;    // 命中率
    int16_t Evasion;    // 闪避率
    int16_t Jump;       // 跳跃力

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
	bool inSight;
	bool inAttackRange;
	bool isBackStrike;
	bool isSideStrike;
};

struct DamageCalcuteInfo	// 嵌套的结构体 用以传递计算伤害
{
	CharacterInfo Attacker;
	CharacterInfo Defender;
	SpatialRelationship Relative;
};

struct BuffInfo
{
    int64_t id;
    int8_t BuffType;
    double value;
    int64_t remainTurn;
    int funcAddress;
};
