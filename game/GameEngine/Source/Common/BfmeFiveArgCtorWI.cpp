// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the five-parameter constructor at retail 0x003BEA30, 111 bytes.
// The leading eight bytes are a plain by-reference struct copy; the flag
// parameter lands last even though it is declared before the second string.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Keep the entry point's existing parameter type while using the real
// StringBase<char> copy constructor and releaseBuffer through AsciiString.
class AsciiStringWI;

class BfmeStrWI
{
public:
	BfmeStrWI(const AsciiStringWI &other)
		: m_bfmeData(reinterpret_cast<const AsciiString &>(other)) {}
	~BfmeStrWI(void) {}

private:
	AsciiString m_bfmeData;
};

struct BfmePairWI
{
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class Gen_003BEA30
{
public:
	Gen_003BEA30(const BfmePairWI &pair, int kind, const AsciiStringWI &first,
		bool flag, const AsciiStringWI &second);

	BfmePairWI m_bfmePair;					// +0x00
	int m_bfmeKind;						// +0x08
	BfmeStrWI m_bfmeFirst;					// +0x0C
	BfmeStrWI m_bfmeSecond;					// +0x10
	bool m_bfmeFlag;					// +0x14
};

// ??0Gen_003BEA30@@QAE@ABUBfmePairWI@@HABVAsciiStringWI@@_N1@Z
Gen_003BEA30::Gen_003BEA30(const BfmePairWI &pair, int kind,
	const AsciiStringWI &first, bool flag, const AsciiStringWI &second)
	: m_bfmePair(pair),
	  m_bfmeKind(kind),
	  m_bfmeFirst(first),
	  m_bfmeSecond(second),
	  m_bfmeFlag(flag)
{
}
