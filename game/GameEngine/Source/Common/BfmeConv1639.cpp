// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

// The +0x0C member is EA's AsciiString (StringBase<char>): retail's destructor
// at 0x001B5550 calls 0x00887940 on it, which is
// ?releaseBuffer@?$StringBase@D@@AAEXXZ, matched in
// game/Libraries/Source/string/StringBase.cpp.  The inline base destructor in
// string_base.h is what makes the call, so the real header types the member.
#include "ascii_string.h"

class BfmeSinkVUH
{
public:
	virtual void bfmeSlot0VUH(int flags);
};

class BfmeBaseVUH
{
public:
	~BfmeBaseVUH()
	{
		BfmeSinkVUH *sink = m_bfme04;

		if (sink != 0)
			sink->bfmeSlot0VUH(1);

		m_bfme04 = 0;
	}

	// This TU carries no body for its own vtable slot 0: retail installs the
	// shared single-entry base vftable (0x0107FCB0, whose only entry is the
	// 0x0043D168 thunk) from the destructor, so the slot stays undefined here
	// and pure is how that is spelled.  The vftable itself is emitted out of
	// line, so no key-function reference is left behind.
	virtual void bfmeSlot0VUH() = 0;
	BfmeSinkVUH *m_bfme04;
	char m_bfmePad08[4];
};

class BfmeOwnVUH : public BfmeBaseVUH
{
public:
	~BfmeOwnVUH();
	AsciiString m_bfme0c;
};

BfmeOwnVUH::~BfmeOwnVUH()
{
}
