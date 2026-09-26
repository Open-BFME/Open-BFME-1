// Two bodies that branch on a byte-wide flag.  Both are as concrete as small
// bodies get -- 005701A0 has no relocation site at all, and 00589620 has only
// its REL32.
//
// 005701A0 -- an IF/ELSE, not a guard:
//
//     mov al,[ecx+0x260] / test al,al / jz L / mov byte [ecx+0x261],1 / ret
//   L:mov byte [ecx+0x260],1 / ret
//
// The jz lands on a SECOND store-and-return rather than on the function's exit,
// so both arms do work: when the first flag is set the SECOND flag is raised,
// and when it is clear the FIRST flag is raised instead.  A plain
// `if (a) b = true;` would have nothing after the jz but `ret`.  The loads and
// stores are all one byte wide, so both members are byte-sized; an int-width
// flag would have used a dword load and `test eax,eax`.
//
// 00589620 -- a guard on a BIT, not on the whole byte:
//
//     mov ecx,[ecx+0x10] / test byte ptr [ecx+0x20],1 / jz L /
//     push 0x1F4 / call <REL32> / ret   (L: ret)
//
// The pointer is loaded straight into ecx, so the callee is a __thiscall member
// of the pointee; the guard then tests bit 0 of a byte inside THAT object, not
// inside `this`.  `test <mem>,1` is what `flags & 1` compiles to -- a whole-byte
// test would be `cmp`/`test al,al` after a load.  One dword-sized constant
// (0x1F4 = 500) is pushed and the stack is not adjusted afterwards, so the
// callee cleans up: a __thiscall member taking one int.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, the leading char
// arrays reproduce proven offsets, and the bytes cannot say whether the flag
// byte is a bool, a byte-wide enum or one bit of a bitfield.

class Rva005701A0
{
public:
	void raise();
	char m_lead[ 0x260 ];
	bool m_first;
	bool m_second;
};

void Rva005701A0::raise()
{
	if ( m_first )
	{
		m_second = true;
	}
	else
	{
		m_first = true;
	}
}

class Gen00020B5D
{
public:
	void handle( int value );
	char m_lead[ 0x20 ];
	unsigned char m_flags;
};

class Rva00589620
{
public:
	void notifyTarget();
	char m_lead[ 0x10 ];
	Gen00020B5D *m_target;
};

void Rva00589620::notifyTarget()
{
	if ( m_target->m_flags & 1 )
	{
		m_target->handle( 500 );
	}
}
