// BFME Player::getProductionTimeChangePercent, retail 0x000DA030 / 35 bytes.
// ThingTemplate::calcTimeToBuild calls this body with its Player receiver and
// ThingTemplate name.  The retail body looks up the name in the Player map at
// +0x1D8, returns the matched record's float at +8, and returns the global zero
// on a miss.  The local layout keeps that BFME map position independent of the
// shorter Zero Hour Player header.

typedef float Real;

class AsciiString
{
};

extern const float g_rva01075350;

struct BfmeResEZC
{
	unsigned char m_bfmeHead[8];
	Real m_bfmeF;
};

// The map lookup goes through the five-byte ILT thunk at 0x00037D6C, defined
// as ?j_00037d6c@@YAXXZ in game/gen_small/thunks_026.cpp (target 0x004D7180).
// The thunk declares no arguments of its own: it jumps with the thiscall `this`
// in ECX and the caller's argument already in place, leaving the record pointer
// in EAX, so the call is spelled through a thiscall member pointer of the same
// shape.
extern void j_00037d6c();

class BfmeSubEZC
{
};

typedef BfmeResEZC *(BfmeSubEZC::*bfmeFindEZCThunk)(void *a);

union BfmeFindEZCThunkCast
{
	void (__cdecl *freeFunction)(void *a);
	bfmeFindEZCThunk memberFunction;
};

class Player
{
public:
	Real getProductionTimeChangePercent(const AsciiString &buildTemplateName) const;

private:
	unsigned char m_bfmeHead[0x1D8];
	mutable BfmeSubEZC m_productionTimeChanges;
};

Real Player::getProductionTimeChangePercent(const AsciiString &buildTemplateName) const
{
	BfmeFindEZCThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(void *)>(
		&::j_00037d6c);
	BfmeResEZC *productionTimeChange = (m_productionTimeChanges.*
		cast.memberFunction)((void *)&buildTemplateName);
	if (productionTimeChange)
		return productionTimeChange->m_bfmeF;
	return g_rva01075350;
}
