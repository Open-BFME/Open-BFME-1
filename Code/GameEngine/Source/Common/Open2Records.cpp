// cl: /DNDEBUG /MD /EHsc
//
// Eleven record copy bodies over one shape: a struct whose members include an
// AsciiString, copied either by its own copy constructor (__thiscall, `ret 4`,
// returning the receiver) or through STLport's `_Construct` (__cdecl over
// place and value, guarded by the null test placement new leaves behind).
//
// Every layout below was read off its own body's load/store pairs by a
// symbolic walk over the disassembly: registers are tracked as DEST- or
// SOURCE-relative addresses, so a copy through `lea esi,[eax+4]` reads the
// same as one through a direct displacement.  A layout is a CLAIM, not a
// transcription -- it fixes every member's offset and width, and a wrong width
// or a missed member fails the byte check on its own row.
//
// Only what these bodies reach is declared.  StringBase's copy constructor is
// private in the real header and the ledger holds the private mangling at
// 0x00887B60, so it is spelled private here with AsciiString as its friend.

// A gap between two copied members is layout, not data: retail's copy skips
// it, so it is spelled as a type whose copy constructor is empty.  A char
// array here is a member like any other and gets copied.
template <int N>
class Open2Gap
{
public:
	Open2Gap() {}
	Open2Gap( const Open2Gap<N> & ) {}
	char m_bytes[ N ];
};

// A pointer whose new owner takes a reference: retail copies the dword, tests
// it, and falls into `inc dword ptr [reg+N]` past the same `je` the outer
// guard uses.  The counter offset varies between records, so it is a
// parameter.
template <int COUNTER>
class Open2RefAt
{
public:
	Open2RefAt( const Open2RefAt<COUNTER> &other ) : m_held( other.m_held )
	{
		if( m_held )
			++*(int *)( (char *)m_held + COUNTER );
	}

	void *m_held;
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase( const StringBase<T> &src );		// retail 0x00887B60
	~StringBase();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const AsciiString &other ) : m_string( other.m_string ) {}
	~AsciiString() {}

	StringBase<char> m_string;
};

inline void *operator new( unsigned int, void *place ) { return place; }
inline void operator delete( void *, void * ) {}

// -------------------------------------------------------------------------
// 0x000FCED0 -- 73 bytes, ctor
class Open2Rec0FCED0
{
public:
	Open2Rec0FCED0( const Open2Rec0FCED0 &other );
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	AsciiString m_at1c;
	unsigned char m_at20;
};

