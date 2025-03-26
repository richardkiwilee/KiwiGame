#pragma once
#include <cstdint>
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
