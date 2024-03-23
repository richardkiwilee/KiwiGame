#pragma once
#include <list>
class IKiwiCoreManager
{
public:
	virtual ~IKiwiCoreManager() = default;
	virtual void Init() = 0;
	virtual void CreateQuadMap(int x, int y) = 0;
	virtual void LoadQuadMap(char* path) = 0;
	virtual void Save(char* path) = 0;
	virtual void Load(char* path) = 0;
private:
	IQuadMap * m_quadMap;
	std::list<IUnit*> units;
	std::list<IUnit*> enemies;
	std::list<IBuilding*> buildings;
};

class IBuilding
{
public:

};

enum TerrainType 
{
	Plain,
	Mountain,
	Water,
	Sand,
	Snow,
	Desert,
	Stone,
};

struct QuadCell
{
	int terrain;
	int entity;
	int ground_effect;
	int spatial_effect;
	int brightness;
	IUnit* unit;
};

class IQuadMap
{
public:
	virtual ~IQuadMap() = default;
	virtual void Create(__int64 seed) = 0;
	virtual char* Dump() = 0;
	virtual void Load(char* data) = 0;
	virtual void Update(int x, int y, int z, QuadCell* cell) = 0;
	virtual QuadCell* GetCell(int x, int y, int z) = 0;
};

class IUnitAttribute
{
public:
	virtual ~IUnitAttribute() = default;
};

class IUnit
{
public:
	virtual ~IUnit() = default;
	virtual bool hasSight(QuadCell* cell) = 0;
	virtual QuadCell* GetPosition() = 0;
	virtual bool reachable(QuadCell* cell) = 0;
	virtual void MoveTo(QuadCell* cell) = 0;
	virtual void BlinkTo(QuadCell* cell) = 0;
	virtual bool CastSkill(char* skill, QuadCell* cell) = 0;
	IUnitAttribute * hp;						// ����ֵ	
	IUnitAttribute* mp;							// ħ��ֵ
	IUnitAttribute* ap;							// �ж���
	IUnitAttribute* jump;						// ��Ծ��
	IUnitAttribute* mv;							// �ƶ���
	IUnitAttribute* strength;					// ����
	IUnitAttribute* dexterity;					// ����
	IUnitAttribute* intelligence;				// ����
	IUnitAttribute* criticalrate;				// ������
	IUnitAttribute* criticalbonus;				// ��������
	IUnitAttribute* balance;					// �ȶ���
	IUnitAttribute* evasion;					// ������
	IUnitAttribute* precision;					// ��׼��
	IUnitAttribute* armor;						// ����
	IUnitAttribute* phydef;						// �￹
	IUnitAttribute* magdef;						// ħ��
	IUnitAttribute* protection;					// ����
	IUnitAttribute* penetration;				// ��͸

	IUnitAttribute* hittheblot;					// �������
	IUnitAttribute* helpless;					// ������Ԯ
	IUnitAttribute* multiattack;				// ��������
	IUnitAttribute* comboattack;				// ��������
	IUnitAttribute* vertigo_possibility;		// ѣ�θ���
	IUnitAttribute* barge;						// ���ֱײ
	IUnitAttribute* skillrange;					// ���ܷ�Χ

};
