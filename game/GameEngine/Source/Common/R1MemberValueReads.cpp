// Thirty-six more tiny bodies, five shapes, grouped here because each one is a
// single read (or a single pair of writes) with no control flow worth the name.
//
// (1) 0x001F6F90 & co -- guarded interior pointer
//
//     test ecx,ecx / jz .null / lea eax,[ecx+K] / ret / .null: xor eax,eax / ret
//
//     The test is on the INCOMING pointer and comes BEFORE the `lea`, so it is
//     not the `this - K` guard that a trailing test would be, and MSVC 7.1 never
//     emits a null test for `this` on its own.  Someone wrote the test.  The
//     null arm re-materialises zero with `xor eax,eax` rather than falling
//     through, which is what the compiler does when the tested register is not
//     the return register.
//
// (2) 0x0016A950 & co -- float out of a pointed-at object
//
//     mov eax,<slot> / fld dword ptr [eax+K] / ret
//
//     `fld dword` (not `qword`) proves a 4-byte float.  Two members read the
//     holding pointer out of the object at +4.  The other six read it at a
//     NEGATIVE displacement, -0x33C or -0x340: the incoming pointer is not the
//     start of the object that holds the pointer, so those six are a genuinely
//     different shape that mnemonic grouping could not distinguish.  What sits
//     between is not recovered; the source below only says what the load says.
//
// (3) 0x00537720 & co -- sum of two adjacent members
//
//     mov eax,[p+4] / add eax,[p] / ret
//
//     THE ORDER IS SOURCE ORDER: the member at +4 is the left operand.  Two
//     members take p off the stack (free functions of one pointer); three read
//     it out of the object first.
//
//     0x0073A320 and 0x0073A330 were swept into the same mnemonic group by
//     mov/mov/add/ret and are NOT this shape at all -- they store a byte
//     constant and then add an immediate.  They are landed here as their own
//     shape and named separately.
//
// (4) 0x000B8E50 & co -- clear two fields
//
//     xor eax,eax / mov <slot>,eax / mov <slot>,eax / ret
//
//     Store order is source order.  A `mov byte` store is a one-byte field; the
//     `xor al,al` variant proves BOTH fields are one byte.  One member writes
//     two globals instead of two members and touches no `this`.
//
// (5) 0x000A0080 & co -- guarded virtual tail call
//
//     mov eax,<slot> / test eax,eax / jz .out / mov ecx,eax / mov eax,[ecx] /
//     jmp dword ptr [eax+S] / .out: ret
//
//     eax is loaded first and only then copied to ecx, because the vptr load
//     needs a register of its own -- that is why this reads differently from the
//     non-virtual guarded tail calls.  The `jz` lands on the trailing `ret`, so
//     the body is one `if` and the function returns nothing; a version that
//     returned a pointer puts a `xor eax,eax` on the null arm and retail has
//     none.  S/4 is the vtable slot index; the pad virtuals below exist only to
//     place the callee at that index and assert nothing about what they are.
//
// IDENTITY IS NOT RECOVERED anywhere in this file.  Every name is derived from
// the address of the row or the address it reads.

// ------------------------------------------------------------------ shape (1)

#define BFME_GUARDED_INTERIOR( NAME, OFFSET )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void *get();                                                      \
		char m_lead[ OFFSET ];                                            \
		int m_field;                                                      \
	};                                                                    \
	void *NAME::get()                                                     \
	{                                                                     \
		if( this )                                                        \
			return &m_field;                                              \
		return 0;                                                         \
	}

BFME_GUARDED_INTERIOR( Rva001F6F90, 0x50 )
BFME_GUARDED_INTERIOR( Rva002C7CB0, 0x344 )
BFME_GUARDED_INTERIOR( Rva002C7CD0, 0x344 )
BFME_GUARDED_INTERIOR( Rva002C7CF0, 0x348 )
BFME_GUARDED_INTERIOR( Rva002C7D10, 0x348 )
BFME_GUARDED_INTERIOR( Rva007F4B70, 0x04 )

// ------------------------------------------------------------------ shape (2)

