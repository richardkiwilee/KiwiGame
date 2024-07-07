#pragma once
#include <map>
#include <vector>
#ifndef SKILL_H
#define SKILL_H

#ifdef SKILL_EXPORTS
#define SKILL_API __declspec(dllexport)
#else
#define SKILL_API __declspec(dllimport)
#endif

class SKILL_API Skill {
public:
    Skill();
    ~Skill();
	void Cast();
	void OnTrigger();
private:
	uint64_t id;
	bool isPassive;			// 是否是被动技能
	uint64_t castRange;		// 定义施法范围 指使用技能后需要点击的可选范围，0表示无需点击 以自己为出发点；正整数表示一个半径
	uint64_t castTime;		// 定义施法时间 指使用技能后需要等待的时间，0表示无需等待
	uint64_t cooldown;		// 定义冷却时间 指使用技能后需要等待的时间，0表示无需等待
	uint64_t limit;			// 定义使用次数 指技能的使用次数
	uint64_t recoverType;	// 定义重置技能使用次数的类型 分为OnTurn, OnBattle, OnLife
	uint64_t EffectRange;	// 定义效果范围的应用id 指技能的效果范围，由xml定义
	std::map<uint64_t, uint64_t> cost;	// 定义消耗 指使用技能后需要消耗的资源，0表示无需消耗
	// 这边如果以后做成联机 AP类型的单回合多次攻击是不是太过imba
	std::vector<uint64_t> effect;		// 定义效果 指技能的效果，由xml定义
};

#endif
