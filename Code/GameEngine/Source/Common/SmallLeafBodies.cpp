// Eleven small leaf shapes that share nothing but their size, collected here
// because each has too few members to earn a file.  Every one is read straight
// off its instruction stream; where a displacement is negative it is spelled as
// an explicit backward cast, and no inheritance relationship is claimed by any
// of them.  IDENTITY IS NOT RECOVERED: every name is derived from an address.

// mov al,[esp+4] / mov [ecx+<DISP>],al / ret 4 -- the disp8 half of
// DispByteFieldSetters.cpp.
#define BFME_SMALL_BYTE_SETTER( NAME, DISP )                                  \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( unsigned char value );                                      \
		char          m_lead[ DISP ];                                         \
		unsigned char m_value;                                                \
	};                                                                        \
	void NAME::set( unsigned char value ) { m_value = value; }

BFME_SMALL_BYTE_SETTER( Rva00112950ByteSlot8, 0x6A )
BFME_SMALL_BYTE_SETTER( Rva00160AA0ByteSlot8, 0x50 )
BFME_SMALL_BYTE_SETTER( Rva00160AC0ByteSlot8, 0x7C )
BFME_SMALL_BYTE_SETTER( Rva001FE030ByteSlot8, 0x32 )
BFME_SMALL_BYTE_SETTER( Rva002ED470ByteSlot8, 0x43 )
BFME_SMALL_BYTE_SETTER( Rva002ED6A0ByteSlot8, 0x1D )
BFME_SMALL_BYTE_SETTER( Rva003826E0ByteSlot8, 0x69 )
BFME_SMALL_BYTE_SETTER( Rva003A3CD0ByteSlot8, 0x1F )
BFME_SMALL_BYTE_SETTER( Rva003BC500ByteSlot8, 0x1D )
BFME_SMALL_BYTE_SETTER( Rva004581B0ByteSlot8, 0x64 )
BFME_SMALL_BYTE_SETTER( Rva0050D8C0ByteSlot8, 0x59 )
BFME_SMALL_BYTE_SETTER( Rva00516680ByteSlot8, 0x59 )
BFME_SMALL_BYTE_SETTER( Rva006E1970ByteSlot8, 0x69 )
BFME_SMALL_BYTE_SETTER( Rva006E1980ByteSlot8, 0x6A )

// mov byte ptr [<address>],<imm8> / ret -- a fixed byte written to a .data
// global with no arguments at all.  Two members write the same global.
extern unsigned char g_Va012D6DFC;
extern unsigned char g_Va012EF1DC;
extern unsigned char g_Va012F13FC;
extern unsigned char g_Va012F1B23;
extern unsigned char g_Va012F4125;
extern unsigned char g_Va012F4126;
extern unsigned char g_Va012F4970;
extern unsigned char g_Va012F70B0;
extern unsigned char g_Va0130E9F8;
extern unsigned char g_Va0134CB4C;
extern unsigned char g_Va0134CB4D;

void Rva00061BE0SetFlag( void )
{
	g_Va0134CB4C = 0x01;
}

void Rva00382870SetFlag( void )
{
	g_Va012EF1DC = 0x01;
}

void Rva00382880SetFlag( void )
{
	g_Va012EF1DC = 0x00;
}

void Rva0046EF50SetFlag( void )
{
	g_Va012F1B23 = 0x01;
}

void Rva004E0660SetFlag( void )
{
	g_Va012F4126 = 0x01;
}

void Rva004E0670SetFlag( void )
{
	g_Va012F4125 = 0x01;
}

void Rva00510DB0SetFlag( void )
{
	g_Va012F4970 = 0x01;
}

void Rva00627C40SetFlag( void )
{
	g_Va012F70B0 = 0x01;
}

void Rva006C5410SetFlag( void )
{
	g_Va012D6DFC = 0x01;
}

void Rva007D6BD0SetFlag( void )
{
	g_Va012F13FC = 0x00;
}

void Rva00882F20SetFlag( void )
{
	g_Va0130E9F8 = 0x01;
}

void Rva00882F30SetFlag( void )
{
	g_Va0130E9F8 = 0x00;
}

void Rva009C8730SetFlag( void )
{
	g_Va0134CB4D = 0x01;
}

// mov eax,[esp+4] / mov edx,[ecx] / imul eax,eax,<STRIDE> / add eax,edx /
// ret 4 -- indexing a block of <STRIDE>-byte elements off a pointer at +0x00.
#define BFME_SMALL_STRIDE_INDEX( NAME, STRIDE )                               \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *at( int index ) const;                                          \
		char *m_base;                                                         \
	};                                                                        \
	char *NAME::at( int index ) const { return m_base + index * ( STRIDE ); }

