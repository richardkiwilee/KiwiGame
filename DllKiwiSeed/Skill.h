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
	bool isPassive;			// �Ƿ��Ǳ�������
	uint64_t castRange;		// ����ʩ����Χ ָʹ�ü��ܺ���Ҫ����Ŀ�ѡ��Χ��0��ʾ������ ���Լ�Ϊ�����㣻��������ʾһ���뾶
	uint64_t castTime;		// ����ʩ��ʱ�� ָʹ�ü��ܺ���Ҫ�ȴ���ʱ�䣬0��ʾ����ȴ�
	uint64_t cooldown;		// ������ȴʱ�� ָʹ�ü��ܺ���Ҫ�ȴ���ʱ�䣬0��ʾ����ȴ�
	uint64_t limit;			// ����ʹ�ô��� ָ���ܵ�ʹ�ô���
	uint64_t recoverType;	// �������ü���ʹ�ô��������� ��ΪOnTurn, OnBattle, OnLife
	uint64_t EffectRange;	// ����Ч����Χ��Ӧ��id ָ���ܵ�Ч����Χ����xml����
	std::map<uint64_t, uint64_t> cost;	// �������� ָʹ�ü��ܺ���Ҫ���ĵ���Դ��0��ʾ��������
	// �������Ժ��������� AP���͵ĵ��غ϶�ι����ǲ���̫��imba
	std::vector<uint64_t> effect;		// ����Ч�� ָ���ܵ�Ч������xml����
};

#endif
