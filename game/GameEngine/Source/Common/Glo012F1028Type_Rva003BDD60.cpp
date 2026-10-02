// cl: /DNDEBUG /MD /EHsc
//
// Glo012F1028Type::rva003BDD60, retail 0x003BDD60, 120 bytes.
//
// Returns 0 when the +0x28 subobject is nil, else the signed min of that
// subobject's +0x38 value and (large limit - base limit), where both limits
// are picked from TheWritableGlobalData by the same
// TheLivingWorldCampaignManager +0x1C flag test, emitted twice.
//
// Owner: the 0x0000353F ILT is called as a Glo012F1028Type member by the
// named BfmePlayerMapState::bfmeNewMap path (0x000C7A30), and the landed
// Glo012F1028Type_Rva003BDA10.cpp witnesses the same +0x28 subobject field.
// The method spelling stays address-derived; the subobject's +0x38 value is
// likewise opaque.
//
// Shape note: every limit read goes through the TheWritableGlobalData global
// directly; none of them caches it in a local pointer.  MSVC 7.1 then CSEs the
// four loads into one EDX temp it treats as live across the second selection,
// so it loads the selected base into ECX rather than destructively
// overwriting EDX, and therefore subtracts before loading the subobject
// value.  Holding the pointer in a local reverses both and costs seven bytes
// at +0x43..+0x55 -- the residue fifteen earlier attempts stalled on.

class Glo012F1024Type
{
public:
	char m_bfmeHead[0x1C];
	bool m_bfmeUseHigh;
};

class Glo012ED5C8Type
{
public:
	char m_bfmeHead[0xE70];
	int m_bfmeLow;
	int m_bfmeHigh;
	char m_bfmeGap[0x40];
	int m_bfmeLowLarge;
	int m_bfmeHighLarge;
};

class Rva003BDD60Sub
{
public:
	char m_bfmeHead[0x38];
	int m_rva003BDD60Value;
};

class Glo012F1028Type
{
public:
	int rva003BDD60(void);

private:
	char m_bfmeHead[0x28];
	Rva003BDD60Sub *m_bfmeSub;
};

// Retail's global at 0x012F1024 is EA's LivingWorldCampaignManager singleton,
// defined once in GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldCampaignManager.cpp, so this reference carries that canonical type
// (class, not struct); the local view above is cast in at its uses.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

// Canonical identity of the retail global at 0x012ED5C8, defined once by
// game/GameEngine/Source/Common/GlobalData.cpp as
// ?TheWritableGlobalData@@3PAVGlobalData@@A.  The field reads keep the local
// view and cast at each use: caching the pointer in a local would change the
// emitted shape (see the shape note above).
class GlobalData;
extern GlobalData *TheWritableGlobalData;

// ?rva003BDD60@Glo012F1028Type@@QAEHXZ
int Glo012F1028Type::rva003BDD60(void)
{
	Rva003BDD60Sub *child = m_bfmeSub;
	if (child != 0)
	{
		Glo012F1024Type *state = (Glo012F1024Type *)TheLivingWorldCampaignManager;
		int flag = state != 0 ? state->m_bfmeUseHigh : 0;
		int limit;
		int offset;
		if (state != 0 && flag != 0)
		{
			limit = ((Glo012ED5C8Type *)TheWritableGlobalData)->m_bfmeHighLarge;
		}
		else
		{
			limit = ((Glo012ED5C8Type *)TheWritableGlobalData)->m_bfmeLowLarge;
		}
		flag = state != 0 ? state->m_bfmeUseHigh : 0;
		if (state != 0 && flag != 0)
			offset = ((Glo012ED5C8Type *)TheWritableGlobalData)->m_bfmeHigh;
		else
			offset = ((Glo012ED5C8Type *)TheWritableGlobalData)->m_bfmeLow;

		int value;
		int difference;
		difference = limit - offset;
		value = child->m_rva003BDD60Value;
		return *((value < difference) ? &value : &difference);
	}
	return 0;
}
