// cl: /DNDEBUG -Igame/GameEngine/Source/Common -Igame/Libraries/Source/WWVegas/WWLib
// 26 identical 18-byte __thiscall constructors:
//
//     push esi / mov esi,ecx / call <REL32> / mov dword ptr [esi],<DIR32>
//     mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  ecx is saved once, a single subobject constructor runs
// on the SAME pointer (no `lea`, so the base sits at offset 0), the vptr slot at
// offset 0 is then overwritten with this class's own vftable, and `this` is
// returned in eax.  A base at offset 0 whose vptr slot is rewritten afterwards
// means the BASE is already polymorphic; the derived class adds no data members
// of its own -- any member initialiser would appear as a further store here, and
// none does.
//
// TWO AXES, both read directly: the REL32 base constructor and the DIR32
// vftable.  Thirteen distinct base constructors are shared across the 26
// members, so each base class below is declared once and the pin is reused.
// The vftable operand is compiler-generated per class and needs no pin.
//
// Eight of the twenty-six call their base through a low-RVA incremental-link
// thunk; the pins name the BODY, which is what build_call_thunks() expands.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.
//
// FOUR ARE STILL MISNAMED AND CANNOT BE FIXED HERE.  In the vftables the ctors of
// Rva00324490, Rva006709F0, Rva0081C500 and Rva009CC350 install (0x010E1F44,
// 0x0111A394, 0x0112CC60, 0x01143B40) slot 0 holds a SCALAR DELETING DESTRUCTOR
// of the class itself -- 0x00324570, 0x00670E90, 0x0081C530, 0x009CC440 -- so
// `handle` stands in for their own virtual destructor.  Spelling that slot means
// naming the class after its real destructor, which renames this file's
// constructors and breaks the ledger rows that key on ??0Rva00324490@@QAE@XZ and
// its three siblings.  That is a ledger change, not a source one, so `handle`
// stands in until then.

// THE FOUR THAT INHERIT THEIR VFTABLE SLOT 0.  A class whose vftable slot 0 is
// not its own has an inherited virtual there, and a stand-in member cannot spell
// it.  The four members below whose base is GenBase00944940 (retail:
// SimpleSceneClass, ctor 0x00944940) are those: the vftables their ctors
// install -- 0x01120850, 0x01120B08, 0x01126C28, 0x011279A0 -- all hold the ILT
// thunk 0x00005D5D at slot 0, and that thunk jumps to 0x005F38C0, the body the
// ledger calls ?Delete_This@RefCountClass@@UAEXXZ.  RefCountClass is a real type
// with a real header (game/Libraries/Source/WWVegas/WWLib/refcount.h), so the
// slot is spelled with it: the base derives from it and adds no virtual, and the
// four members use the derived macro that declares none.  Retail's slot 1 is
// each class's own scalar deleting destructor (0x006FD6C0, 0x00712100,
// 0x007898C0, 0x0079D360), which is why the compiler emits that slot too.
// The base class itself keeps the stand-in name, because the ctor really is
// retail's 0x00944940 body and the pin spells it that way.
// GenBase009A1A30's body is retail's 0x009A1A30, which the ledger carries as
// ??0SubsystemInterface@@QAE@XZ (game/GameEngine/Source/Common/System/
// SubsystemInterface.cpp), so the eight classes that derive from it derive from
// the real header instead of a TU-local stand-in.  Its subobject is the same
// eight bytes -- vptr plus the four-byte AsciiString m_name -- and the derived
// classes add no members, so every constructor keeps its retail offsets and its
// 18-byte shape.  The base's own vftable slot 0 is its destructor, so the
// derived classes leave `handle` as the only virtual they add of their own.
// This comes before refcount.h so <vector>/<utility> reach <new> first, and
// __PLACEMENT_VEC_NEW_INLINE (the spelling other BFME TUs use) keeps <new> from
// defining a second placement operator new[] that always.h has already defined.
#define __PLACEMENT_VEC_NEW_INLINE
typedef bool Bool;
#include "System/subsystem_interface.h"

#include "../../../Libraries/Source/WWVegas/WWLib/refcount.h"

#define BFME_VPTR_BASE( NAME )                                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
	};

#define BFME_VPTR_DERIVED( NAME, BASE )                                   \
	class NAME : public BASE                                              \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
	}

// A derived class that adds no virtual of its own: every slot in its vftable is
// named by a base, so declaring one here would misname all of them.
#define BFME_VPTR_DERIVED_INHERITED( NAME, BASE )                          \
	class NAME : public BASE                                              \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
	}

