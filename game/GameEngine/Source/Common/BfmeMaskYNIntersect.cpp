// ?bfmeTestYN@BfmeOwnerYN@@QAEDPAUBfmeMaskYN@@@Z
// Open-BFME5 conversions.

// The two calls this body makes are read straight out of its retail bytes:
//   call 0x4316FB (thunk -> 0x00216600)  ?bfmeAnyZX@BfmeFlagsZX@@QBE_NPBV1@@Z
//   call 0x422C5A (thunk -> 0x001C2920)  ?notEquals@Rva001C2920Vec3@@QBE_NPBU1@@Z
// Both owners are matched TUs elsewhere in game/, so the references below carry
// their real names rather than invented BfmeMaskYN members. Both interfaces are
// three words wide, the same as the mask this body ANDs, so the objects are
// passed through as the owning TU's view of them.
class BfmeFlagsZX
{
public:
	bool bfmeAnyZX(const BfmeFlagsZX *other) const;
};

struct Rva001C2920Vec3
{
	int v[3];

	bool notEquals(const Rva001C2920Vec3 *other) const;
};

struct BfmeSubYN
{
	unsigned char m_bfmeBytesYN[4];
};

struct BfmeMaskYN
{
	int m_bfmeAYN;
	int m_bfmeBYN;
	int m_bfmeCYN;
};

class BfmeOwnerYN
{
public:
	char bfmeTestYN(BfmeMaskYN *other);

	unsigned char m_bfmeHeadYN[4];
	BfmeMaskYN m_bfmeMaskYN;
	BfmeSubYN m_bfmeSubYN;
};

char BfmeOwnerYN::bfmeTestYN(BfmeMaskYN *other)
{
	if (reinterpret_cast<const BfmeFlagsZX *>(other)->bfmeAnyZX(
			reinterpret_cast<const BfmeFlagsZX *>(&m_bfmeSubYN)))
		return 0;

	BfmeMaskYN masked = *other;

	masked.m_bfmeAYN &= m_bfmeMaskYN.m_bfmeAYN;
	masked.m_bfmeBYN &= m_bfmeMaskYN.m_bfmeBYN;
	masked.m_bfmeCYN &= m_bfmeMaskYN.m_bfmeCYN;

	return reinterpret_cast<const Rva001C2920Vec3 *>(&m_bfmeMaskYN)->notEquals(
			reinterpret_cast<const Rva001C2920Vec3 *>(&masked)) == 0;
}
