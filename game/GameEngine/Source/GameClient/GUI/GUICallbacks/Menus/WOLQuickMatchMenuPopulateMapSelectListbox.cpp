// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// populateQuickMatchMapSelectListbox, retail 0x00507F70 684 bytes; ZH twin in
// WOLQuickMatchMenu.cpp.  BFME's APT port calls the extracted helper with the
// surrounding BfmeAptScreenQuickMatchMenu in ECX (retail `mov edi,ecx` and
// `ret 4`): both callers, the init-gadgets body 0x005091F0 and
// WOLQuickMatchMenuSystem 0x0050A470, load the menu owner into ECX and push the
// QuickMatchPreferences.  The +0x23C/+0x244/+0x284 windows are the
// ComboBoxNumPlayers/ComboBoxLadder/ListBoxMapSelect members the matched menu
// constructor 0x00505830 binds by name key.

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include <list>

typedef int Int;
typedef int Color;
typedef bool Bool;

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

inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
	return *this;
}

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
// Image+0x24 m_imageSize is the layout witness (name_oracle).
struct ICoord2D
{
	Int x;
	Int y;
};

class Image
{
public:
	Int getImageWidth() const { return m_imageSize.x; }

private:
	char m_unmodelled[0x24];
	ICoord2D m_imageSize;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
class LadderInfo
{
public:
	char m_unmodelled[0xc];
	Int playersPerTeam;
	char m_unmodelled10[0x8];
	Bool randomMaps;
	char m_unmodelled19[0x3];
	std::list<AsciiString> validMaps;
};

class LadderList
{
public:
	const LadderInfo *findLadderByIndex(Int index);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapMetaData
{
public:
	UnicodeString m_displayName;
	char m_unmodelled04[0x1c];
	Int m_numPlayers;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GSConfig.h
class GameSpyConfigInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual std::list<AsciiString> getQMMaps(void) = 0;
};

class QuickMatchPreferences
{
public:
	Bool isMapSelected(const AsciiString &val);
};

class BfmeAptScreenQuickMatchMenu
{
public:
	void populateQuickMatchMapSelectListbox(QuickMatchPreferences &pref);

private:
	char m_unmodelled[0x23c];
	GameWindow *m_numPlayers;
	char m_unmodelled240[0x4];
	GameWindow *m_ladder;
	char m_unmodelled248[0x3c];
	GameWindow *m_mapSelect;
};

extern GameSpyConfigInterface *TheGameSpyConfig;
extern LadderList *TheLadderList;
extern MapCache *TheMapCache;

// BFME inserted two entries ahead of ZH's GSCOLOR_MAP_SELECTED (23) and
// GSCOLOR_MAP_UNSELECTED (24); retail indexes 25 and 26.
extern Color GameSpyColor[];

// ZH's file statics; retail 0x012F480C/0x012F4810 are stored by the init
// body 0x005091F0 from findImageByName("CustomMatch_selected") and
// ("CustomMatch_deselected").
extern const Image *selectedImage;
extern const Image *unselectedImage;

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, Int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);
void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxGetColumnWidth(GameWindow *listbox, Int column);
Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, Int row, Int column, Int hight, Int width, Bool overwrite = true, Color color = -1);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Color color, Int row, Int column = -1, Bool overwrite = true);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column = 0);

template <class T> inline const T &qmMin(const T &a, const T &b)
{
	return a < b ? a : b;
}

void BfmeAptScreenQuickMatchMenu::populateQuickMatchMapSelectListbox(QuickMatchPreferences &pref)
{
	std::list<AsciiString> maps = TheGameSpyConfig->getQMMaps();

	Int index;
	Int selected;
	GadgetComboBoxGetSelectedPos(m_ladder, &selected);
	index = (Int)GadgetComboBoxGetItemData(m_ladder, selected);
	const LadderInfo *li = TheLadderList->findLadderByIndex(index);

	Int numPlayers = 0;
	if (li)
	{
		numPlayers = li->playersPerTeam * 2;
		maps = li->validMaps;
	}
	else
	{
		GadgetComboBoxGetSelectedPos(m_numPlayers, &selected);
		if (selected < 0)
			selected = 0;
		numPlayers = (selected + 1) * 2;
	}

	GadgetListBoxReset(m_mapSelect);
	for (std::list<AsciiString>::const_iterator it = maps.begin(); it != maps.end(); ++it)
	{
		AsciiString theMap = *it;
		const MapMetaData *md = TheMapCache->findMap(theMap);
		if (md && md->m_numPlayers >= numPlayers)
		{
			UnicodeString displayName;
			displayName = md->m_displayName;
			Bool isSelected = pref.isMapSelected(theMap);
			if (li && li->randomMaps)
				isSelected = true;
			Int width = 10;
			Int height = 10;
			const Image *img = (isSelected) ? selectedImage : unselectedImage;
			if (img)
			{
				width = qmMin(GadgetListBoxGetColumnWidth(m_mapSelect, 0), img->getImageWidth());
				height = width;
			}
			Int index = GadgetListBoxAddEntryImage(m_mapSelect, img, -1, 0, height, width);
			GadgetListBoxAddEntryText(m_mapSelect, displayName, GameSpyColor[(isSelected) ? 25 : 26], index, 1);
			GadgetListBoxSetItemData(m_mapSelect, (void *)isSelected, index);
			GadgetListBoxSetItemData(m_mapSelect, (void *)md, index, 1);
		}
	}
}