// ??0GenBase009EB7D0@@QAE@XZ
// This base is the one non-empty member of the otherwise vptr-only family.
// Keep the halfword clear and the bitfield updates in their retail order;
// the late vptr write is the base constructor's own vftable store.
extern "C" char GenBase009EB7D0_vtbl;

class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	virtual void handle();

private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

GenBase009EB7D0::GenBase009EB7D0()
{
	unsigned char *base = reinterpret_cast<unsigned char *>(this);
	unsigned int value;

	*reinterpret_cast<unsigned short volatile *>(base + 4) = 0;
	value = *reinterpret_cast<unsigned int volatile *>(base + 4);
	value &= 0xff07ffffu;
	value |= 0x00070000u;
	*reinterpret_cast<unsigned int volatile *>(base + 4) = value;
	value &= 0xf8ffffffu;
	*reinterpret_cast<char *volatile *>(base) = &GenBase009EB7D0_vtbl;
	*reinterpret_cast<unsigned int volatile *>(base + 4) = value;
	*reinterpret_cast<unsigned int volatile *>(base + 8) = 0;
	*reinterpret_cast<unsigned int volatile *>(base + 0xc) = 0;
	*reinterpret_cast<unsigned int volatile *>(base + 0x10) = 0;
}

BFME_VPTR_BASE( GenBase00101D50 )
BFME_VPTR_BASE( GenBase00101E20 )
BFME_VPTR_BASE( GenBase00138960 )
BFME_VPTR_BASE( GenBase002DF2B0 )
BFME_VPTR_BASE( GenBase003BB1E0 )
BFME_VPTR_BASE( GenBase0046E5E0 )
BFME_VPTR_BASE( GenBase00479230 )
BFME_VPTR_BASE( GenBase004B2C80 )
BFME_VPTR_BASE( GenBase008AD3F0 )
BFME_VPTR_BASE( GenBase009CA9E0 )

// The eight that ran retail's 0x009A1A30 now derive from the real
// SubsystemInterface. init/reset/update stay pure, as retail's bodies for them are
// not in this TU; the classes are only ever constructed, never instantiated, so
// the abstractness costs nothing and the constructor keeps its 18 bytes.
#define BFME_VPTR_DERIVED_SUBSYSTEM( NAME )                                 \
	class NAME : public SubsystemInterface                                 \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
	}

// ??0GenBase00944940@@QAE@XZ -- the base of the four Rva* below.  Its own vftable
// (0x011135AC) starts with the same RefCountClass::Delete_This thunk, so it adds
// no virtual of its own either; the ctor name stays the pinned stand-in because
// the ctor really is retail's 0x00944940 body.
class GenBase00944940 : public RefCountClass
{
public:
	GenBase00944940();
};

BFME_VPTR_DERIVED_SUBSYSTEM( Rva0006B0D0 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva000C3FF0 )
BFME_VPTR_DERIVED( Rva002DCE70, GenBase002DF2B0 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva002ED840 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva00322090 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva00324490 )
BFME_VPTR_DERIVED( Rva003BB2E0, GenBase003BB1E0 )
BFME_VPTR_DERIVED( Rva003BB310, GenBase003BB1E0 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva0048CD10 )
BFME_VPTR_DERIVED( Rva005166B0, GenBase00479230 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva0063FCF0 )
BFME_VPTR_DERIVED( Rva006709F0, GenBase004B2C80 )
BFME_VPTR_DERIVED( Rva00670A10, GenBase004B2C80 )
BFME_VPTR_DERIVED( Rva006BA440, GenBase00101E20 )
BFME_VPTR_DERIVED( Rva006BA470, GenBase00101D50 )
BFME_VPTR_DERIVED( Rva006C0570, GenBase00138960 )
BFME_VPTR_DERIVED_INHERITED( Rva006FCAD0, GenBase00944940 )
BFME_VPTR_DERIVED_INHERITED( Rva00711B00, GenBase00944940 )
BFME_VPTR_DERIVED_INHERITED( Rva00789650, GenBase00944940 )
BFME_VPTR_DERIVED( Rva0078ABB0, GenBase0046E5E0 )
BFME_VPTR_DERIVED_INHERITED( Rva0079D030, GenBase00944940 )
BFME_VPTR_DERIVED_SUBSYSTEM( Rva0081C500 )
BFME_VPTR_DERIVED( Rva008BD2B0, GenBase008AD3F0 )
BFME_VPTR_DERIVED( Rva008FEB20, GenBase009EB7D0 )
BFME_VPTR_DERIVED( Rva00972880, GenBase009EB7D0 )
BFME_VPTR_DERIVED( Rva009CC350, GenBase009CA9E0 )
