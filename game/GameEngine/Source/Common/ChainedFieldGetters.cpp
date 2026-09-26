// 38 seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<OUTER>] / mov eax,[eax+<INNER>] / ret     (dword, 21)
//     mov eax,[ecx+<OUTER>] / mov al,[eax+<INNER>]  / ret     (byte,  17)
//
// WHAT THE BYTES SHOW.  A dword is read out of the object and used as a base;
// a second field is then read at a fixed displacement from IT.  Both
// displacements are disp8, so both are small and either sign is available, and
// the second load's operand size is the only thing separating the two groups.
//
// TWO AXES: the holder displacement and the inner displacement.  Eleven members
// reach the holder at a NEGATIVE displacement (-12, -28, -32); the bytes cannot
// say whether that is a sub-object `this` pointing into the middle of a larger
// object, a container-of computation in the source, or something else, so those
// are spelled as an explicit backward cast and no inheritance relationship is
// claimed.  This is the same shape, and the same reading, as the disp32 family
// in Q1HolderByteGetters.cpp and Q1HolderDwordGetters.cpp.
//
// The byte group returns `unsigned char`: only al is written and the upper
// bytes of eax are left holding the holder pointer, so the bytes cannot
// distinguish it from `signed char`, `bool` or a one-byte enum.  The dword
// group returns `int` for the same reason in reverse -- four bytes moved with a
// plain load say nothing more.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_CHAIN_INNER( NAME, INNER, TYPE )                                 \
	class Inner##NAME                                                         \
	{                                                                         \
	public:                                                                   \
		char m_lead[ INNER ];                                                 \
		TYPE m_value;                                                         \
	};

#define BFME_CHAIN_AT( NAME, OUTER, TYPE )                                    \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		TYPE get() const;                                                     \
                                                                              \
		char        m_lead[ OUTER ];                                          \
		Inner##NAME *m_holder;                                                \
	};                                                                        \
	TYPE NAME::get() const                                                    \
	{                                                                         \
		return m_holder->m_value;                                             \
	}

