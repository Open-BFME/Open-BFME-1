// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BfmeSinkBL::bfmeSubmitBL is reached through ILT 0x00039333. The two report
// senders prove the name, count, and four BfmeBlobBL arguments. The body copies
// the four blocks into the sink record, then submits a by-value name and count.

// AsciiStringBL is the narrow string retail passed by value at 0x0044A240.
// It derives from the real AsciiString, whose inline copy constructor and
// destructor forward to StringBase<char>'s out-of-line bodies at 0x00887B60
// and 0x00887940. A private declared-only narrow-string base left the object
// referencing two names nothing defines.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva004488B0Block
{
	void *first;
	void *second;
	void *third;
};

class AsciiStringBL : public AsciiString
{
public:
	AsciiStringBL(const AsciiStringBL &other) : AsciiString(other)
	{
	}

	~AsciiStringBL(void)
	{
	}
};

class BfmeBlobBL
{
public:
	char m_bfmePadBBL[12];
};

class Rva004488B0FourBlockRecord
{
public:
	void copy(const Rva004488B0Block &a, const Rva004488B0Block &b,
		const Rva004488B0Block &c, const Rva004488B0Block &d);
	void rva004498d0(AsciiStringBL name, int count);
};

class BfmeSinkBL
{
public:
	void bfmeSubmitBL(AsciiStringBL name, int count, BfmeBlobBL *first,
		BfmeBlobBL *second, BfmeBlobBL *third, BfmeBlobBL *fourth);

private:
	char m_bfmePad[0x12c8];
	Rva004488B0FourBlockRecord m_bfmeRecord;
};

#pragma comment(linker, "/alternatename:?copy@Rva004488B0FourBlockRecord@@QAEXABURva004488B0Block@@000@Z=?j_0002825e@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva004498d0@Rva004488B0FourBlockRecord@@QAEXVAsciiStringBL@@H@Z=?j_00043603@@YAXXZ")

void BfmeSinkBL::bfmeSubmitBL(AsciiStringBL name, int count,
	BfmeBlobBL *first, BfmeBlobBL *second,
	BfmeBlobBL *third, BfmeBlobBL *fourth)
{
	m_bfmeRecord.copy(
		*(const Rva004488B0Block *)first,
		*(const Rva004488B0Block *)second,
		*(const Rva004488B0Block *)third,
		*(const Rva004488B0Block *)fourth);
	m_bfmeRecord.rva004498d0(name, count);
}
