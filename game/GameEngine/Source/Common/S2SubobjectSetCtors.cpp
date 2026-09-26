// Six __thiscall constructors that do nothing but hand three constants to one
// __thiscall member of a sub-object held at a fixed offset:
//
//     push esi / push 3F800000h / mov esi,ecx / push 0 / push 0
//     lea ecx,[esi+<OFFSET>] / call <REL32> / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  `mov eax,esi` at the end returns `this`, so these are
// constructors, not void members.  The receiver is reached with `lea`, not by
// replacing ecx with a loaded dword, so it is a SUB-OBJECT of the constructed
// class and not a stored pointer.  Three arguments go out right-to-left: two
// zeroes and 3F800000h, which is 1.0f pushed as an immediate -- the float is
// the LAST parameter.  Nothing else is written, so every other member of the
// enclosing object is left uninitialised by this constructor.
//
// ONE CALLEE, SIX OFFSETS.  All six sites call the same incremental-link thunk
// at 0x0002A1B2 (body 0x00094970), so one sub-object class covers the family;
// the offsets are 0x14, 0x18, 0x1C (twice) and 0x20 and 0x68.  Two members are
// byte-identical apart from their REL32 displacement; retail kept them at
// separate addresses, so they are separate translation units in the original,
// and they stay separate rows here.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The bytes
// do not say what the two zero arguments are (int, pointer or enum all encode
// as `push 0`), nor what the lead bytes ahead of the sub-object hold.

#define BFME_SUBOBJECT_SET_CTOR( NAME, OFFSET )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		char m_lead[ OFFSET ];                                            \
		Gen0002A1B2 m_sub;                                                \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_sub.set( 0, 0, 1.0f );                                          \
	}

class Gen0002A1B2
{
public:
	void set( int a, int b, float c );
};

// @??0Rva0073AB30@@QAE@XZ 0x0073AB30
BFME_SUBOBJECT_SET_CTOR( Rva0073AB30, 0x14 )
// @??0Rva0073AB70@@QAE@XZ 0x0073AB70
BFME_SUBOBJECT_SET_CTOR( Rva0073AB70, 0x18 )
// @??0Rva0073AB50@@QAE@XZ 0x0073AB50
BFME_SUBOBJECT_SET_CTOR( Rva0073AB50, 0x1C )
// @??0Rva0073ABB0@@QAE@XZ 0x0073ABB0
BFME_SUBOBJECT_SET_CTOR( Rva0073ABB0, 0x1C )
// @??0Rva0073AB90@@QAE@XZ 0x0073AB90
BFME_SUBOBJECT_SET_CTOR( Rva0073AB90, 0x20 )
// @??0Rva0073DBF0@@QAE@XZ 0x0073DBF0
BFME_SUBOBJECT_SET_CTOR( Rva0073DBF0, 0x68 )
