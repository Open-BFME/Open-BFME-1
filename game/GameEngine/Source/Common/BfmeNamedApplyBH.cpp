// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the named apply at retail 0x002F83D0, 62 bytes.  The name is
// handed to the registry by value; nothing happens unless it resolves.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail's by-value name is retail AsciiString: one StringBase<char>, whose
// copy constructor (0x00887B60) and releaseBuffer (0x00887940) this copy
// reaches, both matched in game/Libraries/Source/string/StringBase.cpp.
class AsciiStringBH
{
public:
	AsciiStringBH(const AsciiStringBH &other) : m_value(other.m_value)
	{
	}

	~AsciiStringBH(void)
	{
	}

private:
	AsciiString m_value;
};

// Retail's two calls in this body reach incremental-link thunks, which carry
// no signature: the registry lookup through ILT 0x00020F04 and the apply
// through ILT 0x000033B4.  Both thunks are generated bodies
// (?j_00020f04@@YAXXZ in game/gen_small/thunks_015.cpp, ?j_000033b4@@YAXXZ in
// game/gen_small/thunks_001.cpp), so call those rather than the unrelated
// historical names pinned to the same ILTs.
extern void j_00020f04(void);
extern void j_000033b4(void);

class BfmeRegistryBH
{
public:
	void *bfmeFindBH(AsciiStringBH name) throw();
};

// retail 0x012ED80C is the game's TheSpecialPowerStore, so the global must carry
// that name and its pointee type.  SpecialPowerStore itself is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h; only the address
// of the global is referenced here, so a forward declaration of the pointee is
// enough and the registry view below is still reached by cast (which emits
// nothing).
class SpecialPowerStore;

extern SpecialPowerStore *TheSpecialPowerStore;	// retail 0x012ED80C

class BfmeSubBH
{
public:
	char m_bfmePadSBH[4];
};

class BfmeTargetBH
{
public:
	char m_bfmePadTBH[0x38];
	BfmeSubBH m_bfmeSubBH;
};

class BfmeApplierBH
{
public:
	void bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();

	void bfmeAddBH(void *owner, const AsciiStringBH &name, BfmeTargetBH *target);
};

typedef void *(BfmeRegistryBH::*BfmeRegistryFindFunction)(AsciiStringBH);
typedef void (BfmeApplierBH::*BfmeApplyFunction)(void *, void *, BfmeSubBH *);

void BfmeApplierBH::bfmeAddBH(void *owner, const AsciiStringBH &name,
		BfmeTargetBH *target)
{
	union
	{
		void (*raw)(void);
		BfmeRegistryFindFunction find;
	} findThunk;
	union
	{
		void (*raw)(void);
		BfmeApplyFunction apply;
	} applyThunk;

	findThunk.raw = j_00020f04;
	applyThunk.raw = j_000033b4;

	void *found =
		(((BfmeRegistryBH *)TheSpecialPowerStore)->*findThunk.find)(name);

	if (found != 0)
		(this->*applyThunk.apply)(owner, found, &target->m_bfmeSubBH);
}
