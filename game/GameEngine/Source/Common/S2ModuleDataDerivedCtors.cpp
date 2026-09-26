// Three __thiscall constructors that run one base constructor, install their own
// vptr, and then assign a small fixed set of members in the constructor BODY:
//
//     push esi / mov esi,ecx / call <REL32> / [xor eax,eax]
//     mov dword ptr [esi],<VFTABLE> / <member stores> / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  The vptr goes in immediately after the base
// constructor and before every member store, which is the order MSVC 7.1 always
// uses.  The stores that follow are NOT in ascending offset order -- three rows
// write +0xB4 before +0x04 -- so they are assignments in a constructor body, in
// source order, and not a member-initialiser list, which MSVC would reorder to
// declaration order.  Where a zero is written more than once it is hoisted into
// eax first (`xor eax,eax`), which is why the fourth row carries that
// instruction and the other three, with a single zero, do not.
//
// ONE BASE, THREE VFTABLES.  All three call the same base constructor at
// 0x000426E0 and store three different vftable addresses.
//
// A FOURTH SIBLING, 0x00429A40, IS THE SAME SHAPE WITH THREE MEMBER STORES AND
// IS NOT CLAIMED HERE.  Retail keeps its vptr store first; MSVC 7.1 sinks it
// past the first two member stores no matter how the source is written -- body
// assignments in either order, a member-initialiser list on the derived class,
// or a plain pointer member at offset 0 instead of a vptr all produce the same
// b4/b8/vptr/bc schedule.  Two member stores keep the vptr in front (the three
// rows below), three do not.  What restores it is not known.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, and the constants
// 9, 1 and 6 are written as plain ints because a dword immediate cannot tell an
// int from an enum.

class GenBase000426E0
{
public:
	GenBase000426E0();
	virtual void keep();
	int m_kind;
	char m_gap[ 0xB4 - 8 ];
	int m_flag;
};

#define BFME_MODULE_DATA_CTOR( NAME, FLAG, KIND )                         \
	class NAME : public GenBase000426E0                                   \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_flag = FLAG;                                                    \
		m_kind = KIND;                                                    \
	}

// @??0Rva004286B0@@QAE@XZ 0x004286B0
BFME_MODULE_DATA_CTOR( Rva004286B0, 0, 9 )
// @??0Rva00428980@@QAE@XZ 0x00428980
BFME_MODULE_DATA_CTOR( Rva00428980, 0, 1 )
// @??0Rva00429980@@QAE@XZ 0x00429980
BFME_MODULE_DATA_CTOR( Rva00429980, 1, 6 )
