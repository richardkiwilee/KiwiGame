#pragma once
#include <string>
#include <cstdint>

// 定义角色阵营
const std::string Camp_Empty = "";     // 空对象 游戏管理类
const std::string Camp_Leader = "leader";   // 领袖 死亡则游戏结束
const std::string Camp_Member = "member";   // 招募的可操控角色
const std::string Camp_Friendly = "friendly";   // 同阵营的不可操控友好角色
const std::string Camp_Neutral = "neutral";     // 中立角色
const std::string Camp_Enemy = "enemy";     // 杂兵
const std::string Camp_Elite = "elite";     // 精英
const std::string Camp_Boss = "boss";     // BOSS

// 定义全局资源
const std::string Resource_Gold = "gold";
const std::string Resource_Food = "food";
const std::string Resource_Stone = "stone";
const std::string Resource_Iron = "iron";
const std::string Resource_Wood = "wood";

// 定义角色属性
const std::string Resource_Exp = "exp";
const std::string Resource_Level = "level";
const std::string Attr_Face = "face";
const std::string Attr_MaxHP = "max_hp";
const std::string Attr_HP = "hp";
const std::string Attr_MaxMP = "max_mp";
const std::string Attr_MP = "mp";
const std::string Attr_MaxMov = "max_mov";
const std::string Attr_Mov = "mov";
const std::string Attr_MaxAp = "max_ap";
const std::string Attr_Ap = "ap";
const std::string Attr_HP_Regen = "hp_regen";
const std::string Attr_MP_Regen = "mp_regen";
const std::string Attr_Str = "str";
const std::string Attr_Dex = "dex";
const std::string Attr_Intelligence = "int";
const std::string Attr_Base_Str = "base_str";
const std::string Attr_Base_Dex = "base_dex";
const std::string Attr_Base_Intelligence = "base_int";
const std::string Attr_Jump = "jump";
const std::string Attr_Base_Jump = "base_jump";
const std::string Attr_Sight = "sight";
const std::string Attr_Base_Sight = "base_sight";
const std::string Attr_Dmg_Boost = "dmg_boost";
const std::string Attr_Base_Dmg_Boost = "base_dmg_boost";
const std::string Attr_Critical_Chance = "critical_chance";
const std::string Attr_Base_Critical_Chance = "base_critical_change";
const std::string Attr_Critical_Boost = "critical_boost";
const std::string Attr_Base_Critical_Boost = "base_critical_boost";
const std::string Attr_Evasion = "evasion";
const std::string Attr_Base_Evasion = "base_evasion";
const std::string Attr_Def = "def";
const std::string Attr_Base_Def = "base_def";
const std::string Attr_Parry = "parry";
const std::string Attr_Base_Parry = "base_parry";
const std::string Attr_Dmg_Reduce = "dmg_reduce";
const std::string Attr_Base_Dmg_Reduce = "base_dmg_reduce";
const std::string Attr_Ac = "ac";
const std::string Attr_Base_Ac = "base_ac";

// 定义装备类型
const std::string Equip_Helmet = "helmet";
const std::string Equip_Chest = "chest";
const std::string Equip_Leg = "leg";
const std::string Equip_Glove = "glove";
const std::string Equip_Foot = "foot";
const std::string Equip_Cloak = "cloak";
const std::string Equip_TwoHands = "twohands";
const std::string Equip_MainHand = "mainhand";
const std::string Equip_SubHand = "subhand";
const std::string Equip_Jewelry = "jewelry";
const std::string Equip_Consumable = "consumable";

// 定义朝向
const std::string Dir_North = "north";
const std::string Dir_East = "east";
const std::string Dir_South = "south";
const std::string Dir_West = "west";

// 定义异常状态 通过组合复数个状态来拼接一个buff 多个buff可能拥有相同的tag
const std::string Status_Free = "free"; // 自由态 与多个状态互斥
const std::string Status_Unmoveable = "unmoveable";     // 无法主动移动
const std::string Status_Unpushable = "unpushable";     // 无法被推动
const std::string Status_Unattackable = "unattackable";     // 无法攻击
const std::string Status_Unfightback = "unfightback";     // 无法反击
const std::string Status_Uncastable = "uncastable";     // 无法施法
const std::string Status_Unchoosable = "unchoosable";     // 无法被选择
const std::string Status_Unseemly = "unseemly";     // 无法被看到
const std::string Status_Unjumpable = "unjumpable";     // 无法跳跃
const std::string Status_Unswimmable = "unswimmable";     // 无法游泳
const std::string Status_Unfleeable = "unfleeable";     // 无法逃跑
const std::string Status_Unstunnable = "unstunnable";     // 无法被控制
const std::string Status_Unhealable = "unhealable";     // 无法回复

