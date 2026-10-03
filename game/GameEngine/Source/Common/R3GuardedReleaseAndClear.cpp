// Six "release the pointer I own, then forget it" bodies:
//
//     mov  <base>            ; ecx for a member, [esp+4] for a free function
//     mov  eax,[base+OFF]
//     test eax,eax / je  ...
//     push eax / call <free> / add esp,4
//     mov  dword ptr [base+OFF],0
//     ret
//
// THREE AXES, ALL READ DIRECTLY FROM THE BYTES, and every combination that
// appears is unique -- no two members share a (receiver kind, offset, callee)
// triple, which is what makes the multi-axis reading real rather than fitted:
//
//   1. HOW THE OBJECT ARRIVES.  `mov esi,ecx` is __thiscall -- a member.
//      `mov esi,[esp+8]` (one push deep) is a pointer PARAMETER of a free
//      __cdecl function.  Counting the push against the offset the load reads
//      is the whole argument; the callee is never consulted.
//   2. WHICH FIELD.  0x18, 0, 0xC0, 0, 0x1798, 0xAF0.
//   3. WHAT FREES IT.  Four different callees; `push`/`call`/`add esp,4` makes
//      every one of them __cdecl with a single pointer argument.
//
// A FOURTH THING THE BYTES DECIDE: where the null store sits.  The forward
// branch either lands on the store or past it, and that is not cosmetic --
// `if (p) { free(p); p = 0; }` and `if (p) free(p); p = 0;` are different
// source and give different displacements.  Rva0058C470 and Rva0085EFA0 clear
// the field unconditionally; the other four clear it only inside the guard.
//
// CALLEE IDENTITY.  Two of the four callees are already named in the ledger and
// are spelled as themselves: 0x00881EB0 is `operator delete` (reached by
// writing `delete`), and _ArrayFree / _qr2_shutdown are extern "C" declarations
// whose decorated names are the pins.  0x00881EF0 is retail's ARRAY form of the
// delete operator, ?_V@YAXPAX@Z, and WWLib/mem_ops.cpp owns that body.  MSVC
// 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z (the body at 0x00881EB0)
// unless the array form is declared where it can see it, so it is declared
// here and both sites that free a buffer at 0x00881EF0 now write `delete[]`,
// the spelling every other matched TU with that callee uses.  All the call
// site proves is a __cdecl function of one pointer.
//
// The indirect `call dword ptr [0x013593A0]` in Rva00382AA0 is MSVCR71's
// `fclose`: 0x013593A0 is that import's IAT slot (targets/game/reverse/
// imports.csv) and the callee pops its one pointer argument with `ret 4`.
// Retail's original TU linked the DLL CRT, so _DLL is defined before the CRT
// headers to reproduce the dllimport (IAT-indirect) call, as StringBase.cpp
// does for the same reason.
//
// IDENTITY IS NOT RECOVERED: class names are the RVA of the body, the owning
// field is named for its offset, and the leading filler is not a claim that
// anything else lives there.

#define _DLL
#include <stdio.h>
#include <new>

void operator delete[]( void *block );

extern "C" void ArrayFree( void * );
extern "C" void qr2_shutdown( void * );

struct Rva00382AA0Payload { int m_00; };

// ------------------------------------------------------------ member receivers

class Rva00382AA0
{
public:
	void release();
	char m_lead[0x18];
	void *m_18;
};
void Rva00382AA0::release()
{
	if ( m_18 )
	{
		fclose( (FILE *)m_18 );
		m_18 = 0;
	}
}

class Rva0058C470
{
public:
	void release();
	Rva00382AA0Payload *m_00;
};
void Rva0058C470::release()
{
	if ( m_00 )
		delete m_00;
	m_00 = 0;
}

class Rva00728A30
{
public:
	void release();
	char m_lead[0xC0];
	void *m_C0;
};
void Rva00728A30::release()
{
	if ( m_C0 )
	{
		delete[] m_C0;
		m_C0 = 0;
	}
}

// -------------------------------------------------------- pointer-parameter

class Rva007E2E20Owner
{
public:
	void *m_00;
};
void Rva007E2E20( Rva007E2E20Owner *owner )
{
	if ( owner->m_00 )
	{
		delete[] owner->m_00;
		owner->m_00 = 0;
	}
}

class Rva0085EFA0Owner
{
public:
	char m_lead[0x1798];
	void *m_1798;
};
void Rva0085EFA0( Rva0085EFA0Owner *owner )
{
	if ( owner->m_1798 )
		ArrayFree( owner->m_1798 );
	owner->m_1798 = 0;
}

class Rva00866770Owner
{
public:
	char m_lead[0xAF0];
	void *m_AF0;
};
extern "C" void piStopReporting( Rva00866770Owner *owner )
{
	if ( owner->m_AF0 )
	{
		qr2_shutdown( owner->m_AF0 );
		owner->m_AF0 = 0;
	}
}
