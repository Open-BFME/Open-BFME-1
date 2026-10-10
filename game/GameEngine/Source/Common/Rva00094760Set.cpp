// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
public:
private:
	void *m_item;
};

class BfmeThingDN
{
public:
	void bfmeTellDN(void *what);
};

extern void *TheOptionGroupTarget;

class Rva00094760
{
	int m_00;
	int m_04;
	Rva0036CA00Str m_08;

public:
	void set(const Rva0036CA00Str &src);
};

void Rva00094760::set(const Rva0036CA00Str &src)
{
	reinterpret_cast<StringBase<char> *>(&m_08)->set(
		*reinterpret_cast<const StringBase<char> *>(&src));
	reinterpret_cast<BfmeThingDN *>(TheOptionGroupTarget)->bfmeTellDN(this);
}