BFME_SMALL_STRIDE_INDEX( Rva001C2740StrideIndex, 0x5C )
BFME_SMALL_STRIDE_INDEX( Rva00234330StrideIndex, 0x1C )
BFME_SMALL_STRIDE_INDEX( Rva00360B40StrideIndex, 0x58 )
BFME_SMALL_STRIDE_INDEX( Rva003615B0StrideIndex, 0x58 )
BFME_SMALL_STRIDE_INDEX( Rva00422CC0StrideIndex, 0x1C )
BFME_SMALL_STRIDE_INDEX( Rva0049B2F0StrideIndex, 0x70 )
BFME_SMALL_STRIDE_INDEX( Rva00581A10StrideIndex, 0x1C )
BFME_SMALL_STRIDE_INDEX( Rva0075CFE0StrideIndex, 0x38 )

// mov eax,[ecx-<BACK>] / add eax,<OFFSET> / ret -- a pointer read at a
// NEGATIVE displacement and advanced by a constant.  The object at
// (this - BACK) is only witnessed as a pointer sitting at offset 0.
struct LeadingPointerBlock
{
	char *m_base;
};

#define BFME_SMALL_BACK_POINTER_OFFSET( NAME, BACK, OFFSET )                  \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get() const;                                                    \
	};                                                                        \
	char *NAME::get() const                                                   \
	{                                                                         \
		return ( (const LeadingPointerBlock *)( (const char *)this - ( BACK ) ) )->m_base \
			+ ( OFFSET );                                                     \
	}

BFME_SMALL_BACK_POINTER_OFFSET( Rva001F7200BackOffset, 0x4C, 0x1A8 )
BFME_SMALL_BACK_POINTER_OFFSET( Rva00268790BackOffset, 0xC, 0x80 )
BFME_SMALL_BACK_POINTER_OFFSET( Rva002687A0BackOffset, 0xC, 0xF0 )
BFME_SMALL_BACK_POINTER_OFFSET( Rva002687B0BackOffset, 0xC, 0x160 )
BFME_SMALL_BACK_POINTER_OFFSET( Rva0026A960BackOffset, 0x20, 0xEC )
BFME_SMALL_BACK_POINTER_OFFSET( Rva0026A970BackOffset, 0x20, 0x15C )
BFME_SMALL_BACK_POINTER_OFFSET( Rva00287340BackOffset, 0x1C, 0x80 )

// movsx eax,byte ptr [ecx+<DISP>] / ret -- a SIGNED byte widened to int,
// which is what separates this from the plain byte getters.
#define BFME_SMALL_SIGNED_BYTE_GETTER( NAME, DISP )                           \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		int get() const;                                                      \
		char        m_lead[ DISP ];                                           \
		signed char m_value;                                                  \
	};                                                                        \
	int NAME::get() const { return m_value; }

BFME_SMALL_SIGNED_BYTE_GETTER( Rva001BD9E0SignedByte, 0x490 )
BFME_SMALL_SIGNED_BYTE_GETTER( Rva001BD9F0SignedByte, 0x491 )
BFME_SMALL_SIGNED_BYTE_GETTER( Rva00215B70SignedByte, 0x495 )
BFME_SMALL_SIGNED_BYTE_GETTER( Rva003829E0SignedByte, 0x494 )

// mov eax,[esp+4] / mov eax,[ecx+eax*4+<DISP>] / ret 4 -- a dword array
// member indexed by the argument.
#define BFME_SMALL_MEMBER_ARRAY( NAME, DISP )                                 \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		int get( int index ) const;                                           \
		char m_lead[ DISP ];                                                  \
		int  m_array[ 1 ];                                                    \
	};                                                                        \
	int NAME::get( int index ) const { return m_array[ index ]; }

BFME_SMALL_MEMBER_ARRAY( Rva001E0CC0MemberArray, 0x94 )
BFME_SMALL_MEMBER_ARRAY( Rva00588680MemberArray, 0x100 )
BFME_SMALL_MEMBER_ARRAY( Rva00598ED0MemberArray, 0x9C )
BFME_SMALL_MEMBER_ARRAY( Rva00696340MemberArray, 0xAC4 )

// mov eax,[ecx-<BACK>] / mov al,[eax+<INNER>] / ret -- the chained byte
// getter of ChainedFieldGetters.cpp with both displacements widened to disp32.
// ByteAtDisp / PtrToByteAtDisp name the witnessed layout, not an identity.
template <int kDisp>
struct ByteAtDisp
{
	char          m_lead[ kDisp ];
	unsigned char m_value;
};

