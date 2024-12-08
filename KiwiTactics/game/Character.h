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

class EventSystem {
public:
    // ����һ���¼����ͣ��¼���һ�� void() ����
    using EventHandler = std::function<void()>;
    // ���¼��б�������¼�������
    void addEventHandler(const EventHandler& handler) {
        eventHandlers.push_back(handler);
    }
    // �Ƴ��¼�������
    void removeEventHandler(const EventHandler& handler) {
        // ʹ�� std::remove_if �� erase ���Ƴ�ƥ����¼�������
        auto it = std::remove_if(eventHandlers.begin(), eventHandlers.end(),
            [&handler](const EventHandler& storedHandler) {
                return storedHandler.target_type() == handler.target_type() &&
                    *storedHandler.target<void()>() == *handler.target<void()>();
            });

        eventHandlers.erase(it, eventHandlers.end());
    }
    // ���������¼�������
    void triggerEvent() {
        for (auto& handler : eventHandlers) {
            handler();  // ִ���¼�������
        }
    }
private:
    std::vector<EventHandler> eventHandlers;  // �洢�¼�������
};

class Character
{
public:
    Character() = default;
	~Character() = default;
	FaceDirection face;
	CharacterType _character_type;
    int64_t id;
	// ��������
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
        OnAttack.triggerEvent();  // ���������¼�
        target.attacked(*this);  // ��Ŀ���ܵ�����
    }

    void attacked(Character& attacker) {
        OnAttacked.triggerEvent();  // �����������¼�
    }

    void startTurn() {
        OnTurnStart.triggerEvent();  // �����غϿ�ʼ�¼�
    }

    void endTurn() {
        OnTurnEnd.triggerEvent();  // �����غϽ����¼�
    }
    void death() {
		OnDeath.triggerEvent();  // ���������¼�
	}

    // ���л�: �� QuadGridMap ������ֶ��Լ� QuadGridMap ����д���ļ�
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

    // �����л�: ���ļ���ȡ���ݲ��ָ� QuadGridMap ������ֶ��Լ� QuadGridMap ����
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


// Ĭ�ϼ����˺���ʽ������д���ܹ�ʽʱ��һ�㲻ʹ�ñ��������Ŀ��Բ��� ����Ȼ�����˱�����������Ϣ��Ϊ�˷����������նɱ�Ĺ���
double _exampleDmgFormula(DamageCalcuteInfo* info) {
    CharacterInfo attacker = info->Attacker;
    CharacterInfo defender = info->Defender;
    SpatialRelationship relative = info->Relative;
    return 1.0 * info->Attacker.Strength;
};