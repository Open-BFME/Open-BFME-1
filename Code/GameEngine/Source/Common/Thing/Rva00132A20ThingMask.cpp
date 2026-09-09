// ?rva00132a20@Rva00132A20ThingMask@@QBE_NABV1@@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00132A20 intersects six 32-bit words from the object and the
// const reference argument, then scans those six result words.  Its lexical
// class and member names are not recovered; this address-derived identity
// preserves that uncertainty while retaining the real thiscall body.

class Rva00132A20ThingMask
{
	unsigned int m_words[6];

public:
	bool any() const;
	bool rva00132a20(const Rva00132A20ThingMask &) const;
};

bool Rva00132A20ThingMask::any() const
{
	for (unsigned int i = 0; i < 6; ++i)
	{
		if (m_words[i] != 0)
			return true;
	}
	return false;
}

bool Rva00132A20ThingMask::rva00132a20(
	const Rva00132A20ThingMask &that) const
{
	Rva00132A20ThingMask tmp = that;
	for (unsigned int i = 0; i < 6; ++i)
		tmp.m_words[i] &= m_words[i];
	return tmp.any();
}
