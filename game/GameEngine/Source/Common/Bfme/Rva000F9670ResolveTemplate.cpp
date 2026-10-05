// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x000F9670 (32 bytes).  The receiver is the same 0x60-byte record
// vector whose checked element accessor is matched at 0x000F94B0.  Each
// record begins with the AsciiString passed to the global ThingFactory.
// Retail callers at 0x000FE476, 0x0029D980, and 0x004A6021 consume EAX as a
// pointer, proving the return ABI; the first pushes it directly into the next
// call and the latter two store/use it.  A relocation-wildcard scan finds this
// complete instruction shape only at 0x000F9670, followed by INT3 padding.

#include "ascii_string.h"

class ThingTemplate;
// The canonical retail type of the 0x012EF1D8 singleton; only ever used as a
// pointee, so a forward declaration is enough.  The definition lives in
// game_engine_subsystems.h.
class ThingFactory;

// Existing matched BFME ABI view of the retail ThingFactory body at
// 0x00137E80.  Kept as a TU-local view of the same object; the canonical
// global is declared with its own type and the view is applied at the use.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// Canonical global at 0x012EF1D8
// (?TheThingFactory@@3PAVThingFactory@@A), defined once in
// game/GameEngine/Source/Common/Thing/ThingFactory.cpp.
extern ThingFactory *TheThingFactory;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeElemVLH
{
	AsciiString m_name;
	unsigned char m_opaque04[0x5c];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int index);
	const ThingTemplate *rva000F9670(int index);

private:
	int m_opaque00;
	BfmeElemVLH *m_begin;
	BfmeElemVLH *m_end;
};

// ?rva000F9670@BfmeVecVLH@@QAEPBVThingTemplate@@H@Z
const ThingTemplate *BfmeVecVLH::rva000F9670(int index)
{
	BfmeElemVLH *record = bfmeAtVLH(index);
	if (record == 0)
	{
		// This intrinsic emits no instruction.  It preserves retail's null
		// fallthrough block ahead of the non-null tail call under MSVC 7.1.
		_ReadWriteBarrier();
		return 0;
	}

	return ((BfmeThingFactory *)TheThingFactory)->findTemplate(record->m_name);
}

extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

struct Rva00367E30Logic
{
	char m_prefix[0x3c];
	UnsignedInt m_frame;
};

extern const Real g_rva01075350;
extern Real g_bfmeDefaultBU;
extern const Real g_bfmeUint32Scale;
extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva000F9780
{
public:
	Real method(Int index);

private:
	char m_prefix[0x10];
	void *m_pointer10;
};

// ?method@Rva000F9780@@QAEMH@Z
Real Rva000F9780::method(Int index)
{
	BfmeElemVLH *record = ((BfmeVecVLH *)this)->bfmeAtVLH(index);
	if (record == 0)
	{
		_WriteBarrier();
		return g_rva01075350;
	}

	Int *startFrame = (Int *)(record->m_opaque04 + (0x30 - 4));
	if (*startFrame == -1)
		return g_rva01075350;

	void *pointer = m_pointer10;
	const ThingTemplate *tmplate =
		((BfmeThingFactory *)TheThingFactory)->findTemplate(record->m_name);
	if (tmplate != 0)
	{
		Int buildTime = (Int)(long)((BfmeUseB980 *)tmplate)->bfmeApply980B(
				(Int)(long)pointer,
				*(Int *)(record->m_opaque04 + (0x34 - 4)));
		if (buildTime > 0)
			return ((Real)(UnsignedInt)TheBfmeGameLogic->m_frame - *startFrame) /
				(Real)buildTime;
	}
	return g_bfmeDefaultBU;
}
