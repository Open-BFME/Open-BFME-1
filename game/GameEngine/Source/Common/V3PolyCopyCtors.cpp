// cl: /DNDEBUG /MD /EHsc
// Six copy constructors of polymorphic classes that hold nothing but scalars.
// Same shape as game/GameEngine/Source/GameClient/Gen_005e9a20.cpp, which
// landed one of them already; these are its neighbours in the same gen_asm
// file.  Retail:
//
//     mov eax,ecx ; mov ecx,[esp+4]
//     mov [eax],<VFTABLE>            ; the vptr, so the class is polymorphic
//     <copy N dwords / one byte from ecx+k to eax+k>
//     ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` and `mov eax,ecx` make it a one-argument
// constructor returning this; every load is from the argument at the same
// displacement the matching store uses on this, so it is a member-for-member
// COPY constructor of a class whose only base-like thing is its own vptr.  The
// width of each store gives the member: a dword is an int, the trailing `mov
// cl,[ecx+0xC] / mov [eax+0xC],cl` in 0x005EA240 is a one-byte member.
//
// THE TWO REP-MOVSD ROWS COPY A BLOCK, NOT A RUN OF MEMBERS, and the bytes say
// which.  Sixteen or thirty-two individual `int` members assigned one at a time
// do NOT fold into `rep movsd` under this compiler -- they emit the same
// load/store pair per member the other four rows do, and the bodies run 40 and
// 61 bytes instead of 32 and 44.  One POD sub-object assigned wholesale
// (`m_block = other.m_block`) emits exactly the retail `add esi,4 / lea edi,
// [eax+4] / mov ecx,N / rep movsd`, to the byte and to the register choice.  So
// each of these two classes holds ONE aggregate member at +4, of 0x40 and 0x80
// bytes; 0x005E95C0 then copies one more dword at +0x84, a member sitting past
// the end of that aggregate.
//
// SIX DIFFERENT VFTABLE ADDRESSES, so six classes.  Nothing here says anything
// about any virtual function -- the vtables are never read -- only that each
// class has at least one, which is why each is declared with a virtual
// destructor and no more.
//
// IDENTITY IS NOT RECOVERED.  Names come from the body address; field names
// carry their offset.  The vftable dword is a DIR32 site the gate takes from
// the target, so 17 of 0x005E9800's 21 bytes are concrete.

typedef int Int;

struct V3Block16 { Int m_v[16]; };
struct V3Block32 { Int m_v[32]; };

// -------------------------------------------------- vptr + one int (8 bytes)

#define V3_POLY_COPY_1( NAME )                                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
		virtual ~NAME();                                                  \
		Int m_field04;                                                    \
	};                                                                    \
	NAME::NAME( const NAME &other )                                       \
	{                                                                     \
		m_field04 = other.m_field04;                                      \
	}

V3_POLY_COPY_1( Rva005E9800 )
V3_POLY_COPY_1( Rva005E9C70 )

// ------------------------------------ vptr + two ints + a byte (0x10 bytes)

class Rva005EA240
{
public:
	Rva005EA240( const Rva005EA240 &other );
	virtual ~Rva005EA240();

	Int m_field04;
	Int m_field08;
	char m_field0C;
};

Rva005EA240::Rva005EA240( const Rva005EA240 &other )
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
}

// ------------------------------------------ vptr + thirteen ints (0x38 bytes)

class Rva005EA0D0
{
public:
	Rva005EA0D0( const Rva005EA0D0 &other );
	virtual ~Rva005EA0D0();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
};

Rva005EA0D0::Rva005EA0D0( const Rva005EA0D0 &other )
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
}

// ------------------------------------------- vptr + 0x10 dwords (0x44 bytes)

class Rva005E9390
{
public:
	Rva005E9390( const Rva005E9390 &other );
	virtual ~Rva005E9390();

	V3Block16 m_block;
};

Rva005E9390::Rva005E9390( const Rva005E9390 &other )
{
	m_block = other.m_block;
}

// ------------------- vptr + 0x20 dwords + one more dword at +0x84 (0x88 bytes)

class Rva005E95C0
{
public:
	Rva005E95C0( const Rva005E95C0 &other );
	virtual ~Rva005E95C0();

	V3Block32 m_block;
	Int m_field84;
};

Rva005E95C0::Rva005E95C0( const Rva005E95C0 &other )
{
	m_block = other.m_block;
	m_field84 = other.m_field84;
}