// @??0Open2Rec0FCED0@@QAE@ABV0@@Z 0x000FCED0
Open2Rec0FCED0::Open2Rec0FCED0( const Open2Rec0FCED0 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at14( other.m_at14 ), m_at18( other.m_at18 ), m_at1c( other.m_at1c ), m_at20( other.m_at20 )
{
}

// -------------------------------------------------------------------------
// 0x00134500 -- 105 bytes, ctor
class Open2Rec134500
{
public:
	Open2Rec134500( const Open2Rec134500 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	int m_at08;
	int m_at0c;
	unsigned char m_at10;
	unsigned char m_at11;
};

// @??0Open2Rec134500@@QAE@ABV0@@Z 0x00134500
Open2Rec134500::Open2Rec134500( const Open2Rec134500 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at11( other.m_at11 )
{
}

// -------------------------------------------------------------------------
// 0x003A4420 -- 103 bytes, ctor
class Open2Rec3A4420
{
public:
	Open2Rec3A4420( const Open2Rec3A4420 &other );
	int m_at00;
	int m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	int m_at10;
};

// @??0Open2Rec3A4420@@QAE@ABV0@@Z 0x003A4420
Open2Rec3A4420::Open2Rec3A4420( const Open2Rec3A4420 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 )
{
}

// -------------------------------------------------------------------------
// 0x004F1120 -- 158 bytes, ctor
class Open2Rec4F1120
{
public:
	Open2Rec4F1120( const Open2Rec4F1120 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};

// @??0Open2Rec4F1120@@QAE@ABV0@@Z 0x004F1120
Open2Rec4F1120::Open2Rec4F1120( const Open2Rec4F1120 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at14( other.m_at14 ), m_at18( other.m_at18 ), m_at1c( other.m_at1c ), m_at20( other.m_at20 ), m_at24( other.m_at24 ), m_at28( other.m_at28 ), m_at2c( other.m_at2c ), m_at30( other.m_at30 )
{
}

// -------------------------------------------------------------------------
// 0x00582090 -- 104 bytes, ctor
class Open2Rec582090
{
public:
	Open2Rec582090( const Open2Rec582090 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
};

// @??0Open2Rec582090@@QAE@ABV0@@Z 0x00582090
Open2Rec582090::Open2Rec582090( const Open2Rec582090 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c )
{
}

// -------------------------------------------------------------------------
// 0x005822D0 -- 87 bytes, ctor
class Open2Rec5822D0
{
public:
	Open2Rec5822D0( const Open2Rec5822D0 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	int m_at08;
};

// @??0Open2Rec5822D0@@QAE@ABV0@@Z 0x005822D0
Open2Rec5822D0::Open2Rec5822D0( const Open2Rec5822D0 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 )
{
}

// -------------------------------------------------------------------------
// 0x006270C0 -- 155 bytes, ctor
class Open2Rec6270C0
{
public:
	Open2Rec6270C0( const Open2Rec6270C0 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	AsciiString m_at14;
	unsigned char m_at18;
};

// @??0Open2Rec6270C0@@QAE@ABV0@@Z 0x006270C0
Open2Rec6270C0::Open2Rec6270C0( const Open2Rec6270C0 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at14( other.m_at14 ), m_at18( other.m_at18 )
{
}

// -------------------------------------------------------------------------
// 0x0074A060 -- 79 bytes, ctor
class Open2Rec74A060
{
public:
	Open2Rec74A060( const Open2Rec74A060 &other );
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
	int m_at10;
	AsciiString m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
};

// @??0Open2Rec74A060@@QAE@ABV0@@Z 0x0074A060
Open2Rec74A060::Open2Rec74A060( const Open2Rec74A060 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at14( other.m_at14 ), m_at18( other.m_at18 ), m_at1c( other.m_at1c ), m_at20( other.m_at20 ), m_at24( other.m_at24 )
{
}

// -------------------------------------------------------------------------
// 0x00764FA0 -- 121 bytes, construct
class Open2Rec764FA0
{
public:
	AsciiString m_at00;
	unsigned char m_at04;
	Open2Gap< 0x3 > m_pad0;
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	unsigned char m_at20;
};

// @?Open2Construct764FA0@@YAXPAVOpen2Rec764FA0@@ABV1@@Z 0x00764FA0
void Open2Construct764FA0( Open2Rec764FA0 *place, const Open2Rec764FA0 &value )
{
	new ( place ) Open2Rec764FA0( value );
}

// -------------------------------------------------------------------------
// 0x00767F60 -- 56 bytes, ctor
class Open2Rec767F60
{
public:
	Open2Rec767F60( const Open2Rec767F60 &other );
	int m_at00;
	int m_at04;
	int m_at08;
	AsciiString m_at0c;
	Open2RefAt< 0x28 > m_at10;
};

// @??0Open2Rec767F60@@QAE@ABV0@@Z 0x00767F60
Open2Rec767F60::Open2Rec767F60( const Open2Rec767F60 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 )
{
}

// -------------------------------------------------------------------------
// 0x0081C6B0 -- 122 bytes, ctor
class Open2Rec81C6B0
{
public:
	Open2Rec81C6B0( const Open2Rec81C6B0 &other );
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	unsigned char m_at0c;
	Open2Gap< 0x3 > m_pad0;
	int m_at10;
	unsigned char m_at14;
	Open2Gap< 0x3 > m_pad1;
	int m_at18;
};

// @??0Open2Rec81C6B0@@QAE@ABV0@@Z 0x0081C6B0
Open2Rec81C6B0::Open2Rec81C6B0( const Open2Rec81C6B0 &other )
	: m_at00( other.m_at00 ), m_at04( other.m_at04 ), m_at08( other.m_at08 ), m_at0c( other.m_at0c ), m_at10( other.m_at10 ), m_at14( other.m_at14 ), m_at18( other.m_at18 )
{
}
