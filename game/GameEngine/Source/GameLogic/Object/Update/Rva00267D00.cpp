// ?m00267D00@Rva00267D00@@QAEXD@Z
// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail tests Object+0x130 bit 11, clears it, then calls the model-condition
// notifier. The 320-bit condition array begins at Object+0x110, so this is bit 267.
// Retail also reads the FXList pointer at this+4 plus 0x264 and the Object pointer
// at this+8. No evidence proves a semantic owner for this method, so its name keeps
// the RVA.
//
// The SpecialDisguiseUpdate vtable slot 15 body at 0x00267D80 calls ILT 0x00020847
// with ECX=this and one byte argument. Its target at 0x00267B10 returns with ret 4.
// The call names the ledger's exact ILT entry and keeps its unsigned-byte ABI.

typedef bool Bool;
typedef int Int;
typedef float Real;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

class Rva00267D00ConditionBits
{
public:
	Bool test(Int bit) const { return bits.test(bit); }
	void reset(Int bit) { bits.reset(bit); }

private:
	_STL::bitset<320> bits;
};
typedef char Rva00267D00ConditionBitsSize[
	(sizeof(Rva00267D00ConditionBits) == 40) ? 1 : -1];

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;

class FXList
{
public:
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primaryScale, const Coord3D *secondary) const;
};

class Object
{
public:
	void notifyModelConditionChanged(void);

	unsigned char m_unmodelled_000[0x38];
	Coord3D m_coord038;
	unsigned char m_unmodelled_044[0x110 - 0x44];
	Rva00267D00ConditionBits m_bits110;
};

static __forceinline Bool clearRva00267D00ModelCondition(Object *object)
{
	if (!object->m_bits110.test(267))
		return false;
	object->m_bits110.reset(267);
	object->notifyModelConditionChanged();
	return true;
}

class Rva00267D00Data
{
public:
	unsigned char m_unmodelled_000[0x264];
	const FXList *m_fx264;
};

class Rva00267B10
{
public:
};

class Rva00267D00
{
public:
	void m00267D00(char quiet);

	unsigned char m_unmodelled_000[4];
	const Rva00267D00Data *m_moduleData;
	Object *m_object;
};

extern "C" void __cdecl __identifier("?j_00020847@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00011f77@@YAXXZ")();

void Rva00267D00::m00267D00(char quiet)
{
	union { void (*raw)(); void (Rva00267B10::*member)(unsigned char); }
		notify = { __identifier("?j_00020847@@YAXXZ") };
	union { void (*raw)(); Bool (FXList::*member)() const; }
		blocked = { __identifier("?j_00011f77@@YAXXZ") };
	Object *obj = m_object;
	if (!clearRva00267D00ModelCondition(obj))
		return;

	if (quiet != 0)
		return;

	(((Rva00267B10 *)this)->*notify.member)(1);

	const FXList *fx = m_moduleData->m_fx264;

	if (fx == 0)
		return;

	if ((fx->*blocked.member)())
		return;

	fx->doFXPos(&obj->m_coord038, 0, 0.0f, 0);
}
