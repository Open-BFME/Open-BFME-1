// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// The table at VA 0x010E7688 holds ILT 0x0001D499 -> deleting destructor
// 0x00339FA0, already emitted by BfmeOwnCDDeletingDestructor.cpp.
extern "C" void *__identifier("??_7BfmeOwnCD@@6B@")[];

class BfmeStrVTY
{
public:
	BfmeStrVTY() { m_bfme00 = 0; }
	~BfmeStrVTY() { ((StringBase<unsigned short> *)this)->clear(); }
	unsigned short *m_bfme00;
};

class BfmeOwnVTY
{
public:
	BfmeOwnVTY(BfmeStrVTY *first, const BfmeStrVTY &second);
	void *m_00;
	BfmeStrVTY m_bfme04;
	BfmeStrVTY *m_bfme08;
};

BfmeOwnVTY::BfmeOwnVTY(BfmeStrVTY *first, const BfmeStrVTY &second)
	: m_00(__identifier("??_7BfmeOwnCD@@6B@")), m_bfme08(first)
{
	((StringBase<char> *)&m_bfme04)->set(*(const StringBase<char> *)first);
	((StringBase<char> *)first)->set(*(const StringBase<char> *)&second);
}
