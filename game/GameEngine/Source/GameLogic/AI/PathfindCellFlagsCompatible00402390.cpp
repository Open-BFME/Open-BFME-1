// cl: /O2 /DNDEBUG /MD
//
// Retail 0x00402390 (90 B): free cdecl bool, reached through ILT 0x0001951F.
// After bfmeLayersCompatible (0x004022D0, ILT 0x00025F04) it requires the
// two cells' flag word (+0x0C) to agree in bit 20, bit 21 and the two-bit
// field at bits 22-23. The meaning of those bits is unproven, so the function
// and the fields keep address-derived names. Bool accessors for the one-bit
// fields keep retail's separate shift/xor/test per bit, and the explicit
// `return false` / `return true` tail keeps the shared early-fail block.

#include "../../../Include/Common/ScalarTypes.h"


class PathfindCell
{
public:
	Bool getBit20() const { return m_bit20; }
	Bool getBit21() const { return m_bit21; }

	unsigned char m_pad[0x0c];
	UnsignedInt m_low : 20;
	UnsignedInt m_bit20 : 1;
	UnsignedInt m_bit21 : 1;
	UnsignedInt m_bits22 : 2;
	UnsignedInt m_high : 8;
};

Bool bfmeLayersCompatible(const PathfindCell *a, const PathfindCell *b);

Bool rva00402390(const PathfindCell *a, const PathfindCell *b)
{
	if (!bfmeLayersCompatible(a, b))
		return false;
	if (a->getBit20() != b->getBit20())
		return false;
	if (a->getBit21() != b->getBit21())
		return false;
	if (a->m_bits22 != b->m_bits22)
		return false;
	return true;
}
