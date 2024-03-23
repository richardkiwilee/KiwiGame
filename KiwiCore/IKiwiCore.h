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
	IUnitAttribute * hp;						// 生命值	
	IUnitAttribute* mp;							// 魔法值
	IUnitAttribute* ap;							// 行动力
	IUnitAttribute* jump;						// 跳跃力
	IUnitAttribute* mv;							// 移动力
	IUnitAttribute* strength;					// 力量
	IUnitAttribute* dexterity;					// 敏捷
	IUnitAttribute* intelligence;				// 智力
	IUnitAttribute* criticalrate;				// 暴击率
	IUnitAttribute* criticalbonus;				// 暴击倍率
	IUnitAttribute* balance;					// 稳定性
	IUnitAttribute* evasion;					// 闪避率
	IUnitAttribute* precision;					// 精准度
	IUnitAttribute* armor;						// 护甲
	IUnitAttribute* phydef;						// 物抗
	IUnitAttribute* magdef;						// 魔抗
	IUnitAttribute* protection;					// 减伤
	IUnitAttribute* penetration;				// 穿透

	IUnitAttribute* hittheblot;					// 趁虚而入
	IUnitAttribute* helpless;					// 孤立无援
	IUnitAttribute* multiattack;				// 连击次数
	IUnitAttribute* comboattack;				// 连锁次数
	IUnitAttribute* vertigo_possibility;		// 眩晕概率
	IUnitAttribute* barge;						// 横冲直撞
	IUnitAttribute* skillrange;					// 技能范围

};
