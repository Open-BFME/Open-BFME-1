// cl: /O2 /DNDEBUG /MD
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// The two bodies this file calls are StringBase<char>'s: 0x00887940 is
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (ledger) and 0x00887C90 is
// ?set@?$StringBase@D@@QAEXABV1@@Z. string_base.h names UnicodeString a
// friend, so this TU's string is a UnicodeString view over that char
// instantiation: both steps are reached through the base spelling and only
// the declarations are needed here.
class UnicodeString
{
public:
	~UnicodeString()
	{
		(reinterpret_cast<StringBase<char> *>(this))->releaseBuffer();
	}

	void *m_data;
};

struct BfmePairCQ
{
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

class BfmeHostCQ
{
public:
	void bfmeApplyCQ(UnicodeString text, BfmePairCQ *pair);

	unsigned char m_bfmeHeadCQ[0x174];
	UnicodeString m_bfmeTextCQ;
	int m_bfmeACQ;
	int m_bfmeBCQ;
};

void BfmeHostCQ::bfmeApplyCQ(UnicodeString text, BfmePairCQ *pair)
{
	UnicodeString *dst = &m_bfmeTextCQ;

	(reinterpret_cast<StringBase<char> *>(dst))->set(
		reinterpret_cast<const StringBase<char> &>(text));

	m_bfmeACQ = pair->m_bfmeACQ;
	m_bfmeBCQ = pair->m_bfmeBCQ;
}