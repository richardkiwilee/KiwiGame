#include <stdint.h>

struct DamageResult
{
	int64_t src;
	int64_t dst;
	bool hit;
	bool critical;
	int damage;
	int damageType;
};

