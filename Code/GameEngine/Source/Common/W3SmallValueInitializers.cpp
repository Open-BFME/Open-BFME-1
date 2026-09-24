// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: two small value-type bodies out of d_0001466e.asm.
//
// 0x000643C0 opens with `mov eax,ecx`, which is the constructor tell, and takes
// one argument (`ret 4`). It writes seven consecutive dwords in ASCENDING order
// -- and MSVC 7.1 does not reorder straight-line constant stores, so that is
// source order: four zeros, two copies of 0x3F000000, then the argument. The
// two 0x3F000000 stores go through ONE register loaded once, which is what says
// they are the same constant written twice rather than two unrelated values,
// and 0x3F000000 is 0.5f -- an integer move of a float constant is how MSVC 7.1
// spells a float initialiser whose bit pattern it already knows.
//
// 0x000643F0 copies three consecutive dwords out of the object into a caller
// supplied block, again in ascending order. It leaves eax alone, so it is NOT a
// by-value return through a hidden pointer (which would have to return that
// pointer) -- it is a void member taking a destination.
//
// Identity is address-derived: the offsets are what retail writes, the member
// names are the offsets.

typedef float Real;

class Rva000643C0Value
{
public:
	Rva000643C0Value(void *owner);

	Real m_real00;										///< retail this+0x00
	Real m_real04;										///< retail this+0x04
	Real m_real08;										///< retail this+0x08
	Real m_real0C;										///< retail this+0x0C
	Real m_real10;										///< retail this+0x10
	Real m_real14;										///< retail this+0x14
	void *m_owner18;									///< retail this+0x18
};

Rva000643C0Value::Rva000643C0Value(void *owner)
{
	m_real00 = 0.0f;
	m_real04 = 0.0f;
	m_real08 = 0.0f;
	m_real0C = 0.0f;
	m_real10 = 0.5f;
	m_real14 = 0.5f;
	m_owner18 = owner;
}

struct Rva000643F0Triple
{
	int m_value00;										///< block+0x00
	int m_value04;										///< block+0x04
	int m_value08;										///< block+0x08
};

class Rva000643F0Value
{
public:
	Rva000643F0Triple *copyTo(Rva000643F0Triple *destination) const;

	int m_value00;										///< retail this+0x00
	int m_value04;										///< retail this+0x04
	int m_value08;										///< retail this+0x08
};

Rva000643F0Triple *Rva000643F0Value::copyTo(Rva000643F0Triple *destination) const
{
	destination->m_value00 = m_value00;
	destination->m_value04 = m_value04;
	destination->m_value08 = m_value08;
	return destination;
}
