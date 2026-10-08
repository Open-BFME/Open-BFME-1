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
	AsciiStringBL(const AsciiStringBL &other) throw() : AsciiString(other)
	{
	}

	~AsciiStringBL(void) throw()
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
	// Its two bodies are only reached through the retail ILT thunks above;
	// the call sites below type the thunk address directly.
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

// Retail reaches both record bodies through incremental-link thunks at ILT
// 0x0002825e and 0x00043603, so the object references those addresses
// directly instead of locally declared out-of-line members.
extern void j_0002825e();
extern void j_00043603();

void BfmeSinkBL::bfmeSubmitBL(AsciiStringBL name, int count,
	BfmeBlobBL *first, BfmeBlobBL *second,
	BfmeBlobBL *third, BfmeBlobBL *fourth)
{
	typedef void (Rva004488B0FourBlockRecord::*Copy)(
		const Rva004488B0Block &, const Rva004488B0Block &,
		const Rva004488B0Block &, const Rva004488B0Block &);
	union { void (*fn)(); Copy call; } copy = { j_0002825e };
	typedef void (Rva004488B0FourBlockRecord::*Submit)(AsciiStringBL, int);
	union { void (*fn)(); Submit call; } submit = { j_00043603 };

	(m_bfmeRecord.*copy.call)(
		*(const Rva004488B0Block *)first,
		*(const Rva004488B0Block *)second,
		*(const Rva004488B0Block *)third,
		*(const Rva004488B0Block *)fourth);
	(m_bfmeRecord.*submit.call)(name, count);
}
