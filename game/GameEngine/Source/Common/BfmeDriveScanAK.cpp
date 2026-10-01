// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the CD-ROM drive scan at retail 0x006BA720, 196 bytes.  Every
// drive letter is tried in turn and the ones that answer DRIVE_CDROM are
// handed back to the derived class.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowAK/AsciiStringAK), which named retail's callee
// ?format@StringBaseNarrowAK@@QAAXVAsciiStringAK@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class StringBaseNarrowAK
{
protected:
	StringBaseNarrowAK(void)
	{
		m_bfmeNarrowAK = 0;
	}

	StringBaseNarrowAK(const char *text);

	StringBaseNarrowAK(const StringBaseNarrowAK &other);

	~StringBaseNarrowAK(void);

	char *m_bfmeNarrowAK;
};

class AsciiStringAK : public StringBaseNarrowAK
{
public:
	AsciiStringAK(void)
	{
	}

	AsciiStringAK(const char *text) : StringBaseNarrowAK(text)
	{
	}

	AsciiStringAK(const AsciiStringAK &other) : StringBaseNarrowAK(other)
	{
	}

	~AsciiStringAK(void)
	{
	}

	const char *bfmeTextAK(void) const
	{
		return (m_bfmeNarrowAK != 0) ? m_bfmeNarrowAK + 8 : "";
	}
};

extern "C" __declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char *root);

void bfmeResetAK(void);

class BfmeScannerAK
{
public:
	virtual void bfmeSlot0AK(void) = 0;
	virtual void bfmeSlot1AK(void) = 0;
	virtual void bfmeSlot2AK(void) = 0;
	virtual void bfmeSlot3AK(void) = 0;
	virtual void bfmeSlot4AK(void) = 0;
	virtual void bfmeSlot5AK(void) = 0;
	virtual void bfmeSlot6AK(void) = 0;
	virtual void bfmeSlot7AK(void) = 0;
	virtual void bfmeSlot8AK(void) = 0;
	virtual void bfmeSlot9AK(void) = 0;
	virtual void bfmeSlot10AK(void) = 0;
	virtual void bfmeFoundAK(const char *path) = 0;
	virtual void bfmeFinishAK(void) = 0;
	virtual void bfmeBeginAK(void) = 0;

	void bfmeScanAK(void);
};

void BfmeScannerAK::bfmeScanAK(void)
{
	bfmeResetAK();

	bfmeBeginAK();

	for (int letter = 'a', remaining = 26; remaining != 0; ++letter, --remaining)
	{
		AsciiStringAK path;

		((AsciiString &)path).format(AsciiString("%c:\\"), letter);

		if (GetDriveTypeA(path.bfmeTextAK()) == 5)
			bfmeFoundAK(path.bfmeTextAK());
	}

	bfmeFinishAK();
}