// 定义技能影响范围类型
const std::string Skill_Effect_Range_Self = "self";     // 自身
const std::string Skill_Effect_Range_Target = "target";     // 目标
const std::string Skill_Effect_Range_Around = "around";     // 围绕目标 9格
const std::string Skill_Effect_Range_Line = "line";     // 线形范围 增加范围是延长射程
const std::string Skill_Effect_Range_Laser = "laser";     // 镭射范围 增加范围是增大宽度
const std::string Skill_Effect_Range_Sphere = "sphere";     // 球形范围 计算斜向直径
const std::string Skill_Effect_Range_Rectangle = "rectangle";     // 矩形范围 3*2
const std::string Skill_Effect_Range_Global = "global";     // 全局范围
const std::string Skill_Effect_Range_Random_Around = "random_around";     // around范围 随机选择单元格
const std::string Skill_Effect_Range_Random_Sphere = "random_sphere";     // 球形范围 计算斜向直径 随机选择单元格
const std::string Skill_Effect_Range_Random_Global = "random_global";     // 全局范围 随机选择单元格

// 定义单元格类型
const uint8_t QuadGrid_Entity_Empty = 0;     // 空单元格
const uint8_t QuadGrid_Entity_Solid = 1;     // 实心固体 用以建筑物的占位符
const uint8_t QuadGrid_Entity_Passable = 2;     // 通行单元格 用以建筑物的占位符
const uint8_t QuadGrid_Entity_Wood = 3;     // 木质单元格
const uint8_t QuadGrid_Entity_Grass = 4;     // 草地单元格 如果单元格在最上层 应用草地视觉效果
const uint8_t QuadGrid_Entity_Water = 5;     // 水单元格
const uint8_t QuadGrid_Entity_Sand = 6;      // 沙地单元格
const uint8_t QuadGrid_Entity_Lava = 7;      // 岩浆
const uint8_t QuadGrid_Entity_Stone = 8;      // 石头
const uint8_t QuadGrid_Entity_Obsidian = 9;      // 黑曜石
const uint8_t QuadGrid_Entity_Muddy = 10;      // 泥泞

// 定义地面效果
const uint8_t QuadGrid_GroundEffect_None = 0;   // 无地面效果
const uint8_t QuadGrid_GroundEffect_Fire = 1;   // 燃烧
const uint8_t QuadGrid_GroundEffect_Ice = 2;   // 冰
const uint8_t QuadGrid_GroundEffect_Water = 3;   // 水
const uint8_t QuadGrid_GroundEffect_Muddy = 4;   // 泥泞

// 定义悬浮效果
const uint8_t QuadGrid_FloatingEffect_None = 0; // 无悬停效果
const uint8_t QuadGrid_FloatingEffect_Fog = 1; // 雾气
const uint8_t QuadGrid_FloatingEffect_Dark = 2; // 黑暗

// 定义边缘 如果边缘是一个墙体 其生命值归属于建筑对象
const uint8_t QuadGrid_Boundary_None = 0;   // 无边缘
const uint8_t QuadGrid_Boundary_SolidWall = 1;   // 实心墙 不可移动穿过 不可透过视野
const uint8_t QuadGrid_Boundary_DefenceWall = 2;    // 防御用墙 不可移动穿过 可以透过视野 允许单向的远程攻击
const uint8_t QuadGrid_Boundary_Ladder = 3;    // 直梯 两个高度差大于2的相邻单元格 如果通过直梯相连 视为可以移动通过
const uint8_t QuadGrid_Boundary_Fence = 4;    // 栅栏 需要消耗一个动作翻越

// Buff触发类型
const std::string Buff_Trigger_OnTurnStart = "on_turn_start";       // 回合开始
const std::string Buff_Trigger_OnTurnEnd = "on_turn_end";           // 回合结束
const std::string Buff_Trigger_OnAttack = "on_attack";              // 攻击
const std::string Buff_Trigger_OnTakeDamage = "on_take_damage";     // 受到伤害
const std::string Buff_Trigger_OnDeath = "on_death";                // 死亡
const std::string Buff_Trigger_Resident = "resident";               // 常驻

// Buff叠加类型
const std::string Buff_Type_Stack = "stack";     // 叠加
const std::string Buff_Type_Unique = "unique";     // 不可叠加的唯一性

// Buff Reduce Type
const std::string Buff_Reduce_Type_Half = "half";     // 减半
const std::string Buff_Reduce_Type_Full = "full";     // 减全
const std::string Buff_Reduce_Type_Once = "once";     // 减一次
const std::string Buff_Reduce_Type_None = "none";     // 不减

// Buff Target Type
const std::string Buff_Target_Type_Self = "self";     // 本身
const std::string Buff_Target_Type_Enemy = "enemy";     // 敌人
const std::string Buff_Target_Type_Friend = "friend";     // 友军 不包括自己
const std::string Buff_Target_Type_Friend_Self = "friend_self";     // 友军包括自己
const std::string Buff_Target_Type_All = "all";     // 所有

// Buff Effect Range
const std::string Buff_Effect_Range_Self = "self";     // 自身
const std::string Buff_Effect_Range_Around = "around";     // 围绕目标 9格
const std::string Buff_Effect_Range_Sphere = "sphere";     // 球形范围 计算斜向直径
const std::string Buff_Effect_Range_Global = "global";     // 全局范围
const std::string Buff_Effect_Range_Random_Around = "random_around";     // around范围 随机选择单元格
const std::string Buff_Effect_Range_Random_Sphere = "random_sphere";     // 球形范围 计算斜向直径 随机选择单元格
const std::string Buff_Effect_Range_Random_Global = "random_global";     // 全局范围 随机选择单元格
