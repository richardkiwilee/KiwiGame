#include <algorithm>
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

    // ��ȡ����ֵ
    T get() const {
        return _value;
    }

    // ��������ֵ���������ú��ӡ��Ϣ
    void set(T value) {
        if (value != _value) {
            _value = std::clamp(value, _min, _max);
        }
    }

    void setMax(T value){
        _max = std::clamp(value, 0, std::numeric_limits<int>::max());
        _value = std::clamp(_value, _min, _max);
    }

    // ��������أ����ڸ�ֵʱ����set����
    Property& operator=(T value) {
        set(value);
        return *this;
    }
    
    operator T() const {
        return _value;  // ��Propertyת��Ϊ���ڲ���ֵ
    }

private:
    T _value;  // ����ֵ����Ϊģ������T
    T _min;
    T _max;     // ϵͳ���� һ��ȡ���͵ļ�ֵ ע�����������ʵ�����ɽ�ɫ���Ե����޲�ͬ
};

// clamp����������Property��ֵ��ָ����Χ��
template <typename T>
T clamp(T newValue, Property<T>& minValue, Property<T>& maxValue) {
    // ��ȡminValue��maxValue��ֵ����ʹ��std::clamp���з�Χ����
    T clampedValue = std::clamp(newValue, minValue.get(), maxValue.get());
    // �����µ�ֵ���˴�����value��һ��CA16���͵ĳ�Ա������
    return clampedValue;
}


class Character
{
public:
    Character(){};
	~Character();
	FaceDirection face;
	CharacterType _character_type;
	
	// ��������
    Property<int16_t> hp;
    Property<int16_t> mana;
    Property<int16_t> stamina;
    Property<int8_t> movement;
    Property<int8_t> ap;
    Property<int16_t> armor;

};