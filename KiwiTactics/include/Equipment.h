# include "Buff.h"

class BaseEquipment {  // 基础装备
public:
    BaseEquipment() = default;
    ~BaseEquipment() = default;
    int8_t position;    // 部位
    EquipmentEffect* effect = nullptr; // 效果
    std::set<int64_t> skills; // 装备技能
    std::set<int64_t> buffs; // 装备buff
    std::map<int64_t, int32_t> attributes; // 装备属性
};

class Helmet {  // 头盔
public:
    Helmet() = default;
    ~Helmet() = default;
};

class Chest {   // 胸甲
public:
    Chest() = default;
    ~Chest() = default;
};

class Glove {  // 手套
public:
    Glove() = default;
    ~Glove() = default;
};

class Leg {    // 腿部
public:
    Leg() = default;
    ~Leg() = default;
};

class Foot {   // 脚
public:
    Foot() = default;
    ~Foot() = default;
};

class Cloak {    // 披风
public:
    Cloak() = default;
    ~Cloak() = default;
};

class MainWeapon {  // 主武器
public:
    MainWeapon() = default;
    ~MainWeapon() = default;
};

class SubWeapon {  // 副武器
public:
    SubWeapon() = default;
    ~SubWeapon() = default;
};

class Jewelry {  // 饰品
public:
    Jewelry() = default;
    ~Jewelry() = default;
};

class Consumable {  // 消耗品
public:
    Consumable() = default;
    ~Consumable() = default;
};
