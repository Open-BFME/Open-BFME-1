// cl: /DNDEBUG /MD /EHsc
//
// Six record destructors.  A record destructor's only visible work is
// destroying the members that HAVE a destructor, in reverse declaration order,
// so each class below carries only the AsciiStrings and the gaps between them
// -- that is all these bytes attest to, and inventing the rest would be
// inventing identity.
//
// The unwind state counts down alongside the calls (2, 1, 0, then -1), which
// is the same evidence: one destructible subobject per state.
//
// StringBase's destructor is private in the real header and the ledger holds
// the private mangling at 0x00887940, so it is spelled private here with
// AsciiString as its friend.

// A gap is layout, not data: it has no destructor, so it contributes nothing.
template <int N>
class Open2Gap
{
public:
	char m_bytes[ N ];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	~StringBase();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() {}

	StringBase<char> m_string;
};

// -------------------------------------------------------------------------
// 0x0005F4B0 -- 103 bytes, 4 string member(s)
class Open2Dtor05F4B0
{
public:
	~Open2Dtor05F4B0();
	Open2Gap< 0x10 > m_pad0;
	AsciiString m_at10;
	AsciiString m_at14;
	AsciiString m_at18;
	AsciiString m_at1c;
};

// @??1Open2Dtor05F4B0@@QAE@XZ 0x0005F4B0
Open2Dtor05F4B0::~Open2Dtor05F4B0()
{
}

// -------------------------------------------------------------------------
// 0x0013A8E0 -- 180 bytes, 10 string member(s)
class Open2Dtor13A8E0
{
public:
	~Open2Dtor13A8E0();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	Open2Gap< 0x8 > m_pad0;
	AsciiString m_at1c;
	AsciiString m_at20;
	Open2Gap< 0x4 > m_pad1;
	AsciiString m_at28;
	Open2Gap< 0x10 > m_pad2;
	AsciiString m_at3c;
	Open2Gap< 0x4 > m_pad3;
	AsciiString m_at44;
};

// @??1Open2Dtor13A8E0@@QAE@XZ 0x0013A8E0
Open2Dtor13A8E0::~Open2Dtor13A8E0()
{
}

// -------------------------------------------------------------------------
// 0x0040B830 -- 118 bytes, 5 string member(s)
class Open2Dtor40B830
{
public:
	~Open2Dtor40B830();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	Open2Gap< 0x8 > m_pad0;
	AsciiString m_at14;
	Open2Gap< 0x70 > m_pad1;
	AsciiString m_at88;
};

// @??1Open2Dtor40B830@@QAE@XZ 0x0040B830
Open2Dtor40B830::~Open2Dtor40B830()
{
}

// -------------------------------------------------------------------------
// 0x004793C0 -- 102 bytes, 4 string member(s)
class Open2Dtor4793C0
{
public:
	~Open2Dtor4793C0();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
};

// @??1Open2Dtor4793C0@@QAE@XZ 0x004793C0
Open2Dtor4793C0::~Open2Dtor4793C0()
{
}

// -------------------------------------------------------------------------
// 0x005A7D90 -- 102 bytes, 4 string member(s)
class Open2Dtor5A7D90
{
public:
	~Open2Dtor5A7D90();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
};

// @??1Open2Dtor5A7D90@@QAE@XZ 0x005A7D90
Open2Dtor5A7D90::~Open2Dtor5A7D90()
{
}

// -------------------------------------------------------------------------
// 0x0069CF00 -- 141 bytes, 7 string member(s)
class Open2Dtor69CF00
{
public:
	~Open2Dtor69CF00();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	AsciiString m_at14;
	Open2Gap< 0x5c > m_pad0;
	AsciiString m_at74;
};

// @??1Open2Dtor69CF00@@QAE@XZ 0x0069CF00
Open2Dtor69CF00::~Open2Dtor69CF00()
{
}
