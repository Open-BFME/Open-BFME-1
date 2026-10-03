// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /I.

// This retail helper adjusts template damage values by an object's rounded bonus.
// Static linkage preserves the private register inputs used by its caller.
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>

#define OBJECT_TU_MEMBERS bool getAttributeModifierBonus(int, float *) const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"

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
