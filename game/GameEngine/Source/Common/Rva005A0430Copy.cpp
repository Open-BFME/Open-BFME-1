// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva00630D00UStr
{
private:
	void *m_item;
};

class Rva005A0430
{
	char m_00[8];
	char m_08;
	char m_09;
	char m_pad[0x22];
	Rva00630D00UStr m_2C;
	Rva00630D00UStr m_30;

public:
	void copy();
};

void Rva005A0430::copy()
{
	m_08 = 0;
	m_09 = 0;
	reinterpret_cast<StringBase<unsigned short> *>(&m_30)->set(
		*reinterpret_cast<const StringBase<unsigned short> *>(&m_2C));
}
