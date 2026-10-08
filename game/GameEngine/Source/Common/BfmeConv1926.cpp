// cl: /O2 /DNDEBUG /MD
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The two bodies this file calls are StringBase<char>'s: 0x00887940 is
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (the parameter's destructor, reached
// through AsciiString's inline dtor) and 0x00887C90 is
// ?set@?$StringBase@D@@QAEXABV1@@Z, so the string is the narrow AsciiString.

struct BfmePairCQ
{
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

class BfmeHostCQ
{
public:
	void bfmeApplyCQ(AsciiString text, BfmePairCQ *pair);

	unsigned char m_bfmeHeadCQ[0x174];
	AsciiString m_bfmeTextCQ;
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

void BfmeHostCQ::bfmeApplyCQ(AsciiString text, BfmePairCQ *pair)
{
	AsciiString *dst = &m_bfmeTextCQ;

	(reinterpret_cast<StringBase<char> *>(dst))->set(
		reinterpret_cast<const StringBase<char> &>(text));

	m_bfmeACQ = pair->m_bfmeACQ;
	m_bfmeBCQ = pair->m_bfmeBCQ;
}