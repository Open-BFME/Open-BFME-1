// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FD60,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Keep retail's direct word comparison; getLength() materializes an int.
struct BfmeBufferWS
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

struct BfmeEntryWS
{
	BfmeEntryWS(const BfmeEntryWS &other)
		: m_bfmeText(other.m_bfmeText),
		  m_bfmeA(other.m_bfmeA),
		  m_bfmeB(other.m_bfmeB),
		  m_bfmeC(other.m_bfmeC)
	{
	}

	AsciiString m_bfmeText;					// +0x00
	int m_bfmeA;						// +0x04
	bool m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

// View of the language object this TU reads its override from.  The global
// itself is retail's TheGlobalLanguageData, a GlobalLanguage* (0x012F1484);
// that class is declared by Common/System/game_engine_subsystems.h, so this is
// only the layout of the one member read here, reached through a cast.
class BfmeGlobalWS
{
public:
	char m_bfmePad000[0x118];				// +0x000
	BfmeEntryWS m_bfmeOverride;				// +0x118
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;			// retail 0x012F1484

class Gen_0043FD60
{
public:
	BfmeEntryWS bfmeEntryWS(void) const;

	char m_bfmePad000[0x7F4];				// +0x000
	BfmeEntryWS m_bfmeSlot;					// +0x7F4
};

// ?bfmeEntryWS@Gen_0043FD60@@QBE?AUBfmeEntryWS@@XZ
BfmeEntryWS Gen_0043FD60::bfmeEntryWS(void) const
{
	BfmeEntryWS entry(m_bfmeSlot);

	const BfmeEntryWS *override = &reinterpret_cast<BfmeGlobalWS *>( TheGlobalLanguageData )->m_bfmeOverride;

	const BfmeBufferWS *buffer = *reinterpret_cast<BfmeBufferWS *const *>(&override->m_bfmeText);
	if (buffer != 0 && buffer->m_bfmeLength != 0)
	{
		static_cast<StringBase<char> &>(entry.m_bfmeText).set(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
