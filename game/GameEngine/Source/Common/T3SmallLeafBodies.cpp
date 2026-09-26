// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: leaf bodies out of d_0005b6c0.asm that carry no relocation at
// all, so every byte of them is proof.
//
// Four byte-identical 19-byte rows (0x695C0 0x699A0 0x69AD0 0x69B50) are one
// shape: fld / fcomp / fnstsw / test ah,5 / jp. `test ah,5` masks C0 and C2, and
// the parity of that two-bit result is even for {greater, equal, unordered} and
// odd only for less-than, so the fall-through arm is a<b -- a strict float
// less-than returning Int, callee-cleaning two stack pointers. The compiler did
// not fold them, so they are four distinct functions over four distinct types;
// their shared tail from +19 is already claimed elsewhere as an ICF fold, which
// is why each row stops at 19 bytes rather than the full 32.
//
// 0x63E50 is the integer twin of the same idea done with sbb/neg, and it is
// UNSIGNED: sbb after cmp reads CF, so the member at +0x18 compares as an
// unsigned quantity.
//
// The remaining bodies are constructors and a small value swap. A leading
// `mov eax,ecx` marks each constructor.
//
// Identity everywhere here is address-derived: none of these touch a named
// global or call anything, which is exactly why they verify completely and
// exactly why nothing names them.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// ---------------------------------------------------------------------------
// the four float less-than comparators

struct Rva000695C0Key { Real m_value; };
struct Rva000699A0Key { Real m_value; };
struct Rva00069AD0Key { Real m_value; };
struct Rva00069B50Key { Real m_value; };

// ?Rva000695C0Less@@YGHPBURva000695C0Key@@0@Z
Int __stdcall Rva000695C0Less(const Rva000695C0Key *a, const Rva000695C0Key *b)
{
	return a->m_value < b->m_value;
}

// ?Rva000699A0Less@@YGHPBURva000699A0Key@@0@Z
Int __stdcall Rva000699A0Less(const Rva000699A0Key *a, const Rva000699A0Key *b)
{
	return a->m_value < b->m_value;
}

// ?Rva00069AD0Less@@YGHPBURva00069AD0Key@@0@Z
Int __stdcall Rva00069AD0Less(const Rva00069AD0Key *a, const Rva00069AD0Key *b)
{
	return a->m_value < b->m_value;
}

// ?Rva00069B50Less@@YGHPBURva00069B50Key@@0@Z
Int __stdcall Rva00069B50Less(const Rva00069B50Key *a, const Rva00069B50Key *b)
{
	return a->m_value < b->m_value;
}

// ---------------------------------------------------------------------------

// ?Rva00069520Swap@@YAXAAM0@Z
void Rva00069520Swap(Real &a, Real &b)
{
	Real temp = a;
	a = b;
	b = temp;
}

// the unsigned key compared at +0x18
class Rva00063E50Node
{
public:
	Int isLessThan(const Rva00063E50Node *other) const;

private:
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_key;									///< retail this+0x18
};

// ?isLessThan@Rva00063E50Node@@QBEHPBV1@@Z
Int Rva00063E50Node::isLessThan(const Rva00063E50Node *other) const
{
	return m_key < other->m_key;
}

// a two-field record: pointer then a 16-bit tag
class Rva0006AFF0Entry
{
public:
	Rva0006AFF0Entry(void *item, unsigned short tag);

private:
	void *m_item;										///< retail this+0x00
	unsigned short m_tag;								///< retail this+0x04
};

// ??0Rva0006AFF0Entry@@QAE@PAXG@Z
Rva0006AFF0Entry::Rva0006AFF0Entry(void *item, unsigned short tag)
{
	m_item = item;
	m_tag = tag;
}

// a 0x1A-byte record whose second field starts life TRUE
class Rva00069410Record
{
public:
	Rva00069410Record(void *owner);

private:
	void *m_owner;										///< retail this+0x00
	bool m_enabled;										///< retail this+0x04
	Int m_value08;										///< retail this+0x08
	Int m_value0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_value14;										///< retail this+0x14
	bool m_flag18;										///< retail this+0x18
	bool m_flag19;										///< retail this+0x19
};

// ??0Rva00069410Record@@QAE@PAX@Z
Rva00069410Record::Rva00069410Record(void *owner)
{
	m_owner = owner;
	m_enabled = true;
	m_value08 = 0;
	m_value0C = 0;
	m_value10 = 0;
	m_value14 = 0;
	m_flag18 = false;
	m_flag19 = false;
}
