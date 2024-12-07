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
    int16_t Strength;     // ������
    int16_t PhyDef;     // �������
    int16_t Intelligence;     // ħ������
    int16_t MagDef;     // ħ������
    int16_t Dexterity;        // ����
    int16_t CriticalRate;           // ������
    int16_t CriticalStrengh;    // ��������
    int16_t Luck;       // ����
    int16_t Will;       // ��־
    int16_t HitRate;    // ������
    int16_t Evasion;    // ������
    int16_t Jump;       // ��Ծ��

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

struct DamageCalcuteInfo	// Ƕ�׵Ľṹ�� ���Դ��ݼ����˺�
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
