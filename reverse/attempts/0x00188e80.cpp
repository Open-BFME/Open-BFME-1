// ?method@Rva00188E80@@YG_NPAVObject@@0@Z
// partial score=0.18 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include <vector>

enum WeaponSlotType { RvaPrimaryWeaponSlot = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };

class Weapon;
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
};

class Weapon
{
public:
	float bfmeEstimate(const Object *source, const Object *victim) const;
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *victim);
};

class AICommandInterface
{
public:
	void bfmeCommand3C(Object *victim, CommandSourceType source);
};

struct Rva00188E80Entry
{
	int m_object;
	int m_distanceBits;
};

struct Rva00188E80Payload
{
	_STL::vector<Rva00188E80Entry> m_entries;
	Rva00188E80Entry *m_cursor;
	int m_refCount;
};

struct BfmeWideResult
{
	Rva00188E80Payload *m_value;
	~BfmeWideResult()
	{
		if (--m_value->m_refCount == 0)
			delete m_value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;
extern const float BfmeZeroRange;

struct Rva00188E80Filter
{
	unsigned int m_vptr;
	void *m_next;
	Object *m_source;
	unsigned char m_flag;

	Rva00188E80Filter(Object *source)
	{
		m_next = 0;
		m_vptr = 0x01097154;
		m_source = source;
		m_flag = 0;
	}

	~Rva00188E80Filter()
	{
		m_vptr = 0x01083B5C;
	}
};

namespace Rva00188E80
{
bool __stdcall method(Object *source, Object *target)
{
	if (*(void **)((char *)source + 0x214) == 0)
		return false;

	float dx = *(float *)((char *)source + 0x38) - *(float *)((char *)target + 0x38);
	float dy = *(float *)((char *)source + 0x3c) - *(float *)((char *)target + 0x3c);
	float initialDistance = sqrtf(dx * dx + dy * dy);
	Weapon *weapon = source->getCurrentWeapon(0);
	if (weapon == 0)
		return false;

	float limit = weapon->bfmeEstimate(source, target);
	if (initialDistance <= limit)
		limit = initialDistance;

	Rva00188E80Filter filter(source);
	union { float real; int bits; } limitBits;
	limitBits.real = limit;
	BfmeWideResult result = reinterpret_cast<BfmeWideForwardC *>(ThePartitionManager)->bfmeForwardWideC(
		0, (int)&filter, 1, limitBits.bits, (int)((char *)target + 0x38));

	Rva00188E80Payload *payload = result.m_value;
	Rva00188E80Entry *cursor = payload->m_cursor;
	Rva00188E80Entry *finish = payload->m_entries.end();
	Object *best = 0;
	float bestDistance = 0.0f;
	while (cursor != finish)
	{
		Rva00188E80Entry *entry = cursor++;
		payload->m_cursor = cursor;
		Object *candidate = (Object *)entry->m_object;
		if (candidate == 0)
			continue;

		float selfDx = *(float *)((char *)source + 0x38) - *(float *)((char *)candidate + 0x38);
		float selfDy = *(float *)((char *)source + 0x3c) - *(float *)((char *)candidate + 0x3c);
		float selfDistance = sqrtf(selfDx * selfDx + selfDy * selfDy);
		selfDistance -= *(float *)((char *)source + 0xbc);
		selfDistance -= *(float *)((char *)candidate + 0xbc);
		if (selfDistance < BfmeZeroRange)
			selfDistance = BfmeZeroRange;

		float targetDx = *(float *)((char *)target + 0x38) - *(float *)((char *)candidate + 0x38);
		float targetDy = *(float *)((char *)target + 0x3c) - *(float *)((char *)candidate + 0x3c);
		float targetDistance = sqrtf(targetDx * targetDx + targetDy * targetDy);
		targetDistance -= *(float *)((char *)target + 0xbc);
		targetDistance -= *(float *)((char *)candidate + 0xbc);
		if (targetDistance < BfmeZeroRange)
			targetDistance = BfmeZeroRange;

		float candidateRadius = *(float *)((char *)candidate + 0xbc);
		volatile float *radiusScale = (volatile float *)0x0109B46C;
		if (selfDistance + candidateRadius * *radiusScale > limit)
			continue;
		if (sqrtf(targetDistance) + selfDistance > limit)
			continue;
		if (best == 0 || selfDistance < bestDistance)
		{
			best = candidate;
			bestDistance = selfDistance;
		}
	}

	if (best == 0)
		return false;
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)source + 0x204);
	ai->setCurrentVictim(best);
	((AICommandInterface *)((char *)ai + 0x20))->bfmeCommand3C(best, CMD_FROM_AI);
	return true;
}
}
