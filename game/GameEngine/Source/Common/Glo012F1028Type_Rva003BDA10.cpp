// Retail 0x003BDA10 (118 bytes).
//
// The named caller is Glo012F1024Item::j_000250d6 at 0x003AD560.  At both
// call sites that body loads the global at 0x012F1028 into ECX before calling
// the 0x0001713E thunk, proving this member's receiver.  The member at +0x28
// is kept as a LivingWorldRegionManager view: its first call is the reviewed
// rva003C8160 member; the four-pointer operation at 0x003C9CB0 is the
// address-derived rva003C9CB0 member converted alongside it.
//
// Retail 0x003BD9C0 (63 bytes, ret 0xC) is the same caller's other call
// through ILT 0x00036264 (0x003AD560 +0x170 loads 0x012F1028 into ECX first):
// it hands the region and either nothing or the name plus extra to
// rva003C9CB0. Retail lays the empty-name arm first; only an inline isEmpty
// predicate (null data or zero length, cmp word [data+4]) keeps that order --
// direct field tests in either polarity or goto order put the named arm first.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003BDA10Pair
{
	int first;
	int second;
};

struct Rva003BDA10StringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

struct Rva003BDA10String
{
	Rva003BDA10StringData *m_data;

	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
};

class LivingWorldRegion
{
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8160(Coord3D *position);
	// Retail 0x003C9CB0: address-derived four-pointer method, converted in
	// LivingWorld/LivingWorldRegionManager_Rva003C9CB0.cpp (ret 0x10).
	void rva003C9CB0(void *first, void *second, void *third, void *fourth);
};

static __forceinline void callRva003C9CB0(LivingWorldRegionManager *manager,
	void *first, void *second, void *third, void *fourth)
{
	manager->rva003C9CB0(first, second, third, fourth);
}

class Glo012F1028Type
{
public:
	void rva003BDA10(Rva003BDA10Pair *pair,
		Rva003BDA10String *name, void *extra);
	void rva003BD9C0(void *region, Rva003BDA10String *name, void *extra);

private:
	char m_pad00[0x28];
	LivingWorldRegionManager *m_regionManager;
};

// ?rva003BD9C0@Glo012F1028Type@@QAEXPAXPAURva003BDA10String@@0@Z
void Glo012F1028Type::rva003BD9C0(void *region,
	Rva003BDA10String *name, void *extra)
{
	if (name->isEmpty())
		m_regionManager->rva003C9CB0(region, 0, 0, 0);
	else
		m_regionManager->rva003C9CB0(region, name, 0, extra);
}

// ?rva003BDA10@Glo012F1028Type@@QAEXPAURva003BDA10Pair@@PAURva003BDA10String@@PAX@Z
void Glo012F1028Type::rva003BDA10(Rva003BDA10Pair *pair,
	Rva003BDA10String *name, void *extra)
{
	Coord3D position;
	// The input carries two coordinate bit patterns; the callee reads floats.
	memcpy(&position, pair, 8);
	position.z = 0.0f;

	LivingWorldRegion *found =
		m_regionManager->rva003C8160(&position);
	if (found == 0)
		return;

	if (name->m_data == 0)
		goto empty;
	if (name->m_data->length == 0)
		goto empty;
	goto named;

empty:
	callRva003C9CB0(m_regionManager,
		(char *)found + 4, 0, pair, 0);
	return;

named:
	callRva003C9CB0(m_regionManager,
		(char *)found + 4, name, pair, extra);
}
