#pragma once
#include <cstdint>


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