#define BFME_FLOAT_HOLDER( NAME, FLOAT_OFFSET )                           \
	class Hold##NAME                                                      \
	{                                                                     \
	public:                                                               \
		char m_lead[ FLOAT_OFFSET ];                                      \
		float m_value;                                                    \
	};

#define BFME_FORWARD_FLOAT( NAME, PTR_OFFSET, FLOAT_OFFSET )              \
	BFME_FLOAT_HOLDER( NAME, FLOAT_OFFSET )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		float get() const;                                                \
		char m_lead[ PTR_OFFSET ];                                        \
		Hold##NAME *m_holder;                                             \
	};                                                                    \
	float NAME::get() const                                               \
	{                                                                     \
		return m_holder->m_value;                                         \
	}

// The negative-displacement form: the holding pointer sits BACK bytes before
// the incoming pointer.  Written as a raw byte-offset read because that is
// exactly, and only, what the instruction does.
#define BFME_BACKWARD_FLOAT( NAME, BACK, FLOAT_OFFSET )                   \
	BFME_FLOAT_HOLDER( NAME, FLOAT_OFFSET )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		float get() const;                                                \
	};                                                                    \
	float NAME::get() const                                               \
	{                                                                     \
		const Hold##NAME *holder =                                        \
			*(const Hold##NAME *const *)( (const char *)this - BACK );    \
		return holder->m_value;                                           \
	}

BFME_FORWARD_FLOAT( Rva0016A950, 4, 0x510 )
BFME_FORWARD_FLOAT( Rva001F8DC0, 4, 0xd8 )
BFME_BACKWARD_FLOAT( Rva002B6E80, 0x33c, 0x68 )
BFME_BACKWARD_FLOAT( Rva002C60A0, 0x33c, 0x78 )
BFME_BACKWARD_FLOAT( Rva002C8370, 0x33c, 0x68 )
BFME_BACKWARD_FLOAT( Rva002C8380, 0x33c, 0x6c )
BFME_BACKWARD_FLOAT( Rva002C8390, 0x33c, 0x70 )
BFME_BACKWARD_FLOAT( Rva002C8530, 0x340, 0x84 )

// ------------------------------------------------------------------ shape (3)

class R1SumPair
{
public:
	int m_first;
	int m_second;
};

int Rva00537720( const R1SumPair *pair ) { return pair->m_second + pair->m_first; }
int Rva005BD310( const R1SumPair *pair ) { return pair->m_second + pair->m_first; }

#define BFME_MEMBER_SUM( NAME, OFFSET )                                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int sum() const;                                                  \
		char m_lead[ OFFSET ];                                            \
		R1SumPair *m_pair;                                                \
	};                                                                    \
	int NAME::sum() const                                                 \
	{                                                                     \
		return m_pair->m_second + m_pair->m_first;                        \
	}

BFME_MEMBER_SUM( Rva00537860, 4 )
BFME_MEMBER_SUM( Rva005378B0, 4 )
BFME_MEMBER_SUM( Rva005BD370, 8 )

// Same mnemonic sequence, different shape: mark a flag and hand back an
// interior pointer.  The flag store lands between the load and the add, which
// is scheduling; the `add` immediate is what separates the two rows.
#define BFME_FLAG_AND_OFFSET( NAME, ADVANCE )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char *get();                                                      \
		char m_lead[ 0x40 ];                                              \
		char *m_base;                                                     \
		char m_pad[ 4 ];                                                  \
		bool m_dirty;                                                     \
	};                                                                    \
	char *NAME::get()                                                     \
	{                                                                     \
		m_dirty = true;                                                   \
		return m_base + ADVANCE;                                          \
	}

BFME_FLAG_AND_OFFSET( Rva0073A320, 8 )
BFME_FLAG_AND_OFFSET( Rva0073A330, 12 )

// ------------------------------------------------------------------ shape (4)

#define BFME_CLEAR_TWO_INTS( NAME, FIRST, SECOND )                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void clear();                                                     \
		char m_lead[ FIRST ];                                             \
		int m_first;                                                      \
		char m_mid[ SECOND - FIRST - 4 ];                                 \
		int m_second;                                                     \
	};                                                                    \
	void NAME::clear()                                                    \
	{                                                                     \
		m_first = 0;                                                      \
		m_second = 0;                                                     \
	}

