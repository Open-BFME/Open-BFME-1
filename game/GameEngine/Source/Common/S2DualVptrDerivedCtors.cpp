// cl: -Igame/GameEngine/Source/Common/System -Igame/Libraries/Source/WWVegas/WWLib -Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Two __thiscall constructors of classes with TWO polymorphic bases, whose
// whole body is the base constructor and the three vptr stores that follow it:
//
//     push esi / mov esi,ecx / call <REL32>
//     mov dword ptr [esi+8],<VFTABLE-OF-SECOND-BASE>
//     mov dword ptr [esi],<OWN-VFTABLE-FOR-FIRST>
//     mov dword ptr [esi+8],<OWN-VFTABLE-FOR-SECOND>
//     mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  The slot at +8 is written twice, first with one address
// and then with another, which is exactly what a second base with an inline
// (compiler-generated) constructor followed by the derived class's own vptr
// fix-up looks like.  Only ONE base constructor is called, so the other base
// has no user-written constructor; the base at +8 puts the first base's size at
// eight bytes -- a vptr and one dword.  Nothing else is initialised.
//
// THE SECOND BASE IS SHARED.  Both rows store 0x01073744 into +8 before their
// own fix-up, so both derive from the same second base; the called base
// constructor 0x009A1A30 is already pinned in targets/game/reverse/symbols.csv.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The bytes do not say
// what the two bases are called, nor whether the derived classes add virtuals
// of their own -- only that each has its own vftable for each base.

// The called base constructor 0x009A1A30 is SubsystemInterface's constructor
// (ledger row ??0SubsystemInterface@@QAE@XZ, source
// game/GameEngine/Source/Common/System/SubsystemInterface.cpp), so the base is
// declared by the real header instead of a TU-local address-derived stand-in.
// Its subobject is still eight bytes -- vptr plus the four-byte AsciiString
// m_name -- so the second base still lands at +8 and the three vptr stores
// keep their retail offsets.
#include "Lib/BaseType.h"
#include "subsystem_interface.h"

class GenBase01073744
{
public:
	virtual void keepSecond();
};

#define BFME_DUAL_VPTR_CTOR( NAME )                                       \
	class NAME : public SubsystemInterface, public GenBase01073744        \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void keepOwn();                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
	}

// @??0Rva001129B0@@QAE@XZ 0x001129B0
BFME_DUAL_VPTR_CTOR( Rva001129B0 )
// @??0Rva00694E00@@QAE@XZ 0x00694E00
BFME_DUAL_VPTR_CTOR( Rva00694E00 )
