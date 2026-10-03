// The stack copy this body makes of one 0x88-byte attribute entry.  Retail
// constructs and destroys it through the five-byte ILT thunks at RVA
// 0x00024631 and 0x00043699, which the ledger owns as ?j_00024631@@YAXXZ and
// ?j_00043699@@YAXXZ (game/gen_small/thunks_017.cpp and thunks_032.cpp); both
// take the receiver in ecx, so this temporary's constructor and destructor are
// in-class bodies that dispatch to those thunks through a member-pointer union.
// That keeps the call displacements where retail has them and keeps the SEH
// frame and the two destructor calls the /EHsc unwinder needs.
//
// The temporary carries its own name because the real
// ??0BfmeAttrERT@@QAE@ABV0@@Z copy constructor already has an object of its own
// (game/GameEngine/Source/GameLogic/Object/Update/BfmeAttrERTCopyConstructor.cpp,
// the body behind thunk 0x00024631): two COMDAT definitions of one name that
// disagree are a duplicate the linker may silently resolve the wrong way.
extern void j_00024631();
extern void j_00043699();

// The entry layout, 0x88 bytes: the pool's element type, read only here.
class BfmeAttrERT
{
public:
	unsigned char m_bfmeHeadERT[0x80];
	char m_bfmeFlagERT;
	unsigned char m_bfmeTailERT[7];
};

// A view of the receiver, so the thunks can be called with this in ecx from
// inside the temporary's own inline members.
class BfmeAttrThunkOwner
{
};

typedef void (BfmeAttrThunkOwner::*AttrCopyCtorCall)(const BfmeAttrERT *source);
typedef void (BfmeAttrThunkOwner::*AttrDtorCall)();

class BfmeAttrCopyTemp
{
public:
	__forceinline BfmeAttrCopyTemp(const BfmeAttrERT &other)
	{
		union
		{
			void (*raw)();
			AttrCopyCtorCall member;
		} copy;
		copy.raw = j_00024631;
		(reinterpret_cast<BfmeAttrThunkOwner *>(this)->*copy.member)(&other);
	}

	__forceinline ~BfmeAttrCopyTemp()
	{
		union
		{
			void (*raw)();
			AttrDtorCall member;
		} destroy;
		destroy.raw = j_00043699;
		(reinterpret_cast<BfmeAttrThunkOwner *>(this)->*destroy.member)();
	}

	unsigned char m_bfmeHeadERT[0x80];
	char m_bfmeFlagERT;
	unsigned char m_bfmeTailERT[7];
};

// The twelve-byte storage global at VA 0x012F1000, named here as its own proven
// initializer TU already declares it: game/GameEngine/Source/Common/Containers/
// Rva00C6B2C0PoolInitialization.cpp (matched) references
// ?Rva00EF1000Global@@3URva00EF1000Storage@@A, and
// targets/game/reverse/identity_evidence/00c6b2c0-storage-initializer.md records
// that both lifetime ends -- ?Rva00C6B2C0Initialize@@YAXXZ (RVA 0x00C6B2C0) and the
// atexit callback ?bfmeForward_00C6FEF0@@YAXXZ (RVA 0x00C6FEF0) -- witness this one
// address, that the 15-byte callee 0x0039D5B0 clears the three words at +0/+4/+8,
// and that the cell must keep address-qualified names because "no game-level
// identity is asserted".
//
// This file previously used ?TheBfmeAttributePool@@3UBfmeAttributePool@@A.  That
// semantic spelling is one of six over-claims dir32_addresses.csv carries for this
// single address (Rva00EF1000Global, TheBfmeAttributePool with three different type
// spellings, BfmeObject_00C6FEF0, g_bfmeAttrPoolERT and g_bfmeObjEBL), it is
// defined by no object, and its narrower eight-byte view could never match a row
// declaring the proven three-word storage (the type name is inside the mangling).
// It is respelled to the address-derived name so one row serves this file and the
// initializer TU; the DIR32 target is unchanged.
struct Rva00EF1000Storage
{
	BfmeAttrERT *m_word0;
	BfmeAttrERT *m_word4;
	BfmeAttrERT *m_word8;
};

extern Rva00EF1000Storage Rva00EF1000Global;

class BfmeHostERT
{
public:
	char bfmeQueryERT();

	int m_bfmeIndexERT;
};

char BfmeHostERT::bfmeQueryERT()
{
	int index = m_bfmeIndexERT;

	if (index >= 0 &&
		index < (int)(Rva00EF1000Global.m_word4 - Rva00EF1000Global.m_word0))
	{
		BfmeAttrCopyTemp copy(Rva00EF1000Global.m_word0[index]);

		if (copy.m_bfmeFlagERT != 0)
			return 1;
	}

	return 0;
}
