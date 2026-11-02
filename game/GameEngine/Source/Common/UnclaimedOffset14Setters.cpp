// cl: /O2 /DNDEBUG /MD /EHsc
//
// Seventeen 10-byte thiscall leaves with identical bytes, each its own retail
// body (retail was linked without identical-COMDAT folding):
//     mov eax,[esp+4] ; mov [ecx+0x14],eax ; ret 4
// Four have no ILT stub; thirteen are reached through one (noted per body), so
// they are external functions whose real names are still unknown. All were
// gen-alias placeholders borrowing a byte-identical COMDAT from another unit.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the
// argument is a dword of unknown type.

#pragma pack( push, 1 )

// 0x007F09B0 (10 bytes): stores its dword argument at +0x14
class Rva007F09B0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva007F09B0::set( int value )
{
	m_14 = value;
}

// 0x007F0B60 (10 bytes): stores its dword argument at +0x14
class Rva007F0B60
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva007F0B60::set( int value )
{
	m_14 = value;
}

// 0x007F9050 (10 bytes): stores its dword argument at +0x14
class Rva007F9050
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva007F9050::set( int value )
{
	m_14 = value;
}

// 0x008088E0 (10 bytes): stores its dword argument at +0x14
class Rva008088E0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva008088E0::set( int value )
{
	m_14 = value;
}

// 0x00097090 (10 bytes): same shape, reached through ILT stub 0x0003D19F
class Rva00097090
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva00097090::set( int value )
{
	m_14 = value;
}

// 0x001A1A10 (10 bytes): same shape, reached through ILT stub 0x00009269
class Rva001A1A10
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva001A1A10::set( int value )
{
	m_14 = value;
}

// 0x002B9D20 (10 bytes): same shape, reached through ILT stub 0x0004B4D4
class Rva002B9D20
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva002B9D20::set( int value )
{
	m_14 = value;
}

// 0x0036ADB0 (10 bytes): same shape, reached through ILT stub 0x0003A80F
class Rva0036ADB0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva0036ADB0::set( int value )
{
	m_14 = value;
}

// 0x0037D090 (10 bytes): same shape, reached through ILT stub 0x00007392
class Rva0037D090
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva0037D090::set( int value )
{
	m_14 = value;
}

// 0x004E25B0 (10 bytes): same shape, reached through ILT stub 0x00039D83
class Rva004E25B0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva004E25B0::set( int value )
{
	m_14 = value;
}

// 0x005376C0 (10 bytes): same shape, reached through ILT stub 0x0004AAF2
class Rva005376C0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva005376C0::set( int value )
{
	m_14 = value;
}

// 0x006013E0 (10 bytes): same shape, reached through ILT stub 0x00035F44
class Rva006013E0
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva006013E0::set( int value )
{
	m_14 = value;
}

// 0x00662780 (10 bytes): same shape, reached through ILT stub 0x0003347E
class Rva00662780
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva00662780::set( int value )
{
	m_14 = value;
}

// 0x006D4520 (10 bytes): same shape, reached through ILT stub 0x00005DDA
class Rva006D4520
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva006D4520::set( int value )
{
	m_14 = value;
}

// 0x006DF630 (10 bytes): same shape, reached through ILT stub 0x00009DB3
class Rva006DF630
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva006DF630::set( int value )
{
	m_14 = value;
}

// 0x00751B40 (10 bytes): same shape, reached through ILT stub 0x00031020
class Rva00751B40
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva00751B40::set( int value )
{
	m_14 = value;
}

// 0x007B7F90 (10 bytes): same shape, reached through ILT stub 0x0001AEE2
class Rva007B7F90
{
public:
	void set( int value );

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva007B7F90::set( int value )
{
	m_14 = value;
}

#pragma pack( pop )
