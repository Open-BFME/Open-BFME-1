// Seven bodies that save `this`, make one no-argument call, and then write one
// constant into a member:
//
//     push esi / mov esi,ecx / call <REL32> / mov [esi+<OFF>],<K> /
//     [mov eax,esi] / pop esi / ret
//
// WHAT THE BYTES SHOW.  `this` is parked in a callee-saved register ACROSS the
// call and the store happens afterwards, so the store is sequenced after the
// call in the source -- a destructor would run its own body first and call the
// base afterwards, which is the opposite order, so these are not destructors.
//
// THE TRAILING `mov eax,esi` SPLITS THE FAMILY IN TWO, and it is the only thing
// that does:
//
//   * 003CDE40, 00588A00, 00588C30, 005A3160 and 00756CF0 end `pop esi / ret`
//     with eax undefined.  They are VOID.
//   * 002E2680 and 00765B00 define eax from `this` and never read it.  That is
//     a constructor's `this` return.
//
// Both halves are otherwise the same shape, and the store width and value are
// read straight off the encoding (C6 for a byte, C7 for a dword).
//
// WHAT THE BYTES CANNOT DECIDE: ecx still holds `this` when the call is made,
// but nothing is emitted to put it there, so a __thiscall member of this class,
// a base-class subobject call and a no-argument __cdecl free function all
// encode identically.  The callees are therefore spelled as no-argument void
// free functions named after their address -- the spelling that claims no
// owner.  Two of the seven targets (0x00036A9D and 0x00004381) already carry
// exactly that name in targets/game/reverse/symbols.csv from earlier work.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; the leading char
// arrays reproduce a proven offset and assert nothing else.

void b_00036a9d();
void b_0002d817();
void b_0003144e();
void b_00046a74();
void b_00004381();
void b_00025e1e();
void b_00014f2e();

// --- void: call, then store ------------------------------------------------

#define BFME_CALL_THEN_STORE_DWORD( NAME, CALLEE, OFFSET )                \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void reset();                                                     \
		char m_lead[ OFFSET ];                                            \
		int m_value;                                                      \
	};                                                                    \
	void NAME::reset()                                                    \
	{                                                                     \
		CALLEE();                                                         \
		m_value = 0;                                                      \
	}

#define BFME_CALL_THEN_STORE_BYTE( NAME, CALLEE, OFFSET, VALUE )          \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void reset();                                                     \
		char m_lead[ OFFSET ];                                            \
		bool m_value;                                                     \
	};                                                                    \
	void NAME::reset()                                                    \
	{                                                                     \
		CALLEE();                                                         \
		m_value = VALUE;                                                  \
	}

BFME_CALL_THEN_STORE_DWORD( Rva003CDE40, b_00036a9d, 0x30 )
BFME_CALL_THEN_STORE_DWORD( Rva005A3160, b_00046a74, 0xE18 )
BFME_CALL_THEN_STORE_BYTE( Rva00588C30, b_0003144e, 1, true )
BFME_CALL_THEN_STORE_BYTE( Rva00756CF0, b_00004381, 0x24, true )

// The one whose member sits at offset 0, so the store has no displacement byte
// (C6 06 00) and there is no padding to declare.
class Rva00588A00
{
public:
	void reset();
	bool m_value;
};

void Rva00588A00::reset()
{
	b_0002d817();
	m_value = false;
}

// --- constructors: call, store, return this --------------------------------

class Rva002E2680
{
public:
	Rva002E2680();
	char m_lead[ 4 ];
	bool m_value;
};

Rva002E2680::Rva002E2680()
{
	b_00025e1e();
	m_value = false;
}

class Rva00765B00
{
public:
	Rva00765B00();
	char m_lead[ 0x10 ];
	int m_value;
};

Rva00765B00::Rva00765B00()
{
	b_00014f2e();
	m_value = 0;
}
