// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME: retail 0x0039DAC0, 274 bytes, reached only through ILT
// 0x00049940; no caller or string names it, so the method keeps an
// address-derived name.
//
// The receiver holds one attribute-pool index, like AttributeHandleStandIn
// (0x0039D550): the index is bounded by the 0x88-byte entries of the pool at
// 0x012F1000 and -1 means empty. For the entry it names, the body appends to
// an AsciiString the name string at +0x20 of every record in the two pointer
// vectors at +0x18 and +0x30, then the name of every set bit of the 181-bit
// mask at +0x48 from the KindOf bit-name table at 0x012AA068
// (BitFlags<181>, the getSingleBitFromName table).
//
// Shape notes: each record's name is read through one reference (retail
// loads its buffer pointer once for both the length and the text), and the
// bit loop counts with a signed Int (jl) while the mask test takes an
// unsigned position (shr, not sar).

#include <string.h>

#include "ascii_string.h"

typedef int Int;

struct Rva0039DAC0Record
{
	unsigned char m_pad00[0x20];
	AsciiString m_name;					// +0x20
};

struct Rva0039DAC0Entry
{
	unsigned char m_pad00[0x18];
	Rva0039DAC0Record **m_firstStart;			// +0x18
	Rva0039DAC0Record **m_firstFinish;			// +0x1C
	unsigned char m_pad20[0x10];
	Rva0039DAC0Record **m_secondStart;			// +0x30
	Rva0039DAC0Record **m_secondFinish;			// +0x34
	unsigned char m_pad38[0x10];
	unsigned int m_kindMask[6];				// +0x48
	unsigned char m_pad60[0x28];				// ends the entry at 0x88

	bool testKind(unsigned int pos) const
	{
		return (m_kindMask[pos >> 5] & (1U << (pos & 31))) != 0;
	}
};

struct BfmeAttributePool
{
	Rva0039DAC0Entry *m_start;				// +0x00
	Rva0039DAC0Entry *m_finish;				// +0x04
};

// Rva00C6B2C0PoolInitialization.cpp owns the 12-byte pool cell at VA 012F1000.
struct Rva00EF1000Storage;
extern Rva00EF1000Storage Rva00EF1000Global;
#define TheBfmeAttributePool (reinterpret_cast<BfmeAttributePool &>(Rva00EF1000Global))

extern const char *TheKindOfBitNames[];			// 0x012AA068

class Rva0039DAC0Owner
{
public:
	void appendNames(AsciiString *out);

private:
	Int m_handle;						// +0x00
};

// ?appendNames@Rva0039DAC0Owner@@QAEXPAVAsciiString@@@Z
void Rva0039DAC0Owner::appendNames(AsciiString *out)
{
	if (m_handle >= TheBfmeAttributePool.m_finish - TheBfmeAttributePool.m_start)
		return;
	if (m_handle == -1)
		return;

	Rva0039DAC0Entry *entry = &TheBfmeAttributePool.m_start[m_handle];

	for (Rva0039DAC0Record **it = entry->m_firstStart; it != entry->m_firstFinish; ++it)
	{
		const AsciiString &name = (*it)->m_name;
		out->StringBase<char>::concat(name.str(), name.getLength());
	}

	for (Rva0039DAC0Record **it = entry->m_secondStart; it != entry->m_secondFinish; ++it)
	{
		const AsciiString &name = (*it)->m_name;
		out->StringBase<char>::concat(name.str(), name.getLength());
	}

	for (Int bit = 0; bit < 181; ++bit)
	{
		if (entry->testKind(bit))
		{
			const char *name = TheKindOfBitNames[bit];
			if (name != 0)
				out->StringBase<char>::concat(name, strlen(name));
		}
	}
}
