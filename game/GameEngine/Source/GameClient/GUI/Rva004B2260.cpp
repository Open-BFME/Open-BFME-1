// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib 

// This retail helper adjusts template damage values by an object's rounded bonus.
// Static linkage preserves the private register inputs used by its caller.
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>

#define OBJECT_TU_MEMBERS bool getAttributeModifierBonus(int, float *) const;
#include "../../GameLogic/Object/object.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);

template<class T>
inline T &field004B2260(void *pointer, unsigned offset)
{
	return *(T *)((char *)pointer + offset);
}

// ?Rva004B2260@@YAXPAVObject@@PAXAAH2@Z
static __declspec(noinline) void Rva004B2260(Object *object, void *templ,
	int &melee, int &ranged)
{
	float bonus;
	if (!object->getAttributeModifierBonus(2, &bonus))
		bonus = 0;
	int value = (int)floor(bonus + 0.5f);
	melee = field004B2260<int>(templ, 0x470);
	if (melee >= 0)
		melee += value;
	ranged = field004B2260<int>(templ, 0x474);
	if (ranged >= 0)
		ranged += value;
}

// This caller exists only to make the compiler emit the helper's private convention.
// ?Rva004B2260Caller@@YAXPAVObject@@PAXAAH2@Z absent-from-retail
void Rva004B2260Caller(Object *object, void *templ, int &melee, int &ranged)
{
	Rva004B2260(object, templ, melee, ranged);
}

// Retail 0x004B21C0 (23 B): file-static rounded value of the object held at owner+0x200
// (0 when absent); the owner arrives in EAX through the private static convention and
// the float result tail-calls _ftol2. Owner and value types are address-named.
class Rva004B21C0Value
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual float slot18();
};

class Rva004B21C0Owner
{
public:
	unsigned char m_unmodelled000[0x200];
	Rva004B21C0Value *m_value200;
};

static int Rva004B21C0(const Rva004B21C0Owner *owner)
{
	Rva004B21C0Value *value = owner->m_value200;
	if (value)
		return (int)value->slot18();
	return 0;
}

// absent-from-retail: TU-local caller that keeps the static above alive.
int Rva004B21C0Caller(const Rva004B21C0Owner *owner)
{
	return Rva004B21C0(owner);
}