#define BFME_CHAIN_BEFORE( NAME, BACK, TYPE )                                 \
	class Sub##NAME                                                           \
	{                                                                         \
	public:                                                                   \
		Inner##NAME *m_holder;                                                \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		TYPE get() const;                                                     \
	};                                                                        \
	TYPE NAME::get() const                                                    \
	{                                                                         \
		return ( (const Sub##NAME *)( (const char *)this - ( BACK ) ) )       \
			->m_holder->m_value;                                             \
	}

BFME_CHAIN_INNER( Rva001506D0ChainedDword, 0x8, int )
BFME_CHAIN_AT( Rva001506D0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0016A220ChainedDword, 0x20, int )
BFME_CHAIN_AT( Rva0016A220ChainedDword, 0x1C, int )

BFME_CHAIN_INNER( Rva0016A9A0ChainedDword, 0x68, int )
BFME_CHAIN_AT( Rva0016A9A0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0016A9B0ChainedDword, 0x6C, int )
BFME_CHAIN_AT( Rva0016A9B0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0016E4C0ChainedDword, 0x38, int )
BFME_CHAIN_AT( Rva0016E4C0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0016E4D0ChainedDword, 0x34, int )
BFME_CHAIN_AT( Rva0016E4D0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0016E4E0ChainedDword, 0x48, int )
BFME_CHAIN_AT( Rva0016E4E0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva001C0DA0ChainedDword, 0x4, int )
BFME_CHAIN_AT( Rva001C0DA0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva001EAC10ChainedDword, 0x4C, int )
BFME_CHAIN_AT( Rva001EAC10ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0020E850ChainedDword, 0x38, int )
BFME_CHAIN_BEFORE( Rva0020E850ChainedDword, 0xC, int )

BFME_CHAIN_INNER( Rva00233D60ChainedDword, 0x10, int )
BFME_CHAIN_AT( Rva00233D60ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva00233D70ChainedDword, 0x14, int )
BFME_CHAIN_AT( Rva00233D70ChainedDword, 0x4, int )

class Rva00233D50Dword
{
public:
	int get() const;
};

int Rva00233D50Dword::get() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva002BA020Dword
{
public:
	int get() const;
};

int Rva002BA020Dword::get() const
{
	return *(const int *)((const char *)this + 4);
}

BFME_CHAIN_INNER( Rva0026A930ChainedDword, 0x8, int )
BFME_CHAIN_BEFORE( Rva0026A930ChainedDword, 0x20, int )

BFME_CHAIN_INNER( Rva00270140ChainedDword, 0x50, int )
BFME_CHAIN_AT( Rva00270140ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva00281C80ChainedDword, 0x40, int )
BFME_CHAIN_BEFORE( Rva00281C80ChainedDword, 0x1C, int )

BFME_CHAIN_INNER( Rva00289850ChainedDword, 0x24, int )
BFME_CHAIN_AT( Rva00289850ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva0028ED90ChainedDword, 0x4, int )
BFME_CHAIN_AT( Rva0028ED90ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva002B53A0ChainedDword, 0x64, int )
BFME_CHAIN_AT( Rva002B53A0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva002B53B0ChainedDword, 0x68, int )
BFME_CHAIN_AT( Rva002B53B0ChainedDword, 0x4, int )

BFME_CHAIN_INNER( Rva00494290ChainedDword, 0x18, int )
BFME_CHAIN_AT( Rva00494290ChainedDword, 0x8, int )

BFME_CHAIN_INNER( Rva005BD350ChainedDword, 0x8, int )
BFME_CHAIN_AT( Rva005BD350ChainedDword, 0x8, int )

BFME_CHAIN_INNER( Rva0016A990ChainedByte, 0x71, unsigned char )
BFME_CHAIN_AT( Rva0016A990ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva0016E500ChainedByte, 0x28, unsigned char )
BFME_CHAIN_AT( Rva0016E500ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva001EE920ChainedByte, 0x60, unsigned char )
BFME_CHAIN_BEFORE( Rva001EE920ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva001F8910ChainedByte, 0x60, unsigned char )
BFME_CHAIN_BEFORE( Rva001F8910ChainedByte, 0xC, unsigned char )

BFME_CHAIN_INNER( Rva001FB5A0ChainedByte, 0x60, unsigned char )
BFME_CHAIN_BEFORE( Rva001FB5A0ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva001FBF90ChainedByte, 0x60, unsigned char )
BFME_CHAIN_BEFORE( Rva001FBF90ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva00204480ChainedByte, 0x60, unsigned char )
BFME_CHAIN_BEFORE( Rva00204480ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva00281C90ChainedByte, 0x3D, unsigned char )
BFME_CHAIN_BEFORE( Rva00281C90ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva0029C260ChainedByte, 0x28, unsigned char )
BFME_CHAIN_AT( Rva0029C260ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva002AC100ChainedByte, 0x2C, unsigned char )
BFME_CHAIN_AT( Rva002AC100ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva002B53C0ChainedByte, 0x6D, unsigned char )
BFME_CHAIN_AT( Rva002B53C0ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva002B53D0ChainedByte, 0x6E, unsigned char )
BFME_CHAIN_AT( Rva002B53D0ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva002BA030ChainedByte, 0x78, unsigned char )
BFME_CHAIN_AT( Rva002BA030ChainedByte, 0x4, unsigned char )

BFME_CHAIN_INNER( Rva002D0610ChainedByte, 0x31, unsigned char )
BFME_CHAIN_BEFORE( Rva002D0610ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva002D3520ChainedByte, 0x6C, unsigned char )
BFME_CHAIN_BEFORE( Rva002D3520ChainedByte, 0x1C, unsigned char )

BFME_CHAIN_INNER( Rva002D6D30ChainedByte, 0x68, unsigned char )
BFME_CHAIN_AT( Rva002D6D30ChainedByte, 0xC, unsigned char )

BFME_CHAIN_INNER( Rva0058B600ChainedByte, 0x10, unsigned char )
BFME_CHAIN_AT( Rva0058B600ChainedByte, 0x4, unsigned char )
