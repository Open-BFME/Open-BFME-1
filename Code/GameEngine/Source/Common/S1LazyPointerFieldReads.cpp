// Five sixteen-byte __thiscall readers that fall back to a call when a stored
// pointer is null, then read the SAME field either way:
//
//     mov eax,[ecx+4] / test eax,eax / jnz L / call <REL32> /
//   L:mov eax,[eax+8] / ret
//
// WHAT THE BYTES SHOW.  The branch is jnz over exactly the five bytes of the
// call, and the field load is on the JOIN, not duplicated on both arms.  That
// is `p = m_target; if (!p) p = <call>; return p->m_field;` -- one local
// carrying either value.  A conditional expression that returned the field from
// each arm separately would emit the load twice.  The callee's result is
// consumed straight out of eax as a pointer, so it returns the same type the
// member holds.
//
// ALL FIVE CALL 0x00001B18, and all five have identical offsets (pointer at 4,
// field at 8).  Four of them are neighbours in one 0x9000-byte stretch of
// .text.
//
// WHAT THE BYTES CANNOT DECIDE: ecx still holds `this` at the call site, but
// nothing is done to put it there and no argument is pushed, so a __thiscall
// member of this class and a no-argument __cdecl free function encode
// identically.  It is spelled as a free function because that asserts less --
// it claims no owning class for the callee.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.

class Gen00001B18
{
public:
	char m_lead[ 8 ];
	int m_field;
};

Gen00001B18 *Make00001B18();

#define BFME_LAZY_FIELD_READ( NAME )                                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int get();                                                        \
		char m_lead[ 4 ];                                                 \
		Gen00001B18 *m_target;                                            \
	};                                                                    \
	int NAME::get()                                                       \
	{                                                                     \
		Gen00001B18 *target = m_target;                                   \
		if ( !target )                                                    \
		{                                                                 \
			target = Make00001B18();                                      \
		}                                                                 \
		return target->m_field;                                           \
	}

BFME_LAZY_FIELD_READ( Rva005F0CA0 )
BFME_LAZY_FIELD_READ( Rva005F30D0 )
BFME_LAZY_FIELD_READ( Rva005F42E0 )
BFME_LAZY_FIELD_READ( Rva005F5490 )
BFME_LAZY_FIELD_READ( Rva005F7F30 )

// The 0x0020E1F0 body is the direct-return form of the same lazy-pointer
// pattern above: return the stored pointer when present, otherwise tail-call
// the shared fallback at 0x00001B18.  Identity remains address-derived.
class Rva0020E1F0
{
public:
	Gen00001B18 *get();
	Gen00001B18 *m_target;
};

Gen00001B18 *Rva0020E1F0::get()
{
	Gen00001B18 *target = m_target;
	if ( !target )
	{
		return Make00001B18();
	}
	return target;
}
