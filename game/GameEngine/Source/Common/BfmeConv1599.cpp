// Open-BFME5 conversions.

// The wide string member at +0x14 is the wide StringBase (retail releaseBuffer
// body 0x008881D0); retail destroys it through the base's inline destructor,
// which is why the owner's destructor calls releaseBuffer directly rather than
// an out-of-line wide-string destructor.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class BfmeStrWVSX
{
public:
	// clear() is the header's inline wrapper over the private releaseBuffer
	// (retail body 0x008881D0), which is the call retail makes here.
	~BfmeStrWVSX() { ((StringBase<unsigned short> *)this)->clear(); }

	unsigned short *m_bfme00;
};

class BfmeSinkVSX
{
public:
	virtual void bfmeSlot0VSX(int flags);
};

class BfmeOwnVSX
{
public:
	~BfmeOwnVSX();
	char m_bfmePad00[0x14];
	BfmeStrWVSX m_bfme14;
	BfmeSinkVSX *m_bfme18;
};

BfmeOwnVSX::~BfmeOwnVSX()
{
	BfmeSinkVSX *sink = m_bfme18;

	if (sink != 0)
		sink->bfmeSlot0VSX(1);
}
