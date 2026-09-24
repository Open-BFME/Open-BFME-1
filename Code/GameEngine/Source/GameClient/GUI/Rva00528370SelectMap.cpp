// cl: /O2 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x00528370 (296 bytes, thiscall, ret 4), called through ILT
// 0x000430A9 from the still-dumped 0x0052A940.
//
// Select a map in the setup screen's map list: find mapName among the list's
// names with a case-insensitive AsciiString comparison (inline, through the
// MSVCR71 _memicmp import) and select that row; otherwise select row 0 and
// apply its name, or clear the selection and apply AsciiString::TheEmptyString
// when the list is empty. The receiver's +0x108 list is the one the
// literal-named gadget callback 0x00525AB0 binds to "MapList", and it applies
// the map through the matched MpGameSetup::bfmeSetMap on itself; the class
// keeps the address token because the owning class is not proven.

#include "string_base.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	int compareNoCase(const AsciiString &s) const
	{
		const StringBase<char> *that = (const StringBase<char> *)&s;
		int thatLen = that->m_data ? that->m_data->length : 0;
		const char *thatData = that->m_data ? that->m_data->data : "";
		int thisLen = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = _memicmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
};

class GameWindow;

int GadgetListBoxGetNumEntries(GameWindow *listbox);
void GadgetListBoxSetSelected(GameWindow *listbox, int selectIndex);
void GadgetListBoxSetSelected(GameWindow *listbox, const int *selectList, int selectCount);

class MpGameSetup
{
public:
	void bfmeSetMap(const AsciiString &mapName);
};

// +0x10C points at the first of the list's map names, one per row.
class Rva00528370Setup
{
public:
	void selectMap(const AsciiString &mapName);

private:
	unsigned char m_unmodelled00[0x108];
	GameWindow *m_mapList;
	AsciiString *m_mapNames;
};

// ?selectMap@Rva00528370Setup@@QAEXABVAsciiString@@@Z
void Rva00528370Setup::selectMap(const AsciiString &mapName)
{
	int count = GadgetListBoxGetNumEntries(m_mapList);
	int selected = -1;
	for (int i = 0; i < count; ++i)
	{
		if (mapName.compareNoCase(m_mapNames[i]) == 0)
		{
			selected = i;
			break;
		}
	}

	if (selected >= 0)
	{
		GadgetListBoxSetSelected(m_mapList, selected);
		return;
	}

	if (GadgetListBoxGetNumEntries(m_mapList) == 0)
	{
		GadgetListBoxSetSelected(m_mapList, &selected, -1);
		((MpGameSetup *)this)->bfmeSetMap(AsciiString::TheEmptyString);
	}
	else
	{
		GadgetListBoxSetSelected(m_mapList, 0);
		((MpGameSetup *)this)->bfmeSetMap(m_mapNames[0]);
	}
}
