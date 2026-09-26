// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native WOLBuddyOverlayInit, RVA 004EC6E0, 1263 bytes.
// Reconstructed from the banked canonical Zero Hour body (Copyright 2025
// Electronic Arts; GPL-3.0-or-later). The retail FunctionLexicon entry at
// VA 012A9A20 pairs "WOLBuddyOverlayInit" with ILT 00016C89 -> RVA 004EC6E0.
// Canonical strings and BFME window-manager slots reproduce all 135 relocs.
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}
template <> inline const unsigned short *StringBase<unsigned short>::str() const
{
	return m_data ? m_data->data : (const unsigned short *)L"";
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}
inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

#define __PLACEMENT_VEC_NEW_INLINE
#undef UNICODESTRING_H
#define UnicodeString Rva004ED400HeaderUnicodeString
#include "GameClient/GameWindow.h"
#include "PreRTS.h"
#undef UnicodeString
#include <list>
#include <map>
#include <string>
#include <time.h>

#include "Common/NameKeyGenerator.h"
static NameKeyType parentID;
static GameWindow *parent;
static NameKeyType buttonHideID;
static GameWindow *buttonHide;
static NameKeyType buttonAddBuddyID;
static GameWindow *buttonAddBuddy;
static NameKeyType buttonDeleteBuddyID;
static GameWindow *buttonDeleteBuddy;
static NameKeyType buttonAcceptBuddyID;
static GameWindow *buttonAcceptBuddy;
static NameKeyType buttonDenyBuddyID;
static GameWindow *buttonDenyBuddy;
static NameKeyType radioButtonBuddiesID;
static GameWindow *radioButtonBuddies;
static NameKeyType radioButtonIgnoreID;
static GameWindow *radioButtonIgnore;
static NameKeyType parentBuddiesID;
static GameWindow *parentBuddies;
static NameKeyType parentIgnoreID;
static GameWindow *parentIgnore;
static NameKeyType listboxIgnoreID;
static GameWindow *listboxIgnore;

static bool isOverlayActive;
const int BUDDY_WINDOW_BUDDIES = 0;
void InitBuddyControls(int);
void PopulateOldBuddyMessages();
void updateBuddyInfo();
void GadgetRadioSetSelection(GameWindow *, bool);
class BfmeVirtualHideLayout
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void hide(bool) = 0;
};
class Rva004EC6E0WindowManager
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual int winSetFocus(GameWindow *) = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *, int) = 0;
};
extern Rva004EC6E0WindowManager *TheWindowManager;
void WOLBuddyOverlayInit(WindowLayout *layout, void *userData)
{
	parentID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:BuddyMenuParent"));
	buttonHideID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ButtonHide"));
	buttonAddBuddyID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ButtonAdd"));
	buttonDeleteBuddyID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ButtonDelete"));
	buttonAcceptBuddyID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ButtonYes"));
	buttonDenyBuddyID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ButtonNo"));
	radioButtonBuddiesID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:RadioButtonBuddies"));
	radioButtonIgnoreID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:RadioButtonIgnore"));
	parentBuddiesID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:BuddiesParent"));
	parentIgnoreID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:IgnoreParent"));
	listboxIgnoreID = TheNameKeyGenerator->nameToKey(AsciiString("WOLBuddyOverlay.wnd:ListboxIgnore"));

	parent = TheWindowManager->winGetWindowFromId(NULL, parentID);
	buttonHide = TheWindowManager->winGetWindowFromId(parent, buttonHideID);
	buttonAddBuddy = TheWindowManager->winGetWindowFromId(parent, buttonAddBuddyID);
	buttonDeleteBuddy = TheWindowManager->winGetWindowFromId(parent, buttonDeleteBuddyID);
	buttonAcceptBuddy = TheWindowManager->winGetWindowFromId(parent, buttonAcceptBuddyID);
	buttonDenyBuddy = TheWindowManager->winGetWindowFromId(parent, buttonDenyBuddyID);
	radioButtonBuddies = TheWindowManager->winGetWindowFromId(parent, radioButtonBuddiesID);
	radioButtonIgnore = TheWindowManager->winGetWindowFromId(parent, radioButtonIgnoreID);
	parentBuddies = TheWindowManager->winGetWindowFromId(parent, parentBuddiesID);
	parentIgnore = TheWindowManager->winGetWindowFromId(parent, parentIgnoreID);
	listboxIgnore = TheWindowManager->winGetWindowFromId(parent, listboxIgnoreID);

	InitBuddyControls(BUDDY_WINDOW_BUDDIES);
	GadgetRadioSetSelection(radioButtonBuddies, FALSE);
	parentBuddies->winHide(FALSE);
	parentIgnore->winHide(TRUE);
	PopulateOldBuddyMessages();
	((BfmeVirtualHideLayout *)layout)->hide(FALSE);
	TheWindowManager->winSetFocus(parent);
	isOverlayActive = true;
	updateBuddyInfo();
} // WOLBuddyOverlayInit
