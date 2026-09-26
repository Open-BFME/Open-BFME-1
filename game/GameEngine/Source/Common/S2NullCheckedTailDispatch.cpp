// Five bodies with one shape: test a pointer, tail-jump when it is non-null,
// and return zero when it is not.  Four dispatch through the pointee's vtable,
// the fifth through an import slot.
//
//     mov ecx,<pointer> / test ecx,ecx / je zero
//     mov eax,[ecx] / jmp dword ptr [eax+<SLOT>]
//     zero: xor eax,eax / ret
//
// WHAT THE BYTES SHOW.  Control leaves through `jmp`, so the callee's `ret`
// returns to OUR caller and its stack pop is ours: with a bare `ret` on this
// side, both sides are __thiscall taking no stack arguments.  The zero arm is
// `xor eax,eax`, the full-register form, so the return value is dword-wide.
// The pointer comes from +0 of `this` in one row, from +0x8C and +0x1BC in two
// others, and from the single __cdecl argument in the fourth.
//
// THE FIFTH ROW (0x000833E0) IS THE SAME SHAPE OVER A CRT IMPORT.  0x01359524
// is MSVCR71's `wcslen`, read out of the import directory.  MSVC 7.1 re-stores
// the argument over its own incoming slot (`mov [esp+4],eax`) before the jump
// because the callee is __cdecl and takes it from the same place.  `wchar_t` is
// not a distinct type under this compiler's defaults, so the parameter is
// spelled `unsigned short` -- that is also what the decorated name records.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the vtable slots ahead
// of the called one exist only to place it and say nothing about the real class.

typedef unsigned short GenWide;
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const GenWide * );

// @?Rva000833E0@@YAIPBG@Z 0x000833E0
unsigned int Rva000833E0( const GenWide *text )
{
	if( text )
		return wcslen( text );
	return 0;
}

class Gen00703EF0Slot0
{
public:
	virtual int slot00();
};

class Rva00703EF0
{
public:
	int dispatch() const;
	Gen00703EF0Slot0 *m_held;
};

// @?dispatch@Rva00703EF0@@QBEHXZ 0x00703EF0
int Rva00703EF0::dispatch() const
{
	Gen00703EF0Slot0 *held = m_held;
	if( held )
		return held->slot00();
	return 0;
}

class GenSlot08
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
};

// @?Rva00113BA0@@YAHPAVGenSlot08@@@Z 0x00113BA0
int Rva00113BA0( GenSlot08 *held )
{
	if( held )
		return held->slot08();
	return 0;
}

class GenSlot14
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
	virtual int slot0C();
	virtual int slot10();
	virtual int slot14();
};

#define BFME_NULL_CHECKED_TAIL( NAME, OFFSET )                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int dispatch() const;                                             \
		char m_lead[ OFFSET ];                                            \
		GenSlot14 *m_held;                                                \
	};                                                                    \
	int NAME::dispatch() const                                            \
	{                                                                     \
		GenSlot14 *held = m_held;                                         \
		if( held )                                                        \
			return held->slot14();                                        \
		return 0;                                                         \
	}

// @?dispatch@Rva005C3180@@QBEHXZ 0x005C3180
BFME_NULL_CHECKED_TAIL( Rva005C3180, 0x8C )
// @?dispatch@Rva005C34F0@@QBEHXZ 0x005C34F0
BFME_NULL_CHECKED_TAIL( Rva005C34F0, 0x1BC )
