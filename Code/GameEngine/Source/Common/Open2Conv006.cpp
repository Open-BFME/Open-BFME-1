// cl: /DNDEBUG /MD /EHsc
//
// Two bodies out of the string-heavy run at 0x0076xxxx: a constructor and a
// copy constructor over a record whose first three members are AsciiStrings.
// Both carry an SEH frame, which is why this file re-enables exceptions -- the
// base build is /EHs-c- and the frame is a flag, not code.
//
// Only what these bodies reach is declared.  StringBase's constructors are
// private in the real header and the ledger holds the private mangling at
// 0x00887B60, so they are spelled private here with AsciiString as the friend
// that reaches them; the default constructor is inline because retail stores
// the null through the member rather than calling anything.

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set( const T *text, int length );		// retail 0x00887D20
	void set( const StringBase<T> &src );		// retail 0x00887C90

	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	bool isNotEmpty() const { return !isEmpty(); }

private:
	StringBase() { m_data = 0; }
	StringBase( const StringBase<T> &src );		// retail 0x00887B60
	~StringBase();					// retail 0x00887940

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() {}
	AsciiString( const AsciiString &other ) : m_string( other.m_string ) {}
	~AsciiString() {}

	void set( const char *text, int length ) { m_string.set( text, length ); }

	AsciiString &operator=( const AsciiString &other )
	{
		m_string.set( other.m_string );
		return *this;
	}

	void set( const AsciiString &other ) { m_string.set( other.m_string ); }
	bool isNotEmpty() const { return m_string.isNotEmpty(); }

	StringBase<char> m_string;
};

// ---------------------------------------------------------------------------
// 0x00761E10 -- constructor.
//
//     lea ecx,[esi+0xc] / mov [ecx],0 / push 0 / push "" / mov [esi+4],-1
//     call set / mov [esi],0 / mov [esi+8],0
//
// The string is the LAST member by offset yet its construction is emitted
// first, which is member-constructor order; everything else is written in the
// body, and the body's order is what the remaining stores show -- the -1 before
// the set call, the two zeroes after it.

class Rva00761E10
{
public:
	Rva00761E10();

	int m_first;
	int m_state;
	int m_third;
	AsciiString m_name;
};

// @??0Rva00761E10@@QAE@XZ 0x00761E10
Rva00761E10::Rva00761E10()
{
	m_state = -1;
	m_name.set( "", 0 );
	m_first = 0;
	m_third = 0;
}

// ---------------------------------------------------------------------------
// 0x00762170 -- copy constructor.
//
// Three string copies at +0, +4 and +8 through the private copy constructor,
// then thirteen plain member copies.  The unwind state is written twice, as a
// dword 0 after the first string and a byte 1 after the second: two states for
// three subobjects, because nothing after the third can throw.

class Rva00762170
{
public:
	Rva00762170( const Rva00762170 &other );

	AsciiString m_a;
	AsciiString m_b;
	AsciiString m_c;
	int m_d;
	int m_e;
	int m_f;
	int m_g;
	int m_h;
	int m_i;
	unsigned char m_j;
	unsigned char m_k;
	unsigned char m_pad[2];
	int m_l;
	int m_m;
	int m_n;
	unsigned char m_o;
};

// @??0Rva00762170@@QAE@ABV0@@Z 0x00762170
Rva00762170::Rva00762170( const Rva00762170 &other )
	: m_a( other.m_a ), m_b( other.m_b ), m_c( other.m_c )
{
	m_d = other.m_d;
	m_e = other.m_e;
	m_f = other.m_f;
	m_g = other.m_g;
	m_h = other.m_h;
	m_i = other.m_i;
	m_j = other.m_j;
	m_k = other.m_k;
	m_l = other.m_l;
	m_m = other.m_m;
	m_n = other.m_n;
	m_o = other.m_o;
}

// ---------------------------------------------------------------------------
// 0x00761AF0 -- STLport's random-access `copy` over a 20-byte record.
//
//     sub ecx,esi / imul 0x66666667 / sar edx,3 ... test eax,eax / jle empty
//     <loop> mov [edi],[esi] ... call set ... add esi,0x14 / add edi,0x14
//     dec ebx / jne / mov eax,edi / ret ... empty: mov eax,[esp+0x10] / ret
//
// The reciprocal 0x66666667 with `sar 3` is a signed divide by 20, which fixes
// the element at five dwords.  Element assignment is memberwise in declaration
// order and the string arm is `set(const StringBase &)`, not operator=, so the
// record's own assignment is the implicit one over an AsciiString whose
// operator= forwards to set.  The count is computed once and counted DOWN,
// which is STLport's `for (Distance n = last - first; n > 0; --n)`.

class Open2761AF0Record
{
public:
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_text;
	int m_e;
};

// @?Open2CopyRecords@@YAPAVOpen2761AF0Record@@PAV1@00@Z 0x00761AF0
Open2761AF0Record *Open2CopyRecords( Open2761AF0Record *first,
	Open2761AF0Record *last, Open2761AF0Record *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

// ---------------------------------------------------------------------------
// 0x007609B0 -- `return m_text.isNotEmpty()` with both halves inlined.
//
//     mov eax,[ecx+0x200] / test eax,eax / je one / cmp word [eax+4],0 / je one
//     xor eax,eax / <tail> ... one: mov eax,1 / <tail>
//     tail: xor ecx,ecx / test al,al / sete cl / mov al,cl / ret
//
// The tail is DUPLICATED rather than shared, and it negates a value the
// compiler already knows: that is `!isEmpty()` where isEmpty is itself inline
// and short-circuits.  `cmp word ptr [eax+4],0` pins the length field to a
// 16-bit member at +4 of the header, right after the reference count.

class Rva007609B0
{
public:
	bool hasText( void ) const;
	char m_pad[0x200];
	AsciiString m_text;
};

// @?hasText@Rva007609B0@@QBE_NXZ 0x007609B0
bool Rva007609B0::hasText( void ) const
{
	return m_text.isNotEmpty();
}

// ---------------------------------------------------------------------------
// 0x00764220 -- take a string BY VALUE and copy it into a member.
//
// `ret 8` covers an int and one pointer, and the body destroys the second
// argument in place (`lea ecx,[esp+0x14] / call ~StringBase`) after copying it
// out -- that is a by-value class parameter the callee owns, which is also
// where the unwind state and the SEH frame come from.  The member's address is
// computed BEFORE the argument is pushed, which is assignment
// (`m_text = text`), not `m_text.set(text)`: set pushes the argument first.

class Rva00764220
{
public:
	void setup( int value, AsciiString text );
	char m_pad[0x78];
	bool m_armed;
	char m_pad2[3];
	int m_value;
	char m_pad3[0xc];
	AsciiString m_text;
};

// @?setup@Rva00764220@@QAEXHVAsciiString@@@Z 0x00764220
void Rva00764220::setup( int value, AsciiString text )
{
	m_armed = false;
	m_value = value;
	m_text = text;
}
