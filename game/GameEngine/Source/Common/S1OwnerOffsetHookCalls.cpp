// Five fifteen-byte __thiscall members that walk BACKWARDS out of themselves:
//
//     mov eax,[ecx-0x18] / push 1 / push eax / add ecx,-0x20 /
//     call <REL32> / ret
//
// WHAT THE BYTES SHOW.  ecx is adjusted by a NEGATIVE constant, so the receiver
// of the call sits 0x20 bytes BEFORE this object -- this is a helper embedded
// inside a larger object reaching back to its owner.  The loaded argument is at
// this-0x18, i.e. owner+8, and it is pushed second, so the call is
// `owner->f(owner->field, 1)`.
//
// THE CAST IS RECOVERED, NOT CHOSEN.  A C++ base/derived pointer cast cannot
// produce these bytes: MSVC 7.1 null-checks a cast across a non-primary base
// and emits `test ecx,ecx / jz ...` plus a second exit before the adjustment.
// Retail has NO null test, which only the raw form `(Owner *)((char *)this -
// 0x20)` compiles to.  So the source did pointer arithmetic, not a static_cast,
// and the eleven concrete bytes prove it.
//
// AND THE OWNER POINTER IS NOT HOISTED.  This is a same-length trap a size
// comparison cannot catch: writing `Owner *o = (Owner *)((char *)this - 0x20);`
// first and then calling through `o` produces the identical fifteen bytes with
// `add ecx,-0x20` moved AHEAD of the two pushes.  Retail adjusts ecx LAST,
// after both arguments are already on the stack, which is what the compiler
// does when the receiver is spelled inline in the call expression instead of
// being bound to a local first.  Both spellings were compiled; only this one
// matches, and the first landing attempt failed on exactly this.
//
// ALL FIVE CALL ONE CALLEE, 0x000157DA.  That address is already pinned in
// targets/game/reverse/symbols.csv by earlier work as an incremental-link thunk to
// UpdateModule::setWakeFrame(Object *, UpdateSleepTime) -- which fits (a helper
// inside an update module, handing its owner's object pointer back with a
// constant sleep mode), but that identity comes from the LEDGER, not from these
// bytes.  A dword push and a `push 1` cannot distinguish a pointer from an int
// or an enum, so the signature below is spelled in the widest, least assertive
// terms and a fresh address-derived pin is used rather than borrowing a name
// this body cannot prove.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  All five bodies are
// byte-identical apart from the displacement; the bytes cannot say whether that
// is five helper classes in one owner or one helper reached five ways.

class Gen000157DA
{
public:
	void handle( int a, int b );
	char m_lead[ 8 ];
	int m_field;
};

#define BFME_OWNER( SELF ) ( (Gen000157DA *)( (char *)( SELF ) - 0x20 ) )

#define BFME_OWNER_OFFSET_HOOK( NAME )                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void invoke();                                                    \
	};                                                                    \
	void NAME::invoke()                                                   \
	{                                                                     \
		BFME_OWNER( this )->handle(                                       \
			BFME_OWNER( this )->m_field, 1 );                             \
	}

BFME_OWNER_OFFSET_HOOK( Rva001EE8D0 )
BFME_OWNER_OFFSET_HOOK( Rva001FB550 )
BFME_OWNER_OFFSET_HOOK( Rva00204430 )
BFME_OWNER_OFFSET_HOOK( Rva002802D0 )
BFME_OWNER_OFFSET_HOOK( Rva00289830 )
