// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0013A1A0
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	StringBase<char> m_10;
	int m_14;
	int m_18;
	StringBase<char> m_1C;
	StringBase<char> m_20;
	int m_24;
	StringBase<char> m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	StringBase<char> m_3C;
	int m_40;
	StringBase<char> m_44;

public:
	void copyTo(Rva0013A1A0 &dest) const;
};

void Rva0013A1A0::copyTo(Rva0013A1A0 &dest) const
{
	dest.m_00.set(m_00);
	dest.m_04.set(m_04);
	dest.m_08.set(m_08);
	dest.m_0C.set(m_0C);
	dest.m_10.set(m_10);
	dest.m_14 = m_14;
	dest.m_18 = m_18;
	dest.m_1C.set(m_1C);
	dest.m_20.set(m_20);
	dest.m_24 = m_24;
	dest.m_28.set(m_28);
	dest.m_2C = m_2C;
	dest.m_30 = m_30;
	dest.m_34 = m_34;
	dest.m_38 = m_38;
	dest.m_3C.set(m_3C);
	dest.m_40 = m_40;
	dest.m_44.set(m_44);
}
