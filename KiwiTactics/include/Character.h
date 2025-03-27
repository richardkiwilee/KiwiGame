#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include <iostream>
#include <fstream>
#include <ostream>
#include "Property.h"
#include "Buff.h"
#include "GameEvent.h"
#include "CharacterInfo.h"

enum FaceDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum CharacterType { PLAYER = 1, ENEMY = 2, Neutral = 3 };
#define MAX_INT16 65535;
#define MAX_INT8 255;


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
    void attack(Character& target);
    void attacked(Character& attacker);
    void startTurn();
    void endTurn();
    void death();
    void Serialize(const std::string& filename) const;
    void Serialize(std::ofstream& ofs) const;
    void Deserialize(const std::string& filename);
    void Deserialize(std::ifstream& ifs);
    CharacterInfo* GetCharacterInfo();
};
