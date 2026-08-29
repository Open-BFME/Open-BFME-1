// cl: /DNDEBUG /MD /EHsc
//
// Fifteen instances of STLport's `_Construct` over records whose first members
// include an AsciiString.  Each is __cdecl over (place, value), guards the
// destination -- the null test placement new leaves behind, because the
// allocation function is inline and returns its argument yet the compiler
// still cannot prove it non-null -- and copies its record MEMBERWISE, so every
// record uses the implicit copy constructor.
//
// The shape was recovered by hand on 0x00765040 and 0x00768AE0 (see
// Open2Conv006.cpp); the fifteen layouts below were then read off each body's
// own load/store pairs, which is what fixes every member's offset and width.
// A layout is a claim, not a transcription: each one is byte-verified on its
// own row, and a wrong width or a missed member fails that check.
//
// Only what these bodies reach is declared.  StringBase's copy constructor is
// private in the real header and the ledger holds the private mangling at
// 0x00887B60, so it is spelled private here with AsciiString as its friend.


// A gap between two copied members is layout, not data: retail's copy skips it,
// so it is spelled as a type whose copy constructor is empty.  A plain char
// array here is a member like any other and gets copied, which lengthens every
// record that has one.
template <int N>
class Open2Gap
{
public:
	Open2Gap() {}
	Open2Gap( const Open2Gap<N> & ) {}
	char m_bytes[ N ];
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

class AsciiString
{
public:
	AsciiString( const AsciiString &other ) : m_string( other.m_string ) {}
	~AsciiString() {}

	StringBase<char> m_string;
};

inline void *operator new( unsigned int, void *place ) { return place; }
inline void operator delete( void *, void * ) {}

// Five of these records hold a pointer whose new owner takes a REFERENCE:
// retail copies the dword, tests it, and falls into `inc dword ptr [reg+N]`
// past the same `je` the outer null guard uses.  A raw int member is seven
// bytes short of that, so the member is a handle with an inline copy
// constructor.  The counter is at +4 in four of them and +0x28 in the fifth,
// which is why the offset is a parameter and not a fixed layout.
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

// -------------------------------------------------------------------------
// 0x000BF2C0 -- 91 bytes
class Open2Rec0BF2C0
{
public:
	AsciiString m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
};

// @?Open2Construct0BF2C0@@YAXPAVOpen2Rec0BF2C0@@ABV1@@Z 0x000BF2C0
void Open2Construct0BF2C0( Open2Rec0BF2C0 *place, const Open2Rec0BF2C0 &value )
{
	new ( place ) Open2Rec0BF2C0( value );
}

// -------------------------------------------------------------------------
// 0x001DE970 -- 103 bytes
class Open2Rec1DE970
{
public:
	AsciiString m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
};

// @?Open2Construct1DE970@@YAXPAVOpen2Rec1DE970@@ABV1@@Z 0x001DE970
void Open2Construct1DE970( Open2Rec1DE970 *place, const Open2Rec1DE970 &value )
{
	new ( place ) Open2Rec1DE970( value );
}

// -------------------------------------------------------------------------
// 0x002E0560 -- 87 bytes
class Open2Rec2E0560
{
public:
	int m_at00;
	AsciiString m_at04;
	unsigned char m_at08;
};

// @?Open2Construct2E0560@@YAXPAVOpen2Rec2E0560@@ABV1@@Z 0x002E0560
void Open2Construct2E0560( Open2Rec2E0560 *place, const Open2Rec2E0560 &value )
{
	new ( place ) Open2Rec2E0560( value );
}

// -------------------------------------------------------------------------
// 0x0033BCA0 -- 91 bytes
class Open2Rec33BCA0
{
public:
	AsciiString m_at00;
	int m_at04;
	int m_at08;
	int m_at0c;
};

// @?Open2Construct33BCA0@@YAXPAVOpen2Rec33BCA0@@ABV1@@Z 0x0033BCA0
void Open2Construct33BCA0( Open2Rec33BCA0 *place, const Open2Rec33BCA0 &value )
{
	new ( place ) Open2Rec33BCA0( value );
}

// -------------------------------------------------------------------------
// 0x00355050 -- 107 bytes
class Open2Rec355050
{
public:
	int m_at00;
	int m_at04;
	AsciiString m_at08;
	unsigned char m_at0c;
	Open2Gap< 0x1 > m_pad0;
	unsigned short m_at0e;
	int m_at10;
};

// @?Open2Construct355050@@YAXPAVOpen2Rec355050@@ABV1@@Z 0x00355050
void Open2Construct355050( Open2Rec355050 *place, const Open2Rec355050 &value )
{
	new ( place ) Open2Rec355050( value );
}

// -------------------------------------------------------------------------
// 0x003550F0 -- 107 bytes
class Open2Rec3550F0
{
public:
	int m_at00;
	int m_at04;
	AsciiString m_at08;
	unsigned char m_at0c;
	Open2Gap< 0x1 > m_pad0;
	unsigned short m_at0e;
	int m_at10;
};

// @?Open2Construct3550F0@@YAXPAVOpen2Rec3550F0@@ABV1@@Z 0x003550F0
void Open2Construct3550F0( Open2Rec3550F0 *place, const Open2Rec3550F0 &value )
{
	new ( place ) Open2Rec3550F0( value );
}

// -------------------------------------------------------------------------
// 0x00469840 -- 86 bytes
class Open2Rec469840
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
};

