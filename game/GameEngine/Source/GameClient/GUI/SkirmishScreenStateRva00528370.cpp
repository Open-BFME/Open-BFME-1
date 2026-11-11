// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// SkirmishScreenState::rva00528370, retail 0x00528370, 296 bytes (ret 4,
// INT3 padding after). The name is the one SkirmishScreenState::bfmeFlush11
// (0x0052A940+0xE5) already calls through the ILT at 0x000430A9; the receiver
// is the same object MpGameSetup::bfmeSetMap (0x00527130) is called on.
//
// Select the list-box row whose map name equals mapName (case-insensitive,
// the _memicmp import at 0x01359310 inlined as compareNoCase); with no such
// row fall back to the first row and its map, or with an empty list clear the
// selection and set the empty map.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

class GameWindow;

int GadgetListBoxGetNumEntries(GameWindow *listbox);
void GadgetListBoxSetSelected(GameWindow *listbox, int selectIndex);
void GadgetListBoxSetSelected(GameWindow *listbox, const int *selectList, int selectCount);

static inline int CompareNoCase00528370(const AsciiString &self, const AsciiString &other)
{
	int thatLen = other.StringBase<char>::getLength();
	const char *thatData = other.str();
	int thisLen = self.StringBase<char>::getLength();
	const char *thisData = self.str();
	int c = _memicmp(thisData, thatData, thisLen < thatLen ? thisLen : thatLen);
	return c ? c : thisLen - thatLen;
}

// ?bfmeSetMap@MpGameSetup@@QAEXABVAsciiString@@@Z at 0x00527130 is called
// with this object in ECX: both views share the +4 owner / +8 game layout.
class MpGameSetup
{
public:
	void bfmeSetMap(const AsciiString &mapName);
};

class SkirmishScreenState : public MpGameSetup
{
public:
	void rva00528370(const AsciiString &mapName);

private:
	unsigned char m_unmodelled00[0x108];
	GameWindow *m_window108;
	AsciiString *m_member10c;	// first word of the +0x10C member: row map names
};

void SkirmishScreenState::rva00528370(const AsciiString &mapName)
{
	int count = GadgetListBoxGetNumEntries(m_window108);
	int selected = -1;
	for (int i = 0; i < count; ++i)
	{
		if (CompareNoCase00528370(mapName, m_member10c[i]) == 0)
		{
			selected = i;
			break;
		}
	}

	if (selected >= 0)
	{
		GadgetListBoxSetSelected(m_window108, selected);
		return;
	}

	if (GadgetListBoxGetNumEntries(m_window108) == 0)
	{
		GadgetListBoxSetSelected(m_window108, &selected, -1);
		bfmeSetMap(AsciiString::TheEmptyString);
	}
	else
	{
		GadgetListBoxSetSelected(m_window108, 0);
		bfmeSetMap(m_member10c[0]);
	}
}
