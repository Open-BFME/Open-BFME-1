// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FE70,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Buffer view for retail's inlined word-length test; AsciiString owns it.
struct BfmeBufferWT
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class BfmeStrWT : private AsciiString
{
public:
	BfmeStrWT(const BfmeStrWT &other) : AsciiString(other) {}
	~BfmeStrWT(void) {}

	void bfmeSetWT(const BfmeStrWT &other)
	{
		StringBase<char>::set(other);
	}

	bool bfmeFilledWT(void) const
	{
		const BfmeBufferWT *data = *reinterpret_cast<BfmeBufferWT *const *>(this);
		return data != 0 && data->m_bfmeLength != 0;
	}
};

struct BfmeEntryWT
{
	BfmeEntryWT(const BfmeEntryWT &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	BfmeStrWT m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

// View of the language object this TU reads its override from.  The global
// itself is retail's TheGlobalLanguageData, a GlobalLanguage* (0x012F1484);
// that class is declared by Common/System/game_engine_subsystems.h, so this is
// only the layout of the one member read here, reached through a cast.
class BfmeGlobalWT
{
public:
	char m_bfmePad000[0x124];				// +0x000
	BfmeEntryWT m_bfmeOverride;				// +0x124
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;			// retail 0x012F1484

class Gen_0043FE70
{
public:
	BfmeEntryWT bfmeEntryWT(void) const;

	char m_bfmePad000[0x804];				// +0x000
	BfmeEntryWT m_bfmeSlot;					// +0x804
};

// ?bfmeEntryWT@Gen_0043FE70@@QBE?AUBfmeEntryWT@@XZ
BfmeEntryWT Gen_0043FE70::bfmeEntryWT(void) const
{
	BfmeEntryWT entry(m_bfmeSlot);

	const BfmeEntryWT *override = &reinterpret_cast<BfmeGlobalWT *>( TheGlobalLanguageData )->m_bfmeOverride;

	if (override->m_bfmeText.bfmeFilledWT())
	{
		entry.m_bfmeText.bfmeSetWT(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
