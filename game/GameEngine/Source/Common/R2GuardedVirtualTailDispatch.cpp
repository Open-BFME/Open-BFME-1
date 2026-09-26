// Ten tiny __thiscall members that read a pointer out of the object, return
// zero when it is null, and otherwise TAIL-JUMP into one virtual slot of what
// it points at:
//
//     mov eax,[ecx+<OFF>] / test eax,eax / je zero
//     mov ecx,eax / mov eax,[ecx] / jmp dword ptr [eax+<SLOT>]
//     zero: xor eax,eax / ret        (or xor al,al for a one-byte result)
//
// WHAT THE BYTES SHOW.  Control leaves through `jmp`, so the callee's `ret` is
// this function's: both sides are __thiscall with no stack arguments and the
// callee's result IS this function's result.  `mov ecx,eax` moves the loaded
// pointer into the receiver register and `mov eax,[ecx]` loads a vftable from
// OFFSET 0, so the pointee is polymorphic with its vptr at the front and the
// dispatched member sits at the named byte offset in that vftable.  NOTHING IS
// RELOCATED in any of the ten bodies; every byte is concrete.
//
// THE ZERO ARM DECIDES THE RESULT WIDTH: `xor al,al` is a one-byte result and
// `xor eax,eax` a four-byte one, and the two encodings differ, so the gate
// separates them.  The one-byte form is written as bool; a one-byte integer
// would serve equally and the bytes do not choose.
//
// THE SLOT INDEX IS THE ONLY THING THE VFTABLE EVIDENCE GIVES.  It is spelled
// here by chaining single-inheritance bases that declare the preceding slots,
// which is the cheapest construct that puts a member at a chosen byte offset.
// THE NUMBER AND SHAPE OF THE PRECEDING SLOTS ARE NOT RECOVERED -- only that
// the dispatched one lands where retail dispatches.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.

class R2Slots00
{
public:
	virtual void slot00();
};

class R2Slots04 : public R2Slots00
{
public:
	virtual void slot04();
};

class R2Slots08 : public R2Slots04
{
public:
	virtual void slot08();
};

class R2Slots0C : public R2Slots08
{
public:
	virtual void slot0C();
};

class R2Slots10 : public R2Slots0C
{
public:
	virtual void slot10();
};

class R2Slots14 : public R2Slots10
{
public:
	virtual void slot14();
};

class R2Slots18 : public R2Slots14
{
public:
	virtual void slot18();
};

class R2Slots1C : public R2Slots18
{
public:
	virtual void slot1C();
};

class R2Slots20 : public R2Slots1C
{
public:
	virtual void slot20();
};

class R2Slots24 : public R2Slots20
{
public:
	virtual void slot24();
};

class R2Slots28 : public R2Slots24
{
public:
	virtual void slot28();
};

class R2Slots2C : public R2Slots28
{
public:
	virtual void slot2C();
};

class R2Slots30 : public R2Slots2C
{
public:
	virtual void slot30();
};

class R2Slots34 : public R2Slots30
{
public:
	virtual void slot34();
};

class R2Slots38 : public R2Slots34
{
public:
	virtual void slot38();
};

class R2Slots3C : public R2Slots38
{
public:
	virtual void slot3C();
};

class R2Slots40 : public R2Slots3C
{
public:
	virtual void slot40();
};

class R2Slots44 : public R2Slots40
{
public:
	virtual void slot44();
};

class R2Slots48 : public R2Slots44
{
public:
	virtual void slot48();
};

class R2Slots4C : public R2Slots48
{
public:
	virtual void slot4C();
};

class R2Slots50 : public R2Slots4C
{
public:
	virtual void slot50();
};

class R2Slots54 : public R2Slots50
{
public:
	virtual void slot54();
};

class R2Slots58 : public R2Slots54
{
public:
	virtual void slot58();
};

#define R2_GUARDED_VIRTUAL_TAIL( NAME, OFF, BASE, TYPE )                   \
	class NAME##Pointee : public BASE                                      \
	{                                                                      \
	public:                                                                \
		virtual TYPE dispatch();                                             \
	};                                                                     \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		char m_leading[ OFF ];                                               \
		NAME##Pointee *m_pointee;                                            \
		TYPE call();                                                         \
	};                                                                     \
	TYPE NAME::call()                                                      \
	{                                                                      \
		if ( m_pointee )                                                     \
		{                                                                    \
			return m_pointee->dispatch();                                      \
		}                                                                    \
		return 0;                                                            \
	}

R2_GUARDED_VIRTUAL_TAIL( Rva000C93E0, 0x220, R2Slots28, bool )
R2_GUARDED_VIRTUAL_TAIL( Rva000C9420, 0x220, R2Slots2C, int )
R2_GUARDED_VIRTUAL_TAIL( Rva0026E700, 0x1C, R2Slots34, bool )
R2_GUARDED_VIRTUAL_TAIL( Rva0027F310, 0x30, R2Slots20, int )
R2_GUARDED_VIRTUAL_TAIL( Rva0027F330, 0x30, R2Slots24, int )
R2_GUARDED_VIRTUAL_TAIL( Rva0043B4C0, 0x560, R2Slots38, int )
R2_GUARDED_VIRTUAL_TAIL( Rva00477B70, 0x1A0, R2Slots08, int )
R2_GUARDED_VIRTUAL_TAIL( Rva00478520, 0x1CC, R2Slots08, int )
R2_GUARDED_VIRTUAL_TAIL( Rva00497DF0, 0x8, R2Slots38, int )
R2_GUARDED_VIRTUAL_TAIL( Rva0090BB80, 0x14, R2Slots58, int )

// ?dup_00477B90@@YAXXZ
void dup_00477B90(void)
{
}
