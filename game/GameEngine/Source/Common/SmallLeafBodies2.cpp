// Eight more small leaf shapes, each too few to earn a file; companion to
// SmallLeafBodies.cpp, whose header applies here too.  Everything is read
// straight off the instruction stream and IDENTITY IS NOT RECOVERED: every name
// is derived from an address.

// mov eax,[ecx+<LEAD>] / add eax,<OFFSET> / ret -- a pointer member advanced
// by a constant.
#define BFME_PTR_MEMBER_OFFSET( NAME, LEAD, OFFSET )                          \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get() const;                                                    \
                                                                              \
		char  m_lead[ LEAD ];                                                 \
		char *m_base;                                                         \
	};                                                                        \
	char *NAME::get() const { return m_base + ( OFFSET ); }

BFME_PTR_MEMBER_OFFSET( Rva00160B80PtrOffset, 0x30, 0x24 )
BFME_PTR_MEMBER_OFFSET( Rva003CC6C0PtrOffset, 0x8, 0x38 )
BFME_PTR_MEMBER_OFFSET( Rva003CC700PtrOffset, 0x4, 0x8 )
BFME_PTR_MEMBER_OFFSET( Rva0058B580PtrOffset, 0x4, 0x70 )
BFME_PTR_MEMBER_OFFSET( Rva005A7400PtrOffset, 0x4, 0x70 )

class Rva00643100PtrOffset
{
public:
	char *get() const;

private:
	char *m_base;
};

char *Rva00643100PtrOffset::get() const
{
	return m_base + 0x10;
}

class Rva00160B90Field8
{
public:
	int get() const;

private:
	char m_unmodelled[ 0x8 ];
	int m_value;
};

int Rva00160B90Field8::get() const
{
	return m_value;
}

class Rva00160BA0Field4
{
public:
	char *get() const;

private:
	char m_unmodelled[ 0x4 ];
	char *m_value;
};

char *Rva00160BA0Field4::get() const
{
	return m_value;
}

class Rva0026C190Field4
{
public:
	char *get() const;

private:
	char m_unmodelled[ 0x4 ];
	char *m_value;
};

char *Rva0026C190Field4::get() const
{
	return m_value;
}

class Rva00719F70Field4
{
public:
	char *get() const;

private:
	char m_unmodelled[ 0x4 ];
	char *m_value;
};

char *Rva00719F70Field4::get() const
{
	return m_value;
}

// mov eax,[ecx+<LEAD>] / fld dword ptr [eax+<INNER>] / ret -- the chained
// getter of ChainedFieldGetters.cpp with a float at the far end; the `fld`
// opcode is what makes it a float and not a dword.
#define BFME_CHAIN_FLOAT_GETTER( NAME, LEAD, INNER )                          \
	class Inner##NAME                                                         \
	{                                                                         \
	public:                                                                   \
		char  m_lead[ INNER ];                                                \
		float m_value;                                                        \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		float get() const;                                                    \
                                                                              \
		char        m_lead[ LEAD ];                                           \
		Inner##NAME *m_holder;                                                \
	};                                                                        \
	float NAME::get() const { return m_holder->m_value; }

BFME_CHAIN_FLOAT_GETTER( Rva0016A930ChainedFloat, 0x4, 0x20 )
BFME_CHAIN_FLOAT_GETTER( Rva0016A940ChainedFloat, 0x4, 0x24 )
BFME_CHAIN_FLOAT_GETTER( Rva0016E4F0ChainedFloat, 0x4, 0x24 )
BFME_CHAIN_FLOAT_GETTER( Rva001B2080ChainedFloat, 0x2C, 0x8 )
BFME_CHAIN_FLOAT_GETTER( Rva001E0DB0ChainedFloat, 0x4, 0x2C )
BFME_CHAIN_FLOAT_GETTER( Rva002AC110ChainedFloat, 0x4, 0x30 )
BFME_CHAIN_FLOAT_GETTER( Rva002AC140ChainedFloat, 0x4, 0x20 )
BFME_CHAIN_FLOAT_GETTER( Rva002BA160ChainedFloat, 0x4, 0x8 )
BFME_CHAIN_FLOAT_GETTER( Rva0043A7E0ChainedFloat, 0x4, 0x28 )
BFME_CHAIN_FLOAT_GETTER( Rva007E4940ChainedFloat, 0x2C, 0x20 )