#define BFME_CLEAR_INT_THEN_BYTE( NAME, FIRST, SECOND )                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void clear();                                                     \
		char m_lead[ FIRST ];                                             \
		int m_first;                                                      \
		char m_mid[ SECOND - FIRST - 4 ];                                 \
		bool m_second;                                                    \
	};                                                                    \
	void NAME::clear()                                                    \
	{                                                                     \
		m_first = 0;                                                      \
		m_second = false;                                                 \
	}

BFME_CLEAR_TWO_INTS( Rva000B8E50, 0x0c, 0x24 )

// Two adjacent ints, the HIGHER one written first -- source order again.
class Rva006E1950
{
public:
	void clear();
	char m_lead[ 0x3c ];
	int m_low;
	int m_high;
};
void Rva006E1950::clear()
{
	m_high = 0;
	m_low = 0;
}
BFME_CLEAR_INT_THEN_BYTE( Rva0026EE60, 0x134, 0x32d )
BFME_CLEAR_INT_THEN_BYTE( Rva0051B4C0, 0x58, 0xa0 )

// Both stores are byte-wide here, which is what `xor al,al` proves.
class Rva006429B0
{
public:
	void clear();
	char m_lead[ 0x50 ];
	bool m_first;
	bool m_second;
};
void Rva006429B0::clear()
{
	m_second = false;
	m_first = false;
}

// No `this` at all: two globals.
extern int g_Glo00F52810;
extern int g_Glo00F5280C;
void Rva00AFE940()
{
	g_Glo00F52810 = 0;
	g_Glo00F5280C = 0;
}

// ------------------------------------------------------------------ shape (5)

#define BFME_VSLOT4( P )                                                  \
	virtual void P##_0();                                                 \
	virtual void P##_1();                                                 \
	virtual void P##_2();                                                 \
	virtual void P##_3();

#define BFME_VSLOT16( P )                                                 \
	BFME_VSLOT4( P##a )                                                   \
	BFME_VSLOT4( P##b )                                                   \
	BFME_VSLOT4( P##c )                                                   \
	BFME_VSLOT4( P##d )

class GenSlot00 { public: virtual void slot(); };
class GenSlot10 { public: BFME_VSLOT4( a ) virtual void slot(); };
class GenSlot14 { public: BFME_VSLOT4( a ) virtual void b_0(); virtual void slot(); };
class GenSlot18 { public: BFME_VSLOT4( a ) virtual void b_0(); virtual void b_1(); virtual void slot(); };
class GenSlot40 { public: BFME_VSLOT16( a ) virtual void slot(); };
class GenSlot240
{
public:
	BFME_VSLOT16( a ) BFME_VSLOT16( b ) BFME_VSLOT16( c )
	BFME_VSLOT16( d ) BFME_VSLOT16( e ) BFME_VSLOT16( f )
	BFME_VSLOT16( g ) BFME_VSLOT16( h ) BFME_VSLOT16( i )
	virtual void slot();
};

#define BFME_GUARDED_VIRTUAL( NAME, RECEIVER, OFFSET )                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
		char m_lead[ OFFSET ];                                            \
		RECEIVER *m_receiver;                                             \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		if( m_receiver )                                                  \
			m_receiver->slot();                                           \
	}

BFME_GUARDED_VIRTUAL( Rva000A0080, GenSlot40, 0x1c )
BFME_GUARDED_VIRTUAL( Rva0016CB10, GenSlot18, 0x28 )
BFME_GUARDED_VIRTUAL( Rva00489300, GenSlot14, 0x10 )
BFME_GUARDED_VIRTUAL( Rva00489320, GenSlot18, 0x10 )
BFME_GUARDED_VIRTUAL( Rva00489340, GenSlot10, 0x10 )
BFME_GUARDED_VIRTUAL( Rva00730C70, GenSlot240, 0x10 )
BFME_GUARDED_VIRTUAL( Rva008C3E10, GenSlot00, 0x50 )
