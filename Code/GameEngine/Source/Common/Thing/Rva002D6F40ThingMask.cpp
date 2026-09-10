// ?rva002d6f40@Rva002D6F40ThingMask@@QBE_NABV1@@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x002D6F40 is the negated twin of Rva00132A20ThingMask::rva00132a20
// (0x00132A20): it ANDs six 32-bit words from this and the const reference
// argument, then returns true only when every result word is zero. Its
// lexical class and member names are not recovered; this address-derived
// identity preserves that uncertainty while retaining the real thiscall body.

class Rva002D6F40ThingMask
{
	unsigned int m_words[6];

public:
	bool any() const;
	bool rva002d6f40(const Rva002D6F40ThingMask &) const;
};

bool Rva002D6F40ThingMask::any() const
{
	for (unsigned int i = 0; i < 6; ++i)
	{
		if (m_words[i] != 0)
			return true;
	}
	return false;
}

bool Rva002D6F40ThingMask::rva002d6f40(
	const Rva002D6F40ThingMask &other) const
{
	Rva002D6F40ThingMask tmp = *this;
	for (unsigned int i = 0; i < 6; ++i)
		tmp.m_words[i] &= other.m_words[i];
	return tmp.any() == false;
}