template <int kDisp>
struct PtrToByteAtDisp
{
	ByteAtDisp<kDisp> *m_holder;
};

#define BFME_SMALL_BACK_CHAIN_BYTE( NAME, BACK, INNER )                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		unsigned char get() const;                                            \
	};                                                                        \
	unsigned char NAME::get() const                                           \
	{                                                                         \
		return ( (const PtrToByteAtDisp<INNER> *)( (const char *)this - ( BACK ) ) ) \
			->m_holder->m_value;                                              \
	}

BFME_SMALL_BACK_CHAIN_BYTE( Rva00212E90BackChain, 0xDC, 0xB4 )
BFME_SMALL_BACK_CHAIN_BYTE( Rva00230880BackChain, 0xE0, 0x270 )
BFME_SMALL_BACK_CHAIN_BYTE( Rva002308D0BackChain, 0xE0, 0x2F0 )
BFME_SMALL_BACK_CHAIN_BYTE( Rva002C8520BackChain, 0x340, 0x80 )

// mov al,[esp+4] / mov [<address>],al / ret -- one byte argument stored to a
// .data global, caller cleanup.
extern unsigned char g_Va012D6D84;
extern unsigned char g_Va012D6DA8;
extern unsigned char g_Va012ED611;
extern unsigned char g_Va0133F42B;
extern unsigned char g_Va0133F42D;

void Rva00060840StoreFlag( unsigned char value )
{
	g_Va012D6DA8 = value;
}

void Rva000EB270StoreFlag( unsigned char value )
{
	g_Va012ED611 = value;
}

void Rva006E7020StoreFlag( unsigned char value )
{
	g_Va012D6D84 = value;
}

void Rva006E7030StoreFlag( unsigned char value )
{
	g_Va0133F42B = value;
}

void Rva006E7050StoreFlag( unsigned char value )
{
	g_Va0133F42D = value;
}

// mov eax,[esp+4] / mov eax,[<address>+eax*4] / ret -- a global dword array
// indexed by the argument.
extern int g_Va011098B0[];
extern int g_Va012B49FC[];
extern int g_Va012BBD98[];
extern int g_Va012F9C40[];
extern int g_Va01340100[];

int Rva003D4F80Lookup( int index )
{
	return g_Va012B49FC[ index ];
}

int Rva00564070Lookup( int index )
{
	return g_Va011098B0[ index ];
}

int Rva00716970Lookup( int index )
{
	return g_Va012F9C40[ index ];
}

int Rva007A6280Lookup( int index )
{
	return g_Va01340100[ index ];
}

int Rva007AD820Lookup( int index )
{
	return g_Va012BBD98[ index ];
}

// mov eax,ecx / mov [eax],<immediate> / ret 4 -- a constructor (eax is set to
// `this` and nothing else uses it) that consumes one argument without storing
// it and writes one dword at +0x00.  Four write a .rdata address, which is a
// vftable; one writes -1, which is a data member.
#define BFME_SMALL_VPTR_CTOR( NAME )                                          \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( void *ignored );                                                \
		virtual void anchor();                                                \
	};                                                                        \
	NAME::NAME( void * ) {}

#define BFME_SMALL_MINUS_ONE_CTOR( NAME )                                     \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( void *ignored );                                                \
		int m_value;                                                          \
	};                                                                        \
	NAME::NAME( void * ) : m_value( -1 ) {}

BFME_SMALL_MINUS_ONE_CTOR( Rva0039CED0SingleStore )
BFME_SMALL_VPTR_CTOR( Rva00499E60SingleStore )
BFME_SMALL_VPTR_CTOR( Rva00499F00SingleStore )
BFME_SMALL_VPTR_CTOR( Rva004B2250SingleStore )
BFME_SMALL_VPTR_CTOR( Rva004C1310SingleStore )

// mov eax,[esp+4] / mov [eax],<immediate> / ret 4 -- a small integer stored
// through a pointer argument which is also left in eax as the result; callee
// cleanup with `this` never touched, so __stdcall.
int * __stdcall Rva00287400Seed( int *slot )
{
	*slot = 0x18;
	return slot;
}

int * __stdcall Rva0028D880Seed( int *slot )
{
	*slot = 0x18;
	return slot;
}

int * __stdcall Rva0029AA20Seed( int *slot )
{
	*slot = 0x10;
	return slot;
}

int * __stdcall Rva002D3630Seed( int *slot )
{
	*slot = 0x7DB;
	return slot;
}

