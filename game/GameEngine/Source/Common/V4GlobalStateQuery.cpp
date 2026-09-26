// One 54-byte __thiscall member that picks one of two dwords held in two
// different globals, on a three-term condition:
//
//     mov al,[ecx+0x2C] / test al,al / je .ask
//     mov al,[ecx+0x2D] / test al,al / jne .other
//   .ask:
//     mov ecx,ds:[0x012F0898] / call <test> / test al,al / jne .other
//     mov eax,ds:[0x012F0898] / mov eax,[eax+0x110] / ret
//   .other:
//     mov ecx,ds:[0x012ED5C8] / mov eax,[ecx+0xEB0] / ret
//
// WHAT THE BYTES SHOW.  The two byte members are ANDed -- failing the first
// falls into the same block the second's failure falls into -- and that block
// then ORs a call in.  The `.other` arm is OUT OF LINE and reached only by
// forward jumps, with the OTHER return sitting on the fall-through path.  Every
// structured spelling of `if( a || b ) { other } return fallback` puts the
// fallback block last; only jumping INTO the taken arm gives this order, so the
// source is written with the label, and this row is the reason to say so.
//
// TWO GLOBALS, NOT ONE.  0x012F0898 is the same global V4TwoCallForwarders.cpp
// tail-jumps a niladic member of, so it keeps the SAME type here; that type
// gains the predicate called at 0x00382B50 and the dword at +0x110 this row
// reads.  0x012ED5C8 is a second, unrelated global read at +0xEB0.  The
// predicate's `test al,al` after the call fixes its return at one byte.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pin is address-derived and additive.

// Same type as in V4TwoCallForwarders.cpp; that file declares only the niladic
// member it needs, this one adds the two the row below reaches.
class Rva00383860
{
public:
	void invoke();
	bool test();
	char m_pad00[ 0x110 ];
	int  m_at110;
};

// Same type as in V4MirroredFlagUpdate.cpp, which reads the byte at +0x8E.
class Glo012ED5C8Type
{
public:
	char m_pad00[ 0x8E ];
	bool m_at8E;
	char m_pad8F[ 0xE21 ];
	int  m_atEB0;
};

extern Rva00383860 *      Glo012F0898;
extern Glo012ED5C8Type *  Glo012ED5C8;

class Rva003BCC10
{
public:
	int  current();
	char m_pad00[ 0x2C ];
	bool m_at2C;
	bool m_at2D;
};
int Rva003BCC10::current()
{
	if( m_at2C && m_at2D )
		goto other;
	if( !Glo012F0898->test() )
		return Glo012F0898->m_at110;
other:
	return Glo012ED5C8->m_atEB0;
}
