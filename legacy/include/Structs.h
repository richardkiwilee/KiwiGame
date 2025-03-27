#pragma once
#include <cstdint>
#include <vector>

struct SkillInfo
{
    int64_t id;
    int64_t trigger;    // 连锁技能的id
    int8_t DamageType;  // 伤害属性
    int64_t preanimation;   // 施法前动画    
    int64_t animation;      // 施法动画
    int repect;     // 重复次数
    int AffectType; // 友军 敌军 全体 环境
    int TargetType; // 自己 点目标友军 点目标敌人 目标地点 战场
    int AffectRange; // 作用半径
    int CastType;   // 直线 抛射 球体 圆柱体 弹射
    int CastRange; // 施法距离  
    bool NeedSight; // 需要视野
    int funcAddress;	
    int CostHp;     
    int CostHpPct;
    int CostMaxHpPct;
    int CostMp;
    int CostMpPct;
    int CostMaxMpPct;
    int CostAp;
    int CostMove;
    int RecoverType;    // 无法主动回复，按回合回复，按战斗回复
    int MaxUseTime;
    int applyPassiveEffect; // 施加被动效果
};

struct PassiveEffect
{
    int64_t id;
    int funcAddress;
    int64_t animation;      // 动画
    int trigger;    // 回合开始 回合结束 攻击时 受击时 死亡时 常驻
    int stacks;     // 叠加层数
    bool candispeled;   // 是否可被驱散
    int degression;	 // 递减方式 减1 减半 
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

struct BuildingCell3D
{
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t AskTerrain;  // 需要的地格类型
};
struct BuildingInfo
{
    int64_t id;
    int8_t AskTerrain;  // 锚点需要的判定地格类型
    std::vector<BuildingCell3D> occupy;  // 占用地格
};
