// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: more relocation-free leaf bodies out of d_0005b6c0.asm.
//
// Every row here compares byte for byte with nothing masked out: none of them
// touches a global, a string or a vftable, so there is no DIR32 site anywhere
// and no REL32 either. That also means nothing in the image names them, so the
// identities are address-derived -- what the bytes do fix is the shape, the
// field offsets and, for the constructors, the SOURCE ORDER of the stores
// (MSVC 7.1 does not reorder straight-line constant stores).
//
// Rva0007B6B0Release is the one body with a real name recoverable from shape:
// `dec [ecx+4] / jg over / mov eax,[ecx] / push 1 / call [eax]` is the standard
// `delete this` through a virtual destructor -- push 1 selects the deleting arm
// of the scalar deleting destructor in slot 0 -- guarded by a decremented
// counter at +4. That is a reference-counted Release(), and it is why the class
// is declared polymorphic here even though no vftable address appears.
//
// Rva0007C680Clamp and Rva0007C6A0Max are __cdecl free functions. The Max form
// is `__b < __a ? __a : __b` and not STLport's `__a < __b ? __b : __a`: retail
// jumps on GREATER to keep the FIRST argument, which is the reversed spelling.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// ---------------------------------------------------------------------------
// a six-field record whose 0x0C and 0x14 slots start at -1

class Rva00060850Record
{
public:
	Rva00060850Record(void);

private:
	Int m_value00;										///< retail this+0x00
	Int m_value04;										///< retail this+0x04
	Int m_value08;										///< retail this+0x08
	Int m_index0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_index14;										///< retail this+0x14
};

// ??0Rva00060850Record@@QAE@XZ
Rva00060850Record::Rva00060850Record(void)
{
	m_value00 = 0;
	m_value04 = 0;
	m_value08 = 0;
	m_index0C = -1;
	m_value10 = 0;
	m_index14 = -1;
}

// ---------------------------------------------------------------------------
// the unsigned key at +0x18 compared through a free __stdcall predicate

struct Rva00064250Node
{
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_key;									///< retail this+0x18
};

// ?Rva00064250Less@@YGHPBURva00064250Node@@0@Z
Int __stdcall Rva00064250Less(const Rva00064250Node *a, const Rva00064250Node *b)
{
	return a->m_key < b->m_key;
}

// ---------------------------------------------------------------------------
// a two-character pair

class Rva00065330Pair
{
public:
	Rva00065330Pair(char first, char second);

private:
	char m_first;										///< retail this+0x00
	char m_second;										///< retail this+0x01
};

// ??0Rva00065330Pair@@QAE@DD@Z
Rva00065330Pair::Rva00065330Pair(char first, char second)
{
	m_first = first;
	m_second = second;
}

// ---------------------------------------------------------------------------
// a settings record that defaults to 800x600

class Rva0007BBD0Settings
{
public:
	Rva0007BBD0Settings(void);

private:
	Int m_value00;										///< retail this+0x00
	Int m_value04;										///< retail this+0x04
	Real m_scale08;										///< retail this+0x08
	Int m_value0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_value14;										///< retail this+0x14
	Int m_width;										///< retail this+0x18
	Int m_height;										///< retail this+0x1C
};

// ??0Rva0007BBD0Settings@@QAE@XZ
Rva0007BBD0Settings::Rva0007BBD0Settings(void)
{
	m_value00 = 0;
	m_value04 = 1;
	m_scale08 = 1.0f;
	m_value0C = 0;
	m_value10 = 1;
	m_value14 = 1;
	m_width = 800;
	m_height = 600;
}

// ---------------------------------------------------------------------------
// the larger settings record; bytes are flags, dwords are counts

class Rva0007BD80Options
{
public:
	Rva0007BD80Options(void);

private:
	Int m_value00;										///< retail this+0x00
	bool m_flag04;										///< retail this+0x04
	bool m_flag05;										///< retail this+0x05
	bool m_flag06;										///< retail this+0x06
	bool m_flag07;										///< retail this+0x07
	bool m_flag08;										///< retail this+0x08
	bool m_flag09;										///< retail this+0x09
	Int m_value0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_value14;										///< retail this+0x14
	bool m_flag18;										///< retail this+0x18
	bool m_flag19;										///< retail this+0x19
	bool m_flag1A;										///< retail this+0x1A
	Int m_value1C;										///< retail this+0x1C
	bool m_flag20;										///< retail this+0x20
	bool m_flag21;										///< retail this+0x21
	bool m_flag22;										///< retail this+0x22
	bool m_flag23;										///< retail this+0x23
	Int m_value24;										///< retail this+0x24
	Int m_value28;										///< retail this+0x28
	Int m_value2C;										///< retail this+0x2C
};

// ??0Rva0007BD80Options@@QAE@XZ
Rva0007BD80Options::Rva0007BD80Options(void)
{
	m_value00 = 2500;
	m_flag04 = true;
	m_flag05 = true;
	m_flag06 = false;
	m_flag07 = true;
	m_flag08 = true;
	m_flag09 = true;
	m_value0C = 100;
	m_value10 = 25;
	m_value14 = 300000;
	m_flag18 = true;
	m_flag19 = true;
	m_flag1A = true;
	m_value1C = 0;
	m_flag20 = true;
	m_flag21 = true;
	m_flag22 = true;
	m_flag23 = true;
	m_value24 = 1;
	m_value28 = 1;
	m_value2C = 1;
}

// ---------------------------------------------------------------------------
// two free comparison helpers

// ?Rva0007C680Clamp@@YAHHHH@Z
Int Rva0007C680Clamp(Int low, Int value, Int high)
{
	if (value < low)
	{
		return low;
	}

	if (value > high)
	{
		return high;
	}

	return value;
}

// ?Rva0007C6A0Max@@YAABHABH0@Z
const Int &Rva0007C6A0Max(const Int &a, const Int &b)
{
	return a > b ? a : b;
}

// ---------------------------------------------------------------------------
// the reference-counted Release()

class Rva0007B6B0Counted
{
public:
	virtual ~Rva0007B6B0Counted();

	void release(void);

private:
	Int m_refCount;										///< retail this+0x04
};

// ?release@Rva0007B6B0Counted@@QAEXXZ
void Rva0007B6B0Counted::release(void)
{
	if (--m_refCount <= 0)
	{
		delete this;
	}
}
