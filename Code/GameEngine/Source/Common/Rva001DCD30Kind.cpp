// cl: /O2 /Ob0

template <int N>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &) const;
};

class Rva001DCD30
{
	char m_lead[8];
	BitFlags<69> m_kindOf;

public:
	int isNotAnyKindOf(const Thing &mask) const;
};

int Rva001DCD30::isNotAnyKindOf(const Thing &mask) const
{
	return !mask.isAnyKindOf(m_kindOf);
}
