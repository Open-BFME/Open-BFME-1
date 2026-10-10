// Open-BFME5 conversions. The returned name is an AsciiString: the
// hidden-return copy is StringBase<char>'s copy constructor (0x00887B60).

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeHostVTN;

// retail walks the override chain through ILT 0x000022BB, which targets
// Overridable::getFinalOverride (matching row 0x00087A80).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class BfmeSinkVTN
{
};

class BfmeHostVTN
{
public:
	int m_bfme00;
	BfmeSinkVTN *m_bfme04;
	char m_bfmePad08[0x18];
	AsciiString m_bfme20;
};

class BfmeOwnVTN
{
public:
	AsciiString bfmeNameVTN();
};

AsciiString BfmeOwnVTN::bfmeNameVTN()
{
	BfmeHostVTN *host = *(BfmeHostVTN **)((char *)this - 0x60);

	if (host != 0 && host->m_bfme04 != 0)
		host = (BfmeHostVTN *)(const void *)((const Overridable *)host->m_bfme04)->getFinalOverride();

	return host->m_bfme20;
}
