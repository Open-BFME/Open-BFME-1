// Open-BFME5 conversions.

// Retail's 0x0014B6B0 constructor stores 0 and then calls 0x00887940 twice
// (tools/callees.py on that extent).  0x00887940 is retail's
// ?releaseBuffer@?$StringBase@D@@AAEXXZ, matched in
// game/Libraries/Source/string/StringBase.cpp, so the four-byte string members
// are real StringBase<char> buffers reached through AsciiString: its default
// constructor is the inline `m_data = 0` store and its destructor the inline
// releaseBuffer() call, exactly what this constructor emits.  The old
// TU-local BfmeStrVUP/bfmeClearVUP pair named a body retail has no symbol for.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeOwnVUP
{
public:
	BfmeOwnVUP();
	virtual void bfmeSlot0VUP();
	AsciiString m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad18[0x50];
	int m_bfme68;
	char m_bfmePad6c[0x50];
	int m_bfmebc;
	char m_bfmePadc0[0x50];
	int m_bfme110;
	char m_bfmePad114[0x50];
	int m_bfme164;
	char m_bfmePad168[0x50];
	AsciiString m_bfme1b8;
	int m_bfme1bc;
};

BfmeOwnVUP::BfmeOwnVUP()
	: m_bfme08(0), m_bfme0c(1), m_bfme10(2), m_bfme1bc(0)
{
	// Called through the base on purpose: AsciiString::clear is an inline
	// forwarder in ascii_string.h with no body in the retail ledger, so
	// odr-using it would emit a ?clear@AsciiString@@QAEXXZ COMDAT that
	// collides at link with a copy that is not retail's.
	// StringBase<char>::clear is retail's own 0x000680C0 five-byte body and
	// inlines to the same releaseBuffer() call these two members emit.
	((StringBase<char>&)m_bfme04).clear();
	((StringBase<char>&)m_bfme1b8).clear();
	m_bfme14 = 0;
	m_bfme68 = 0;
	m_bfmebc = 0;
	m_bfme110 = 0;
	m_bfme164 = 0;
}
