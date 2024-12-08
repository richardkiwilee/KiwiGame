#include <algorithm>
#include "Structs.h"
#include <map>
#include <string>
#include <functional>

enum FaceDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum CharacterType { PLAYER = 1, ENEMY = 2, Neutral = 3 };
#define MAX_INT16 65535;
#define MAX_INT8 255;
typedef int16_t CA16;
typedef int8_t CA8;
typedef uint16_t UCA16;
typedef uint8_t UCA8;

template <typename T>
class Property {
public:
    Property(T initial_value, T min_value, T max_value)
        : _value(initial_value), _min(min_value), _max(max_value) {}

    Property(T initial_value, T max_value)
        : _value(initial_value), _min(0), _max(max_value) {}

    Property(T max_value)
        : _value(max_value), _min(0), _max(max_value) {}

    Property()
        : _value(100), _min(0), _max(100) {}

    // 获取属性值
    T get() const {
        return _value;
    }

    // 设置属性值，并在设置后打印消息
    void set(T value) {
        if (value != _value) {
            _value = std::clamp(value, _min, _max);
        }
    }

    void setMax(T value){
        _max = std::clamp(value, 0, std::numeric_limits<int>::max());
        _value = std::clamp(_value, _min, _max);
    }

    // 运算符重载，用于赋值时调用set函数
    Property& operator=(T value) {
        set(value);
        return *this;
    }
    
    operator T() const {
        return _value;  // 将Property转换为其内部的值
    }

private:
    T _value;  // 属性值类型为模板类型T
    T _min;
    T _max;     // 系统上限 一般取类型的极值 注意与后续距离实例化成角色属性的上限不同
};

// clamp函数，限制Property的值在指定范围内
template <typename T>
T clamp(T newValue, Property<T>& minValue, Property<T>& maxValue) {
    // 获取minValue和maxValue的值，并使用std::clamp进行范围限制
    T clampedValue = std::clamp(newValue, minValue.get(), maxValue.get());
    // 设置新的值（此处假设value是一个CA16类型的成员变量）
    return clampedValue;
}

class EventSystem {
public:
    // 定义一个事件类型，事件是一个 void() 函数
    using EventHandler = std::function<void()>;
    // 向事件列表中添加事件处理器
    void addEventHandler(const EventHandler& handler) {
        eventHandlers.push_back(handler);
    }
    // 移除事件处理器
    void removeEventHandler(const EventHandler& handler) {
        // 使用 std::remove_if 和 erase 来移除匹配的事件处理器
        auto it = std::remove_if(eventHandlers.begin(), eventHandlers.end(),
            [&handler](const EventHandler& storedHandler) {
                return storedHandler.target_type() == handler.target_type() &&
                    *storedHandler.target<void()>() == *handler.target<void()>();
            });

        eventHandlers.erase(it, eventHandlers.end());
    }
    // 触发所有事件处理器
    void triggerEvent() {
        for (auto& handler : eventHandlers) {
            handler();  // 执行事件处理器
        }
    }
private:
    std::vector<EventHandler> eventHandlers;  // 存储事件处理器
};

class Character
{
public:
    Character() = default;
	~Character() = default;
	FaceDirection face;
	CharacterType _character_type;
    int64_t id;
	// 基础属性
    Property<int16_t> hp;
    Property<int16_t> mana;
    Property<int8_t> movement;
    Property<int8_t> ap;
    Property<int16_t> armor;
    std::map<int64_t, BuffInfo*> buffs;
    EventSystem OnAttack;
    EventSystem OnAttacked;
    EventSystem OnTurnStart;
    EventSystem OnTurnEnd;
    EventSystem OnDeath;
    void attack(Character& target) {
        OnAttack.triggerEvent();  // 触发攻击事件
        target.attacked(*this);  // 让目标受到攻击
    }

    void attacked(Character& attacker) {
        OnAttacked.triggerEvent();  // 触发被攻击事件
    }

    void startTurn() {
        OnTurnStart.triggerEvent();  // 触发回合开始事件
    }

    void endTurn() {
        OnTurnEnd.triggerEvent();  // 触发回合结束事件
    }
    void death() {
		OnDeath.triggerEvent();  // 触发死亡事件
	}

    // 序列化: 将 QuadGridMap 对象的字段以及 QuadGridMap 数组写入文件
    void Serialize(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            std::cerr << "Error opening file for serialization!" << std::endl;
            return;
        }
        this->Serialize(ofs);
        ofs.close();
    }

    void Serialize(std::ofstream& ofs) const {
    }

    // 反序列化: 从文件读取数据并恢复 QuadGridMap 对象的字段以及 QuadGridMap 数组
    void Deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            std::cerr << "Error opening file for deserialization!" << std::endl;
            return;
        }
        this->Deserialize(ifs);
        ifs.close();
    }

    void Deserialize(std::ifstream& ifs) {
    }

    CharacterInfo* GetCharacterInfo()
    {
        CharacterInfo* info = new CharacterInfo();
        return info;
    }

};


// 默认技能伤害公式，在书写技能公式时，一般不使用被攻击方的抗性补正 但仍然传入了被攻击方的信息是为了方便完成例如斩杀的功能
double _exampleDmgFormula(DamageCalcuteInfo* info) {
    CharacterInfo attacker = info->Attacker;
    CharacterInfo defender = info->Defender;
    SpatialRelationship relative = info->Relative;
    return 1.0 * info->Attacker.Strength;
};