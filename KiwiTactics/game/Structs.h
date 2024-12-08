#pragma once
#include <cstdint>
struct SkillInfo
{
    int64_t id;
    int64_t trigger;    // �������ܵ�id
    int8_t DamageType;  // �˺�����
    int64_t preanimation;   // ʩ��ǰ����    
    int64_t animation;      // ʩ������
    int repect;     // �ظ�����
    int AffectType; // �Ѿ� �о� ȫ�� ����
    int TargetType; // �Լ� ��Ŀ���Ѿ� ��Ŀ����� Ŀ��ص� ս��
    int AffectRange; // ���ð뾶
    int CastType;   // ֱ�� ���� ���� Բ���� ����
    int CastRange; // ʩ������  
    bool NeedSight; // ��Ҫ��Ұ
    int funcAddress;	
    int CostHp;     
    int CostHpPct;
    int CostMaxHpPct;
    int CostMp;
    int CostMpPct;
    int CostMaxMpPct;
    int CostAp;
    int CostMove;
    int RecoverType;    // �޷������ظ������غϻظ�����ս���ظ�
    int MaxUseTime;
    int applyPassiveEffect; // ʩ�ӱ���Ч��
};

struct PassiveEffect
{
    int64_t id;
    int funcAddress;
    int64_t animation;      // ����
    int trigger;    // �غϿ�ʼ �غϽ��� ����ʱ �ܻ�ʱ ����ʱ ��פ
    int stacks;     // ���Ӳ���
    bool candispeled;   // �Ƿ�ɱ���ɢ
    int degression;	 // �ݼ���ʽ ��1 ���� 
};

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
    int16_t Strength = -1;     // ������
    int16_t PhyDef = -1;     // �������
    int16_t Intelligence = -1;     // ħ������
    int16_t MagDef = -1;     // ħ������
    int16_t Dexterity = -1;        // ����
    int16_t CriticalRate = -1;           // ������
    int16_t CriticalStrengh = -1;    // ��������
    int16_t Luck = -1;       // ����
    int16_t Will = -1;       // ��־
    int16_t HitRate = -1;    // ������
    int16_t Evasion = -1;    // ������
    int16_t Jump = -1;       // ��Ծ��

};

struct SpatialRelationship
{
	bool inSight = false;
	bool inAttackRange = false;
	bool isBackStrike = false;
	bool isSideStrike = false;
};

struct DamageCalcuteInfo	// Ƕ�׵Ľṹ�� ���Դ��ݼ����˺�
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

struct BuildingCell3D
{
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t AskTerrain;  // ��Ҫ�ĵظ�����
};
struct BuildingInfo
{
    int64_t id;
    int8_t AskTerrain;  // ê����Ҫ���ж��ظ�����
    std::vector<BuildingCell3D> occupy;  // ռ�õظ�
};
