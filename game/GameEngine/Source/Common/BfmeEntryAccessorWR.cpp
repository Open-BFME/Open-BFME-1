// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the override-aware entry accessor at retail 0x0043FC50,
// 210 bytes.  Copies the member entry into a local, replaces its text from the
// global override when that override's buffer is non-empty, and returns the
// local by value.  One of four identical siblings.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Keep retail's direct word comparison; getLength() materializes an int.
struct BfmeBufferWR
{
	int m_bfmeRef;
	short m_bfmeLength;
};

struct BfmeEntryWR
{
	BfmeEntryWR(const BfmeEntryWR &other)
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
class BfmeGlobalWR
{
public:
	char m_bfmePad000[0x10C];				// +0x000
	BfmeEntryWR m_bfmeOverride;				// +0x10C
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;			// retail 0x012F1484

class Gen_0043FC50
{
public:
	BfmeEntryWR bfmeEntryWR(void) const;

	char m_bfmePad000[0x7E4];				// +0x000
	BfmeEntryWR m_bfmeSlot;					// +0x7E4
};

// ?bfmeEntryWR@Gen_0043FC50@@QBE?AUBfmeEntryWR@@XZ
BfmeEntryWR Gen_0043FC50::bfmeEntryWR(void) const
{
	BfmeEntryWR entry(m_bfmeSlot);

	const BfmeEntryWR *override = &reinterpret_cast<BfmeGlobalWR *>( TheGlobalLanguageData )->m_bfmeOverride;

	const BfmeBufferWR *buffer = *reinterpret_cast<BfmeBufferWR *const *>(&override->m_bfmeText);
	if (buffer != 0 && buffer->m_bfmeLength != 0)
	{
		static_cast<StringBase<char> &>(entry.m_bfmeText).set(override->m_bfmeText);

		entry.m_bfmeA = override->m_bfmeA;
		entry.m_bfmeB = override->m_bfmeB;
	}

	return entry;
}
