// Seven tiny __thiscall members that write four fields of the object and
// return nothing:
//
//     xor eax,eax / <four member stores> / ret
//
// WHAT THE BYTES SHOW, AND WHAT SEPARATES THESE FROM A CONSTRUCTOR: there is
// NO `mov eax,ecx`.  MSVC 7.1 always returns `this` from a __thiscall
// constructor, so a body that leaves eax holding the zero it materialised for
// the stores is not one.  These are void members that assign fields; the
// stores go through ecx directly.
//
// `xor eax,eax` before the stores means the compiler saw two or more zero
// assignments and hoisted the constant; the non-zero ones (100, 1, 20.0f) keep
// their immediate encoding, which is why they are visible as immediates in the
// retail bytes and are transcribed literally here.
//
// THE STORE ORDER IS SOURCE ORDER, and again the family proves it: 0x000C7A10
// writes +8 before +4, 0x003BCD20 writes +0xC4 before +0x48, 0x0026F0E0 writes
// +0x323, +0x324, +0x16C, +0x326 in that order, and 0x0029BD50 writes +0x3C
// and +0x40 before +0x38.  None of those is ascending, so none of them is the
// compiler laying out a memset.
//
// 0x0029BD50's store of an absolute address at offset 0 IS NOT A VPTR -- this
// is a void member, not a constructor, so nothing here initialises a class.
// It is an ordinary pointer-valued field; the address is a DIR32 site the
// patcher fills from retail and the extern name is address-derived.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern int R2Data010C0D90;

class Rva000C7A10
{
public:
	char m_pad00[ 0x4 ];
	int m_at04;
	int m_at08;
	char m_pad0C[ 0x4 ];
	int m_at10;
	int m_at14;
	void reset();
};
void Rva000C7A10::reset()
{
	m_at08 = 0;
	m_at04 = 100;
	m_at10 = 0;
	m_at14 = 0;
}

class Rva0026F0E0
{
public:
	char m_pad00[ 0x16C ];
	int m_at16C;
	char m_pad170[ 0x1B3 ];
	char m_at323;
	char m_at324;
	char m_pad325[ 0x1 ];
	char m_at326;
	void reset();
};
void Rva0026F0E0::reset()
{
	m_at323 = 0;
	m_at324 = 1;
	m_at16C = 0;
	m_at326 = 0;
}

class Rva0026F390
{
public:
	char m_pad00[ 0x1D8 ];
	int m_at1D8;
	int m_at1DC;
	int m_at1E0;
	int m_at1E4;
	void reset();
};
void Rva0026F390::reset()
{
	m_at1D8 = 1;
	m_at1DC = 0;
	m_at1E0 = 0;
	m_at1E4 = 0;
}

class Rva003BCD20
{
public:
	char m_pad00[ 0x48 ];
	int m_at48;
	char m_at4C;
	char m_at4D;
	char m_pad4E[ 0x76 ];
	int m_atC4;
	void reset();
};
void Rva003BCD20::reset()
{
	m_atC4 = 0;
	m_at48 = 0;
	m_at4C = 0;
	m_at4D = 0;
}

class Rva0060C2A0
{
public:
	char m_pad00[ 0x14 ];
	int m_at14;
	int m_at18;
	int m_at1C;
	int m_at20;
	void reset();
};
void Rva0060C2A0::reset()
{
	m_at14 = 0;
	m_at18 = 0;
	m_at1C = 0;
	m_at20 = 0;
}

class Rva007AE350
{
public:
	char m_pad00[ 0x58 ];
	int m_at58;
	int m_at5C;
	float m_at60;
	char m_at64;
	void reset();
};
void Rva007AE350::reset()
{
	m_at58 = 0;
	m_at5C = 0;
	m_at60 = 20.0f;
	m_at64 = 0;
}

class Rva0029BD50
{
public:
	void * m_at00;
	char m_pad04[ 0x34 ];
	int m_at38;
	int m_at3C;
	int m_at40;
	void reset();
};
void Rva0029BD50::reset()
{
	m_at00 = &R2Data010C0D90;
	m_at3C = 0;
	m_at40 = 0;
	m_at38 = 0;
}
