#pragma once
#include <cstdint>
#include <map>


struct BuffInfo
{
    int64_t id = 0;
    int8_t BuffType = 0;
    double value = 0;
    int64_t remainTurn = 0;
    int funcAddress = 0;
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

class EquipmentEffect
{
public:
    EquipmentEffect() = default;
    ~EquipmentEffect() = default;
};

class Buff
{
public:
    Buff() = default;
    ~Buff() = default;
    int64_t id = 0;
    std::string name = "";
    bool visible = true;
    std::string BuffType = "";   // stack unique
    std::string ReduceType = ""; // half full once none
    std::string TargetType = ""; // self enemy friend friend_self all
    std::string EffectRange = ""; // self around sphere global random_around random_sphere random_global
    uint16_t max_value = 0xffff;    // max=0xffff
    uint16_t value = 0;
    int64_t remainTurn;
    std::vector<std::map<std::string, int64_t>> nodes;
    int funcAddress;
    void* OnTurnStart = nullptr;
    void* OnTurnEnd = nullptr;
    void* OnAttack = nullptr;
    void* OnTakeDamage = nullptr;
    void* OnDeath = nullptr;
    void* OnEnable = nullptr;
    void* OnDisable = nullptr;
};