// mov al,[<address>] / ret -- one byte read from a .data global.
extern unsigned char g_Va012B7D84;
extern unsigned char g_Va012F13FC;
extern unsigned char g_Va012F499C;
extern unsigned char g_Va012F499D;
extern unsigned char g_Va0130E9F8;
extern unsigned char g_Va01336E7C;
extern unsigned char g_Va0133F428;
extern unsigned char g_Va0133F42B;
extern unsigned char g_Va0133F42C;
extern unsigned char g_Va0133F42F;
extern unsigned char g_Va0133F451;

unsigned char Rva0051A6C0GetFlag( void )
{
	return g_Va012F499D;
}

unsigned char Rva0051A6D0GetFlag( void )
{
	return g_Va012F499C;
}

unsigned char Rva00563970GetFlag( void )
{
	return g_Va012B7D84;
}

unsigned char Rva006C5230GetFlag( void )
{
	return g_Va0133F451;
}

unsigned char Rva006D1C10GetFlag( void )
{
	return g_Va0133F42C;
}

unsigned char Rva006E7010GetFlag( void )
{
	return g_Va0133F428;
}

unsigned char Rva0078ABA0GetFlag( void )
{
	return g_Va0133F42F;
}

unsigned char Rva0078AE10GetFlag( void )
{
	return g_Va0133F42B;
}

unsigned char Rva007D6BE0GetFlag( void )
{
	return g_Va012F13FC;
}

unsigned char Rva00882F40GetFlag( void )
{
	return g_Va0130E9F8;
}

unsigned char Rva0088CDF0GetFlag( void )
{
	return g_Va01336E7C;
}

// mov dword ptr [<address>],<immediate> / ret -- a fixed dword written to
// a global.  Two of the immediates are themselves addresses inside the image,
// so those are written as the address of another global rather than as a number.
extern unsigned int g_Va012B8B2C;
extern unsigned int g_Va012C3B34;
extern unsigned int g_Va012C3BBC;
extern unsigned int g_Va012C3C5C;
extern unsigned int g_Va012D71B0;
extern unsigned int g_Va012D71BC;
extern unsigned int g_Va012ED85C;
extern unsigned int g_Va012F4020;
extern unsigned int g_Va0111015C;
extern unsigned int g_Va0112B954;
extern unsigned int g_Va0112BEB0;
extern unsigned int g_Va0112C148;
extern unsigned int g_Va0113CBAC;
extern unsigned int g_Va0113CBAC;

void Rva00104750SetGlobal( void )
{
	g_Va012ED85C = 0x000007FFu;
}

void Rva004D8F40SetGlobal( void )
{
	g_Va012F4020 = 0x00000000u;
}

void Rva00C70430SetGlobal( void )
{
	g_Va012B8B2C = (unsigned int)&g_Va0111015C;
}

void Rva00C70C40SetGlobal( void )
{
	g_Va012C3B34 = (unsigned int)&g_Va0112B954;
}

void Rva00C70C50SetGlobal( void )
{
	g_Va012C3BBC = (unsigned int)&g_Va0112BEB0;
}

void Rva00C70C60SetGlobal( void )
{
	g_Va012C3C5C = (unsigned int)&g_Va0112C148;
}

void Rva00C71320SetGlobal( void )
{
	g_Va012D71B0 = (unsigned int)&g_Va0113CBAC;
}

void Rva00C71330SetGlobal( void )
{
	g_Va012D71BC = (unsigned int)&g_Va0113CBAC;
}

// mov eax,[esp+4] / mov edx,[ecx] / imul eax,eax,<STRIDE> / add eax,edx /
// ret 4 -- the stride index of SmallLeafBodies.cpp with a stride too large for
// the imm8 form.
#define BFME_WIDE_STRIDE_INDEX( NAME, STRIDE )                                \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *at( int index ) const;                                          \
                                                                              \
		char *m_base;                                                         \
	};                                                                        \
	char *NAME::at( int index ) const { return m_base + index * ( STRIDE ); }

