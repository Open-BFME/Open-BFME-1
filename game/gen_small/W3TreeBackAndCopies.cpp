// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: two relocation-free bodies out of d_0001466e.asm.
//
// 0x000647B0 is a null-guarded seven-dword copy: a free function, both operands
// on the stack, `ret` with no argument cleanup. The stores ascend and MSVC 7.1
// does not reorder straight-line stores, so that is source order; guarding only
// the destination and not the source is what says the source was assumed valid.
//
// 0x00065F10 indexes an array of 0x40-byte elements hanging directly off the
// object (`shl 6` then a base+index address) and returns the dword 0x0C into the
// element. It cleans EIGHT bytes for two arguments while reading only the first,
// so the second is present in the signature and unused in the body.
//
// Identity is address-derived.

typedef int Int;

// ---------------------------------------------------------------------------

struct Rva000647B0Block
{
	Int m_value00;										///< block+0x00
	Int m_value04;										///< block+0x04
	Int m_value08;										///< block+0x08
	Int m_value0C;										///< block+0x0C
	Int m_value10;										///< block+0x10
	Int m_value14;										///< block+0x14
	Int m_value18;										///< block+0x18
};

// ?Rva000647B0Copy@@YAXPAURva000647B0Block@@PBU1@@Z
void Rva000647B0Copy(Rva000647B0Block *destination, const Rva000647B0Block *source)
{
	if (destination != 0)
	{
		destination->m_value00 = source->m_value00;
		destination->m_value04 = source->m_value04;
		destination->m_value08 = source->m_value08;
		destination->m_value0C = source->m_value0C;
		destination->m_value10 = source->m_value10;
		destination->m_value14 = source->m_value14;
		destination->m_value18 = source->m_value18;
	}
}

// ---------------------------------------------------------------------------

struct Rva00065F10Element
{
	unsigned char m_unreconstructed_00[0x0C];
	void *m_value0C;									///< element+0x0C
	unsigned char m_unreconstructed_10[0x40 - 0x10];
};

class Rva00065F10Table
{
public:
	void *lookup(Int index, Int unused) const;

private:
	Rva00065F10Element m_elements[1];					///< retail this+0x00
};

// ?lookup@Rva00065F10Table@@QBEPAXHH@Z
void *Rva00065F10Table::lookup(Int index, Int unused) const
{
	return m_elements[index].m_value0C;
}
