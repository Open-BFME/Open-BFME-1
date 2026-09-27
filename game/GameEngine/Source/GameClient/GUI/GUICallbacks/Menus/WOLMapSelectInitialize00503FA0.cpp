// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME body at RVA 00503FA0, 1100 bytes.
// Derived from ZH WOLMapSelectMenu.cpp; Copyright 2025 Electronic Arts Inc.
// GPL-3.0-or-later.
// Window-name literals and control flow identify the ZH map-select init
// operation. The address stays in the name because the callback signature
// is not independently proven. Retail has no ZH staging-room stats guards.
// Complete retail end: ret at 005043EB. Map metadata is read only at the
// witnessed byte offset +26; name_oracle has no member name for that offset.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const {
  return m_data ? m_data->data : "";
}
template <>
inline const unsigned short *StringBase<unsigned short>::str() const {
  return m_data ? m_data->data : (const unsigned short *)L"";
}

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(
          *(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString() {
  ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->set(*(const StringBase<unsigned short> *)&s);
  return *this;
}

// The legacy window header embeds its own UnicodeString in unused inline
// accessors. Give that header-only view a distinct name while preserving the
// canonical native strings used by this body.
#undef UNICODESTRING_H
#define UnicodeString Rva00503FA0HeaderUnicodeString
#include "GameClient/GameWindow.h"

#include "PreRTS.h"
#undef UnicodeString
#include "Common/CustomMatchPreferences.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameNetwork/GUIUtil.h"

// Native callees; no receiver storage is accessed through these declarations.
class MapMetaData;
class MapCache { public: const MapMetaData *findMap(AsciiString); void updateCache(); };
extern MapCache *TheMapCache;
class GameInfo { public: AsciiString getMap() const; };
extern GameInfo *TheGameSpyGame;
// ILT 00029CEE -> 00457090 takes four cdecl stack arguments. Its
// final argument is a pointer to a caller-owned AsciiString temporary,
// which the caller destroys after return (unlike the ZH by-value API).
extern void j_00029cee();
inline void rva00457090PopulateMapList(GameWindow *w, bool system, bool multiplayer, const AsciiString &map) {
 ((void (__cdecl *)(GameWindow*,bool,bool,const AsciiString&))j_00029cee)(w,system,multiplayer,map);
}
const int MAX_SLOTS = 8;
static NameKeyType buttonBack = NAMEKEY_INVALID;
static NameKeyType buttonOK = NAMEKEY_INVALID;
static NameKeyType listboxMap = NAMEKEY_INVALID;
static GameWindow *parent = NULL;
static Bool raiseMessageBoxes = FALSE;
static GameWindow *winMapPreview = NULL;
static NameKeyType winMapPreviewID = NAMEKEY_INVALID;

static NameKeyType radioButtonSystemMapsID = NAMEKEY_INVALID;
static NameKeyType radioButtonUserMapsID = NAMEKEY_INVALID;

extern WindowLayout *WOLMapSelectLayout;			///< Map selection overlay
static GameWindow *mapList = NULL;

static GameWindow *buttonMapStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };
static NameKeyType buttonMapStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static GameWindow *winMapWindow = NULL;

static const char *layoutFilename = "GameSpyGameOptionsMenu.wnd";
static const char *parentName = "GameSpyGameOptionsMenuParent";
static const char *gadgetsToHide[] =
{
	"MapWindow",
	//"StaticTextGameName",
	"StaticTextTeam",
	"StaticTextFaction",
	"StaticTextColor",
	"TextEntryMapDisplay",
	"ButtonSelectMap",
	"ButtonStart",
	"StaticTextMapPreview",
	
	NULL // keep this last
};
static const char *perPlayerGadgetsToHide[] =
{
	"ComboBoxTeam",
	"ComboBoxColor",
	"ComboBoxPlayerTemplate",
	//"ButtonStartPosition",
	NULL // keep this last
};
void positionStartSpots( AsciiString mapName, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow);

static void showGameSpyGameOptionsUnderlyingGUIElements( Bool show )
{
	ShowUnderlyingGUIElements( show, layoutFilename, parentName, gadgetsToHide, perPlayerGadgetsToHide );
	GameWindow *win	= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey("GameSpyGameOptionsMenu.wnd:ButtonBack") );
	if(win)
		win->winEnable( show );
}

void Rva00503FA0InitializeMapSelectMenu()
{

	// set keyboard focus to main parent
	AsciiString parentName( "WOLMapSelectMenu.wnd:WOLMapSelectMenuParent" );
	NameKeyType parentID = TheNameKeyGenerator->nameToKey( parentName );
	parent = TheWindowManager->winGetWindowFromId( NULL, parentID );

	TheWindowManager->winSetFocus( parent );

	CustomMatchPreferences pref;
	Bool usesSystemMapDir = pref.usesSystemMapDir();
	winMapPreviewID = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:WinMapPreview") );
	winMapPreview = TheWindowManager->winGetWindowFromId(parent, winMapPreviewID);

	const MapMetaData *mmd = TheMapCache->findMap(TheGameSpyGame->getMap());
	if (mmd)
	{
		usesSystemMapDir = *(const bool *)((const char *)mmd + 0x26);
	}

	buttonBack = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:ButtonBack") );
	buttonOK = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:ButtonOK") );
	listboxMap = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:ListboxMap") );
	radioButtonSystemMapsID = TheNameKeyGenerator->nameToKey( "WOLMapSelectMenu.wnd:RadioButtonSystemMaps" );
	radioButtonUserMapsID = TheNameKeyGenerator->nameToKey( "WOLMapSelectMenu.wnd:RadioButtonUserMaps" );
	winMapWindow = TheWindowManager->winGetWindowFromId( parent, listboxMap );

	GameWindow *radioButtonSystemMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonSystemMapsID );
	GameWindow *radioButtonUserMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonUserMapsID );
	if (usesSystemMapDir)
		GadgetRadioSetSelection( radioButtonSystemMaps, FALSE );
	else
		GadgetRadioSetSelection( radioButtonUserMaps, FALSE );
	
	AsciiString tmpString;
	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		tmpString.format("WOLMapSelectMenu.wnd:ButtonMapStartPosition%d", i);
		buttonMapStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonMapStartPosition[i] = TheWindowManager->winGetWindowFromId( winMapPreview, buttonMapStartPositionID[i] );
		DEBUG_ASSERTCRASH(buttonMapStartPosition[i], ("Could not find the ButtonMapStartPosition[%d]",i ));
		buttonMapStartPosition[i]->winHide(TRUE);
		buttonMapStartPosition[i]->winEnable(FALSE);
	}

	raiseMessageBoxes = TRUE;
	showGameSpyGameOptionsUnderlyingGUIElements( FALSE );

	// get the listbox window
	AsciiString listString( "WOLMapSelectMenu.wnd:ListboxMap" );
	NameKeyType mapListID = TheNameKeyGenerator->nameToKey( listString );
	mapList = TheWindowManager->winGetWindowFromId( parent, mapListID );
	if( mapList )
	{
		if (TheMapCache)
			TheMapCache->updateCache();
		rva00457090PopulateMapList( mapList, usesSystemMapDir, TRUE, TheGameSpyGame->getMap() );
	}

}  