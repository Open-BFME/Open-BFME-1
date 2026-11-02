// cl: /O2 /DNDEBUG /MD /EHsc
//
// Four 10-byte thiscall leaves with identical bytes, each its own retail body
// (retail was linked without identical-COMDAT folding):
//     mov eax,[esp+4] ; mov [ecx+0x14],eax ; ret 4
// No ILT stub reaches any of them. They were gen-alias placeholders borrowing a
// byte-identical COMDAT from another unit.
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

#pragma pack( pop )
