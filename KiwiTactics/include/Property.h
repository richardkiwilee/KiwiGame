#pragma once
#include <cstdint>

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