// Retail 0x003BDA10 (118 bytes).
//
// The named caller is Glo012F1024Item::j_000250d6 at 0x003AD560.  At both
// call sites that body loads the global at 0x012F1028 into ECX before calling
// the 0x0001713E thunk, proving this member's receiver.  The member at +0x28
// is kept as a LivingWorldRegionManager view: its first call is the reviewed
// rva003C8160 member; the four-pointer operation at 0x003C9CB0 is the
// address-derived rva003C9CB0 member converted alongside it.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct Coord3D
{
	float x;
	float y;
	float z;
};

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

private:
	char m_pad00[0x28];
	LivingWorldRegionManager *m_regionManager;
};

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
