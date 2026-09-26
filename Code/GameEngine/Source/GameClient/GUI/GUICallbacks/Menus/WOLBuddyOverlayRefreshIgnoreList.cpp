// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// refreshIgnoreList retail 0x004EF6D0 539 bytes; ZH twin in WOLBuddyOverlay.cpp.
// WOLBuddyOverlaySystem (0x004EFAF0) calls it through ILT when the ignore tab
// is selected. GameSpyInfo vtable 0x011188D0 slot 76 returns this+0x6D4 by
// address and slot 78 is returnIgnoreList (0x00635640), in ZH declaration order.

#define _STLP_USE_STATIC_LIB 1
#include <map>
#include <set>

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;

// Retail calls StringBase<T>'s copy ctor and releaseBuffer directly, so the
// string members this body needs are inline forwarders here.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

class GameWindow;

typedef std::map<Int, AsciiString> SavedIgnoreMap;
typedef std::set<AsciiString> IgnoreList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfo
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void slot_0bc();
	virtual void slot_0c0();
	virtual void slot_0c4();
	virtual void slot_0c8();
	virtual void slot_0cc();
	virtual void slot_0d0();
	virtual void slot_0d4();
	virtual void slot_0d8();
	virtual void slot_0dc();
	virtual void slot_0e0();
	virtual void slot_0e4();
	virtual void slot_0e8();
	virtual void slot_0ec();
	virtual void slot_0f0();
	virtual void slot_0f4();
	virtual void slot_0f8();
	virtual void slot_0fc();
	virtual void slot_100();
	virtual void slot_104();
	virtual void slot_108();
	virtual void slot_10c();
	virtual void slot_110();
	virtual void slot_114();
	virtual void slot_118();
	virtual void slot_11c();
	virtual void slot_120();
	virtual void slot_124();
	virtual void slot_128();
	virtual void slot_12c();
	virtual SavedIgnoreMap &returnSavedIgnoreList(void);
	virtual void loadSavedIgnoreList(void);
	virtual IgnoreList returnIgnoreList(void);
};

extern GameSpyInfo *TheGameSpyInfo;
extern GameWindow *listboxIgnore;

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Color color, Int row, Int column = -1, bool overwrite = true);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column = 0);

// ?refreshIgnoreList@@YAXXZ
void refreshIgnoreList( void )
{
	SavedIgnoreMap tempMap;
	tempMap = TheGameSpyInfo->returnSavedIgnoreList();
	SavedIgnoreMap::iterator it = tempMap.begin();
	GadgetListBoxReset(listboxIgnore);
	while(it != tempMap.end())
	{
		UnicodeString name;
		name.translate(it->second);
		Int pos = GadgetListBoxAddEntryText(listboxIgnore, name, GameMakeColor(255,100,100,255),-1);
		GadgetListBoxSetItemData(listboxIgnore, (void *)it->first,pos );
		++it;
	}
	IgnoreList tempList;
	tempList = TheGameSpyInfo->returnIgnoreList();
	IgnoreList::iterator iListIt = tempList.begin();
	while( iListIt != tempList.end())
	{
		AsciiString aName = *iListIt;
		UnicodeString name;
		name.translate(aName);
		Int pos = GadgetListBoxAddEntryText(listboxIgnore, name, GameMakeColor(255,100,100,255),-1);
		GadgetListBoxSetItemData(listboxIgnore, 0,pos );
		++iListIt;
	}
}
