// cl: /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

inline void *operator new(unsigned int, void *place) { return place; }

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

struct BfmeBigAB
{
	int m_bfmeWords[6];
};

class BfmeThingAB
{
public:
	BfmeThingAB *bfmeInitAB(void *one, const BfmeBigAB *two);
	Rva005A7CF0FourStringRecord m_bfmeHead;
	BfmeBigAB m_bfmeBig;
};

BfmeThingAB *BfmeThingAB::bfmeInitAB(void *one, const BfmeBigAB *two)
{
	__assume(this != 0);
	new (&m_bfmeHead) Rva005A7CF0FourStringRecord(
		*static_cast<const Rva005A7CF0FourStringRecord *>(one));
	m_bfmeBig = *two;
	return this;
}
