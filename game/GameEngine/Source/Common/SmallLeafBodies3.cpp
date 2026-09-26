// Four more small leaf shapes, companion to SmallLeafBodies.cpp and
// SmallLeafBodies2.cpp; those headers apply here too.  IDENTITY IS NOT
// RECOVERED: every name is derived from an address.

// mov eax,[esp+4] / mov edx,[eax] / add ecx,<LEAD> / mov [ecx],edx / ... /
// ret 4 -- three dwords copied out of a reference into a member aggregate.  The
// `add ecx` rather than a displacement off `this` is the aggregate's own
// assignment operator inlined, with ecx made to point at the member.
#define BFME_BLOCK_ASSIGN( NAME, LEAD, DWORDS )                               \
	struct Block##NAME                                                        \
	{                                                                         \
		unsigned int m_dword[ DWORDS ];                                       \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Block##NAME &value );                                 \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		Block##NAME  m_block;                                                 \
	};                                                                        \
	void NAME::set( const Block##NAME &value ) { m_block = value; }

// mov eax,[esp+4] / mov edx,[eax] / mov [ecx+<D>],edx / mov eax,[eax+4] /
// mov [ecx+<D>+4],eax / ret 4 -- two dwords, copied field by field off `this`
// with no address made, which is the same copy done as two member assignments
// rather than through an aggregate.
#define BFME_TWO_DWORD_ASSIGN( NAME, LEAD )                                   \
	struct Pair##NAME                                                         \
	{                                                                         \
		unsigned int m_first;                                                 \
		unsigned int m_second;                                                \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Pair##NAME &value );                                  \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		unsigned int m_first;                                                 \
		unsigned int m_second;                                                \
	};                                                                        \
	void NAME::set( const Pair##NAME &value )                                 \
	{                                                                         \
		m_first = value.m_first;                                              \
		m_second = value.m_second;                                            \
	}

// mov eax,[ecx-<BACK>] / add eax,<OFFSET> / ret -- a pointer read at a NEGATIVE
// displacement and advanced by a constant, as in SmallLeafBodies.cpp.
#define BFME_BACK_POINTER_OFFSET( NAME, BACK, OFFSET )                        \
	class Sub##NAME                                                           \
	{                                                                         \
	public:                                                                   \
		char *m_base;                                                         \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get() const;                                                    \
	};                                                                        \
	char *NAME::get() const                                                   \
	{                                                                         \
		return ( (const Sub##NAME *)( (const char *)this - ( BACK ) ) )->m_base \
			+ ( OFFSET );                                                     \
	}

BFME_BLOCK_ASSIGN( Rva0016A2C0BlockAssign, 0x24, 3 )
BFME_BLOCK_ASSIGN( Rva0016A370BlockAssign, 0x50, 3 )
BFME_BLOCK_ASSIGN( Rva0016A3E0BlockAssign, 0x44, 3 )
BFME_BLOCK_ASSIGN( Rva0016A400BlockAssign, 0x44, 3 )
BFME_BLOCK_ASSIGN( Rva001BD280BlockAssign, 0x10, 6 )
BFME_BLOCK_ASSIGN( Rva001BD2C0BlockAssign, 0x28, 3 )
BFME_BLOCK_ASSIGN( Rva0020A760BlockAssign, 0x24C, 3 )
BFME_BLOCK_ASSIGN( Rva00265BD0BlockAssign, 0x3C, 3 )
BFME_BLOCK_ASSIGN( Rva00299790BlockAssign, 0x8, 3 )
BFME_BLOCK_ASSIGN( Rva00299990BlockAssign, 0x8, 3 )
BFME_BLOCK_ASSIGN( Rva002BB950BlockAssign, 0x498, 3 )
BFME_BLOCK_ASSIGN( Rva003A1030BlockAssign, 0xA4, 3 )
BFME_BLOCK_ASSIGN( Rva003D5C60BlockAssign, 0x848, 3 )
BFME_BLOCK_ASSIGN( Rva004094A0BlockAssign, 0x48, 3 )
BFME_BLOCK_ASSIGN( Rva006C55E0BlockAssign, 0x1440, 4 )
BFME_BLOCK_ASSIGN( Rva0077E010BlockAssign, 0x134, 3 )

BFME_TWO_DWORD_ASSIGN( Rva0015A200PairAssign, 0x320 )
BFME_TWO_DWORD_ASSIGN( Rva003C5E10PairAssign, 0x10 )
BFME_TWO_DWORD_ASSIGN( Rva003C5F40PairAssign, 0xE0 )
BFME_TWO_DWORD_ASSIGN( Rva003D5070PairAssign, 0xA4 )
BFME_TWO_DWORD_ASSIGN( Rva003D5090PairAssign, 0x9C )
BFME_TWO_DWORD_ASSIGN( Rva0043A630PairAssign, 0x2C )
BFME_TWO_DWORD_ASSIGN( Rva0048E330PairAssign, 0x10 )
BFME_TWO_DWORD_ASSIGN( Rva004F0700PairAssign, 0x30 )
BFME_TWO_DWORD_ASSIGN( Rva00661BA0PairAssign, 0x1E4 )
BFME_TWO_DWORD_ASSIGN( Rva00746050PairAssign, 0x78 )
BFME_TWO_DWORD_ASSIGN( Rva0075AF60PairAssign, 0xE8 )

BFME_BACK_POINTER_OFFSET( Rva00219AC0BackOffset, 0x18, 0x38 )
BFME_BACK_POINTER_OFFSET( Rva00219AD0BackOffset, 0x18, 0x38 )
BFME_BACK_POINTER_OFFSET( Rva00219AE0BackOffset, 0x18, 0x38 )
BFME_BACK_POINTER_OFFSET( Rva002341B0BackOffset, 0xE0, 0x23C )
BFME_BACK_POINTER_OFFSET( Rva00268780BackOffset, 0xC, 0x10 )
BFME_BACK_POINTER_OFFSET( Rva0026A940BackOffset, 0x20, 0xC )
BFME_BACK_POINTER_OFFSET( Rva0026A950BackOffset, 0x20, 0x7C )
BFME_BACK_POINTER_OFFSET( Rva00287330BackOffset, 0x1C, 0x10 )

// mov eax,[esp+4] / ret 8 -- the FIRST of two dword arguments returned,
// callee cleanup and `this` never touched: __stdcall.
int __stdcall Rva0006D980First( int first, int second )
{
	return first;
}

int __stdcall Rva00097960First( int first, int second )
{
	return first;
}

int __stdcall Rva00384710First( int first, int second )
{
	return first;
}

int __stdcall Rva003C6940First( int first, int second )
{
	return first;
}

int __stdcall Rva0054B310First( int first, int second )
{
	return first;
}

int __stdcall Rva0058A830First( int first, int second )
{
	return first;
}

