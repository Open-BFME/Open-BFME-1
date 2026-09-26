// ?rvaCalcBuildProgress@Rva000F9780Owner@@QAEMH@Z
// partial score=0.6 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x000F9780, 125 bytes, __thiscall taking one Int index and cleaning
// 4 bytes (ret 4). Uses the SAME 0x60-byte record vector as the sibling
// Rva000F9670ResolveTemplate.cpp (BfmeVecVLH::bfmeAtVLH, BfmeElemVLH with an
// AsciiString name at +0, and TheThingFactory::findTemplate), so those
// declarations are repeated verbatim here. The owning object additionally
// carries a Player* at +0x10 that is not part of BfmeVecVLH itself.
//
// record->m_opaque04 offsets +0x30 (an Int "start frame", -1 = not started)
// and +0x34 (an Int passed to ThingTemplate::calcTimeToBuild as the queue
// count) are read as raw ints -- no field name is proven beyond their use
// here. calcTimeToBuild is reached through the already-landed
// BfmeUseB980::bfmeApply980B ABI-view wrapper (BfmeUseB980Apply.cpp).
//
// Progress fraction: (UnsignedInt)TheBfmeGameLogic's frame counter (read via
// the standard (Real)(UnsignedInt) idiom, see WorkerAIUpdate_construct.cpp)
// minus the start frame, divided by buildTime -- 0.0f when there is no
// record or it has not started, 1.0f when the template or buildTime cannot
// be resolved.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class ThingTemplate;
class Player;

extern const Real BfmeZeroRange;     // 0x01075350 == 0.0f
extern Real g_bfmeDefaultBU;          // 0x01075334 == 1.0f
extern const Real g_bfmeUint32Scale;  // 0x01075358 == 2^32

// Existing matched BFME ABI view of the retail ThingFactory body at
// 0x00137E80 (see Rva000F9670ResolveTemplate.cpp).
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;  // 0x012EF1D8

struct BfmeElemVLH
{
	AsciiString m_name;
	unsigned char m_opaque04[0x5c];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int index);

private:
	int m_opaque00;
	BfmeElemVLH *m_begin;
	BfmeElemVLH *m_end;
};

// ABI view of retail 0x0044B01F: tail-calls ThingTemplate::calcTimeToBuild
// through a (Player*, Int) -> void* wrapper.
class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

struct Rva00367E30Logic
{
	char m_prefix[0x3c];
	UnsignedInt m_frame;   // +0x3c
};

extern Rva00367E30Logic *TheBfmeGameLogic;  // 0x012F0898

class Rva000F9780Owner
{
public:
	Real rvaCalcBuildProgress(Int index);

private:
	char m_prefix[0x10];
	Player *m_owningPlayer;   // +0x10
};

// ?rvaCalcBuildProgress@Rva000F9780Owner@@QAEMH@Z
Real Rva000F9780Owner::rvaCalcBuildProgress(Int index)
{
	BfmeElemVLH *record = ((BfmeVecVLH *)this)->bfmeAtVLH(index);
	if (record != 0)
	{
		Int *startFrame = (Int *)(record->m_opaque04 + (0x30 - 4));
		if (*startFrame != -1)
		{
			const ThingTemplate *tmplate = TheThingFactory->findTemplate(record->m_name);
			if (tmplate == 0)
				return g_bfmeDefaultBU;

			Int quantity = *(Int *)(record->m_opaque04 + (0x34 - 4));
			Int buildTime = (Int)(long)((BfmeUseB980 *)tmplate)->bfmeApply980B(
					(Int)(long)m_owningPlayer, quantity);

			if (buildTime <= 0)
				return g_bfmeDefaultBU;

			return ((Real)(UnsignedInt)TheBfmeGameLogic->m_frame - *startFrame) / (Real)buildTime;
		}
	}

	return BfmeZeroRange;
}