BFME_WIDE_STRIDE_INDEX( Rva00360AA0WideStride, 0xB4 )
BFME_WIDE_STRIDE_INDEX( Rva00360AC0WideStride, 0xB4 )
BFME_WIDE_STRIDE_INDEX( Rva003A1350WideStride, 0xB8 )
BFME_WIDE_STRIDE_INDEX( Rva003A6590WideStride, 0xDC )
BFME_WIDE_STRIDE_INDEX( Rva003A65B0WideStride, 0xDC )
BFME_WIDE_STRIDE_INDEX( Rva0075D1C0WideStride, 0x128 )
BFME_WIDE_STRIDE_INDEX( Rva00760A30WideStride, 0x128 )

// mov eax,[esp+4] / inc dword ptr [eax] / ret -- a dword incremented
// through a pointer argument, caller cleanup.
void Rva0007C6C0Increment( int *slot )
{
	++*slot;
}

void Rva000B4A60Increment( int *slot )
{
	++*slot;
}

void Rva0010A6E0Increment( int *slot )
{
	++*slot;
}

void Rva0039B040Increment( int *slot )
{
	++*slot;
}

void Rva00422830Increment( int *slot )
{
	++*slot;
}

void Rva00697C80Increment( int *slot )
{
	++*slot;
}

void Rva00697C90Increment( int *slot )
{
	++*slot;
}

void Rva00697CA0Increment( int *slot )
{
	++*slot;
}

void Rva00697D40Increment( int *slot )
{
	++*slot;
}

// mov eax,ecx / ret -- the body proves only that it returns its receiver.
class Rva0006D1B0Self
{
public:
	Rva0006D1B0Self *self();
};

Rva0006D1B0Self *Rva0006D1B0Self::self()
{
	return this;
}

// mov eax,[esp+8] / ret 8 -- the SECOND of two dword arguments returned,
// callee cleanup and `this` never touched: __stdcall.
int __stdcall Rva0006D1C0Second( int first, int second )
{
	return second;
}

int __stdcall Rva00384330Second( int first, int second )
{
	return second;
}

int __stdcall Rva003C6570Second( int first, int second )
{
	return second;
}

int __stdcall Rva0054A780Second( int first, int second )
{
	return second;
}

int __stdcall Rva0054AB50Second( int first, int second )
{
	return second;
}

int __stdcall Rva0058A440Second( int first, int second )
{
	return second;
}

// mov eax,[esp+4] / mov edx,[esp+8] / mov [ecx+<D>],eax /
// mov [ecx+<D>+4],edx / ret 8 -- two dword arguments stored into adjacent
// members.
#define BFME_TWO_DWORD_SETTER( NAME, LEAD )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( int first, int second );                                    \
                                                                              \
		char m_lead[ LEAD ];                                                  \
		int  m_first;                                                         \
		int  m_second;                                                        \
	};                                                                        \
	void NAME::set( int first, int second )                                   \
	{                                                                         \
		m_first = first;                                                      \
		m_second = second;                                                    \
	}

BFME_TWO_DWORD_SETTER( Rva0018F030PairSlot, 0x80 )
BFME_TWO_DWORD_SETTER( Rva002997C0PairSlot, 0x58 )
BFME_TWO_DWORD_SETTER( Rva0035EE30PairSlot, 0x14 )
BFME_TWO_DWORD_SETTER( Rva00360EF0PairSlot, 0x3C )
BFME_TWO_DWORD_SETTER( Rva00412300PairSlot, 0x3C )
BFME_TWO_DWORD_SETTER( Rva0043ADA0PairSlot, 0x830 )
BFME_TWO_DWORD_SETTER( Rva004784D0PairSlot, 0x1AC )
BFME_TWO_DWORD_SETTER( Rva00493E70PairSlot, 0x30 )
BFME_TWO_DWORD_SETTER( Rva007F8820PairSlot, 0x28 )

// mov al,[ecx+<LEAD>] / and al,1 / ret -- single bit read out of a bitfield
#define BFME_BIT0_GETTER( NAME, LEAD )                                         	struct Bits##NAME                                                         	{                                                                         		unsigned char m_bit0 : 1;                                             		unsigned char m_rest : 7;                                             	};                                                                        	class NAME                                                                	{                                                                         	public:                                                                   		unsigned char test() const;                                                                                                                         		char         m_lead[ LEAD ];                                          		Bits##NAME   m_bits;                                                  	};                                                                        	unsigned char NAME::test() const { return m_bits.m_bit0; }

