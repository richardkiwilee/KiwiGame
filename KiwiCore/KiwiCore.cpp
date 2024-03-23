#include "IKiwiCore.h"
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif // _WIN32

class KiwiCoreManager : public IKiwiCoreManager
{
public:

};

class QuadMap : public IQuadMap
{
public:
};

class Skill : public ISkill
{
public:

};

class Unit : public IUnit
{
public:

};

extern "C" {
	DLL_EXPORT IKiwiCoreManager* CreateKiwiCoreManager()
	{
		return new KiwiCoreManager();
	}
	DLL_EXPORT IQuadMap* CreateQuadMap()
	{
		return new QuadMap();
	}
	DLL_EXPORT ISkill* CreateSkill()
	{
		return new Skill();
	}
	DLL_EXPORT IUnit* CreateUnit()
	{
		return new Unit();
	}
}