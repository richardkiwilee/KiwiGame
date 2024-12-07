#include "Character.h"
#include "Skill.h"
#include <cstdlib>
#include <random>
#include <ctime>
#include <math.h>
#include "RandomSeed.h"
struct DamageResult
{
	int64_t src;
	int64_t dst;
	bool hit;
	bool critical;
	int damage;
	int damageType;
};

DamageResult CalculateDamage(RandomSeed* seed, SkillManager* skillmgr, Character* c1, SkillInfo* skill, Character* c2)
{
	const int8_t base_hit = 30;
	const double base_critical = 30.0;

	CharacterInfo* src = c1->GetCharacterInfo();
	CharacterInfo* tar = c2->GetCharacterInfo();
	auto _func = skillmgr->Get(skill->id);
	DamageCalcuteInfo info;
	info.Attacker = *src;
	info.Defender = *tar;
	info.Relative = SpatialRelationship();
	DamageResult result;
	result.src = src->id;
	result.dst = tar->id;
	
	if (skill->DamageType == DAMAGE_TYPE_HEAL)
	{
		result.hit = true;
		result.damage = _func(&info);
		return result;
	}

	int8_t hit_tar = seed->GetPct();
	result.hit = (base_hit + src->HitRate * (1 + src->Luck * 0.01) - tar->Evasion * (1 + tar->Luck * 0.01)) >= hit_tar;
	if (result.hit)
	{
		result.damageType = skill->DamageType;

		result.damage = _func(&info);

		double boost = 1.0;
		for(auto iter = c1->buffs.begin(); iter != c1->buffs.end(); iter++)
		{
			if (iter->second->BuffType == BUFF_TYPE_BOOST)
			{
				boost += iter->second->value;
			}
		}
		for(auto iter = c2->buffs.begin(); iter != c2->buffs.end(); iter++)
		{
			if (iter->second->BuffType == BUFF_TYPE_RESIST_BOOST)
			{
				boost -= iter->second->value;
			}
		}
		
		switch (result.damageType)
		{
		case DAMAGE_TYPE_PHYSICAL:
		case DAMAGE_TYPE_MAGICAL:
		case DAMAGE_TYPE_PURE:
			result.damage = result.damage * boost;
			break;
		default:
			break;
		}

		double criticaladj = 1.0;
		int8_t critical_tar = seed->GetPct();
		result.critical = std::clamp(src->CriticalRate * (1 + src->Luck * 0.01) - tar->Will * (1 + tar->Luck * 0.01), 0.0, base_critical) >= critical_tar;
		if (result.critical)
		{
			result.damage *= src->CriticalStrengh;
		}

	}
	else
	{
		result.critical = false;
		result.damage = 0;
		result.damageType = 0;
	}
	return result;
}
