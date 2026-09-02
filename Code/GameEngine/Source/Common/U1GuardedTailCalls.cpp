// Four __cdecl functions, 19 to 50 bytes, that test something about their
// LAST argument and, when the test passes, tail-jump into another function
// with the identical argument list.  Retail, the byte-flag arity:
//
//     mov eax,[esp+0x10] / cmp byte ptr [eax],0 / je out
//     mov [esp+0x10],eax / jmp <REL32>
//     out: ret
//
// WHAT THE BYTES SHOW.  A bare `ret` popping nothing, ecx dead on entry, and
// arguments read at [esp+4] through [esp+0x10]: __cdecl with four dword
// parameters and no return value.  The `jmp` is a TAIL CALL -- the frame is
// handed over untouched, so the callee has this function's exact signature and
// the callee's `ret` is what returns to the original caller.  The
// `mov [esp+0x10],eax` that precedes it writes the fourth argument back over
// itself; MSVC 7.1 emits that redundant store whenever it converts a call in
// tail position into a jump and the argument was loaded into a register for
// the test.  It is not a source assignment.
//
// THE FOUR ROWS DIFFER ONLY IN THE TEST, and each test names its own type:
//
//   0x005C8A80  cmp byte ptr [eax],0        -- a one-byte field at offset 0
//   0x005C9C80  cmp dword ptr [eax],0       -- a pointer at offset 0
//   0x005C7280  a pointer at 0, null-checked, then cmp word ptr [eax+4],0
//   0x005C9C40  two floats at 4 and 8, each compared against 0.0f
//
// 0x005C7280 IS THE TWO-LEVEL FORM: both failing tests fall through to the
// same `ret`, so the source is one `&&` guarding the call, and the pointer is
// bound to a local first (it is loaded into ecx and tested there, the tell
// this whole range keeps producing).  A SIXTEEN-BIT compare cannot come from a
// dword member.
//
// 0x005C9C40 IS THE FLOAT FORM and its branch polarity is the evidence for
// its operator.  After `fucompp / fnstsw ax / test ah,0x44`, an EQUAL compare
// leaves 0x40 in the tested byte -- one bit, odd parity, PF clear -- and an
// UNEQUAL compare leaves zero, which has even parity and sets PF.  So the
// first branch, `jp` into the call, fires when the field is NOT zero, and the
// second, `jnp` into the `ret`, fires when the second field IS zero.  That is
// `first != 0.0f || second != 0.0f`, not the `== 0.0f` reading the shape
// invites: spelling it with `==` inverts both branch bytes and misses.  The
// zero itself comes from an absolute address in .rdata holding four zero
// bytes, which is how MSVC 7.1 materialises a float comparand rather than
// `fldz`; that address is a DIR32 operand copied from retail and is not
// evidence.
//
// EACH ROW GETS ITS OWN CALLEE TYPE.  Four rows, four distinct jump targets,
// and a target is a function with one signature -- but nothing says two rows'
// fourth parameters are the same type, and the four tests read four different
// layouts, so each row is spelled against its own.
//
// IDENTITY IS NOT RECOVERED.  Every name here comes from a row or callee
// address.

class U1ByteFlagged
{
public:
	bool m_flag;
};

class U1DwordFlagged
{
public:
	void *m_pointer;
};

class U1Counted
{
public:
	char m_pad[ 4 ];
	unsigned short m_count;
};

class U1CountedHolder
{
public:
	U1Counted *m_item;
};

class U1Pair
{
public:
	char m_pad[ 4 ];
	float m_x;
	float m_y;
};

class INI
{
public:
	void u4Indent( int width );
	void u4Append( const void *value );
	void u4Finish( int radix );
};

extern const char g_u4Separator[];
extern const char g_u1False[];
extern const char g_u1True[];
extern const char g_u1Empty[];
void __cdecl u1FormatPointer( INI *ini, void *value );

void u1Do_005C7410( void *a, void *b, void *c, U1ByteFlagged *d );
void u1Do_005C90D0( void *a, void *b, void *c, U1DwordFlagged *d );
void u1Do_005C71F0( void *a, void *b, void *c, U1CountedHolder *d );
void u1Do_005C9030( void *a, void *b, void *c, U1Pair *d );

inline void u1BeginField( INI *ini, void *depthValue, void *store )
{
	unsigned int depth = (unsigned int)depthValue;
	if ( depth > 0 )
	{
		do
		{
			ini->u4Indent( 32 );
		}
		while ( --depth );
	}
	ini->u4Append( store );
	ini->u4Append( g_u4Separator );
}

void u1Do_005C90D0( void *a, void *b, void *c, U1DwordFlagged *d )
{
	INI *ini = (INI *)a;
	u1BeginField( ini, b, c );
	u1FormatPointer( ini, d->m_pointer );
	ini->u4Finish( 10 );
}

void u1Do_005C7410( void *a, void *b, void *c, U1ByteFlagged *d )
{
	INI *ini = (INI *)a;
	u1BeginField( ini, b, c );
	ini->u4Append( d->m_flag ? g_u1True : g_u1False );
	ini->u4Finish( 10 );
}

void u1Do_005C71F0( void *a, void *b, void *c, U1CountedHolder *d )
{
	INI *ini = (INI *)a;
	u1BeginField( ini, b, c );
	ini->u4Append( d->m_item ? (char *)d->m_item + 8 : g_u1Empty );
	ini->u4Finish( 10 );
}

void u1Guard_005C8A80( void *a, void *b, void *c, U1ByteFlagged *d )
{
	if ( d->m_flag )
	{
		u1Do_005C7410( a, b, c, d );
	}
}

void u1Guard_005C9C80( void *a, void *b, void *c, U1DwordFlagged *d )
{
	if ( d->m_pointer )
	{
		u1Do_005C90D0( a, b, c, d );
	}
}

void u1Guard_005C7280( void *a, void *b, void *c, U1CountedHolder *d )
{
	U1Counted *item = d->m_item;
	if ( item != 0 && item->m_count != 0 )
	{
		u1Do_005C71F0( a, b, c, d );
	}
}

void u1Guard_005C9C40( void *a, void *b, void *c, U1Pair *d )
{
	if ( d->m_x != 0.0f || d->m_y != 0.0f )
	{
		u1Do_005C9030( a, b, c, d );
	}
}
