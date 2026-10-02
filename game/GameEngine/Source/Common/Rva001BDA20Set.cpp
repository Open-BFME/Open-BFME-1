// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva001BDA20
{
	char m_00[0x10];
	Rva0036CA00Str m_10;
	int m_14;

public:
	void set(const Rva0036CA00Str &s);
};

void Rva001BDA20::set(const Rva0036CA00Str &s)
{
	reinterpret_cast<StringBase<char> *>(&m_10)->set(
		*reinterpret_cast<const StringBase<char> *>(&s));
	m_14 = 4;
}