// @?Open2Construct469840@@YAXPAVOpen2Rec469840@@ABV1@@Z 0x00469840
void Open2Construct469840( Open2Rec469840 *place, const Open2Rec469840 &value )
{
	new ( place ) Open2Rec469840( value );
}

// -------------------------------------------------------------------------
// 0x0046A6E0 -- 86 bytes
class Open2Rec46A6E0
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
};

// @?Open2Construct46A6E0@@YAXPAVOpen2Rec46A6E0@@ABV1@@Z 0x0046A6E0
void Open2Construct46A6E0( Open2Rec46A6E0 *place, const Open2Rec46A6E0 &value )
{
	new ( place ) Open2Rec46A6E0( value );
}

// -------------------------------------------------------------------------
// 0x0046A760 -- 92 bytes
class Open2Rec46A760
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
	int m_at08;
};

// @?Open2Construct46A760@@YAXPAVOpen2Rec46A760@@ABV1@@Z 0x0046A760
void Open2Construct46A760( Open2Rec46A760 *place, const Open2Rec46A760 &value )
{
	new ( place ) Open2Rec46A760( value );
}

// -------------------------------------------------------------------------
// 0x0046A7F0 -- 86 bytes
class Open2Rec46A7F0
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
};

// @?Open2Construct46A7F0@@YAXPAVOpen2Rec46A7F0@@ABV1@@Z 0x0046A7F0
void Open2Construct46A7F0( Open2Rec46A7F0 *place, const Open2Rec46A7F0 &value )
{
	new ( place ) Open2Rec46A7F0( value );
}

// -------------------------------------------------------------------------
// 0x004741D0 -- 86 bytes
class Open2Rec4741D0
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
};

// @?Open2Construct4741D0@@YAXPAVOpen2Rec4741D0@@ABV1@@Z 0x004741D0
void Open2Construct4741D0( Open2Rec4741D0 *place, const Open2Rec4741D0 &value )
{
	new ( place ) Open2Rec4741D0( value );
}

// -------------------------------------------------------------------------
// 0x0052EBB0 -- 87 bytes
class Open2Rec52EBB0
{
public:
	unsigned char m_at00;
	Open2Gap< 0x3 > m_pad0;
	AsciiString m_at04;
	int m_at08;
};

// @?Open2Construct52EBB0@@YAXPAVOpen2Rec52EBB0@@ABV1@@Z 0x0052EBB0
void Open2Construct52EBB0( Open2Rec52EBB0 *place, const Open2Rec52EBB0 &value )
{
	new ( place ) Open2Rec52EBB0( value );
}

// -------------------------------------------------------------------------
// 0x00768B60 -- 106 bytes
class Open2Rec768B60
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	AsciiString m_at0c;
	Open2RefAt< 0x28 > m_at10;
};

// @?Open2Construct768B60@@YAXPAVOpen2Rec768B60@@ABV1@@Z 0x00768B60
void Open2Construct768B60( Open2Rec768B60 *place, const Open2Rec768B60 &value )
{
	new ( place ) Open2Rec768B60( value );
}

// -------------------------------------------------------------------------
// 0x00768D20 -- 103 bytes
class Open2Rec768D20
{
public:
	AsciiString m_at00;
	unsigned char m_at04;
	Open2Gap< 0x3 > m_pad0;
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
};

// @?Open2Construct768D20@@YAXPAVOpen2Rec768D20@@ABV1@@Z 0x00768D20
void Open2Construct768D20( Open2Rec768D20 *place, const Open2Rec768D20 &value )
{
	new ( place ) Open2Rec768D20( value );
}

// -------------------------------------------------------------------------
// 0x004603F0 -- 86 bytes
class Open2Rec4603F0
{
public:
	AsciiString m_at00;
	Open2RefAt< 0x4 > m_at04;
};

// @?Open2Construct4603F0@@YAXPAVOpen2Rec4603F0@@ABV1@@Z 0x004603F0
void Open2Construct4603F0( Open2Rec4603F0 *place, const Open2Rec4603F0 &value )
{
	new ( place ) Open2Rec4603F0( value );
}
