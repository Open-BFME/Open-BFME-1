// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

inline void *operator new(unsigned int, void *place) { return place; }
inline void operator delete(void *, void *) {}

class Rva005A7CF0FourStringRecord
{
public:
	Rva005A7CF0FourStringRecord(
		const AsciiString &a,
		const AsciiString &b,
		const AsciiString &c,
		const AsciiString &d);
	Rva005A7CF0FourStringRecord(const Rva005A7CF0FourStringRecord &other);

private:
	AsciiString m_a;
	AsciiString m_b;
	AsciiString m_c;
	AsciiString m_d;
};

struct Rva005A84D0Tail
{
	int m_values[6];
};

class BfmeThingAB
{
public:
	BfmeThingAB(const BfmeThingAB &other) : m_base(other.m_base)
	{
		m_tail = other.m_tail;
	}
	~BfmeThingAB();

private:
	Rva005A7CF0FourStringRecord m_base;
	Rva005A84D0Tail m_tail;
};

void constructRva005A84D0Record(BfmeThingAB *place, const BfmeThingAB &value)
{
	new (place) BfmeThingAB(value);
}
