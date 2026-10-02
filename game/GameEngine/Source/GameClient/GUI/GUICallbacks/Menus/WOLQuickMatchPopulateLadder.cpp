// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Native BFME body at RVA 00508C80, 1063 bytes.
// Derived from ZH WOLQuickMatchMenu.cpp; Copyright 2025 Electronic Arts Inc.
// GPL-3.0-or-later.
// Established name from PopulateQMLadderComboBox (005091D0) and the
// matched quick-match initializer (005091F0). Receiver fields +23c/+244
// agree with that initializer. Complete retail end: ret at 005090A6.
// name_oracle has no witnessed layout for BfmeQuickMatchLadderPanel.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

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
#define UnicodeString Rva00508C80HeaderUnicodeString
#include "GameClient/GameWindow.h"

#include "PreRTS.h"
#undef UnicodeString
#include "Common/QuickmatchPreferences.h"
#include "PreRTS.h"

#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/Image.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
const int GSCOLOR_MAP_SELECTED = 25;
const int GSCOLOR_MAP_UNSELECTED = 26;
#include "GameNetwork/GameSpyOverlay.h"

#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/Shell.h"
#include "Common/LadderPreferences.h"

// ZH PopulateQMLadderComboBox with native BFME receiver fields.
// Slot +70 returns the local profile ID, as consumed by loadProfile below.
// Established caller name retained; fields checked against 00508C80 loads.
class BfmeQuickMatchLadderPanel {
public:
 void populateLadderList();
 const LadderInfo *rva00508C80LadderInfo() { int selected; GadgetComboBoxGetSelectedPos(m_rva244, &selected); return TheLadderList->findLadderByIndex((int)GadgetComboBoxGetItemData(m_rva244, selected)); }
 char m_rva000[0x23c];
 GameWindow *m_rva23c;
 int m_rva240;
 GameWindow *m_rva244;
};
class GameSpyInfo {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual int getLocalProfileID();
};
extern GameSpyInfo *TheGameSpyInfo;
extern int GameSpyColor[];
static bool isPopulatingLadderBox = false;
// Retail validity call: ECX is LadderInfo, no stack arguments, bool in AL.
extern void j_0001ccba();
// Retail side-population call: menu receiver plus side and ladder pointer.
extern void j_00035701();
class Rva0062A7D0Owner { public: bool method(); };
inline bool rva0062A7D0Valid(const LadderInfo *p) {
 typedef bool (Rva0062A7D0Owner::*Method)();
 union { void (*raw)(); Method member; } f;
 f.raw=j_0001ccba;
 return (((Rva0062A7D0Owner*)p)->*f.member)();
}
class Rva005082D0Owner {};
typedef void (Rva005082D0Owner::*Rva005082D0Method)(int,const LadderInfo*);
inline Rva005082D0Method rva005082D0Method() {
 union { void (*raw)(); Rva005082D0Method member; } f;
 f.raw=j_00035701;
 return f.member;
}
void BfmeQuickMatchLadderPanel::populateLadderList()
{
	if (!m_rva244)
		return;

	isPopulatingLadderBox = true;

	QuickMatchPreferences pref;
	Int localProfile = TheGameSpyInfo->getLocalProfileID();

	Color specialColor = GameSpyColor[GSCOLOR_MAP_SELECTED];
	Color normalColor = GameSpyColor[GSCOLOR_MAP_UNSELECTED];
	Int index;
	GadgetComboBoxReset( m_rva244 );
	index = GadgetComboBoxAddEntry( m_rva244, TheGameText->fetch("GUI:NoLadder"), normalColor );
	GadgetComboBoxSetItemData( m_rva244, index, 0 );

	std::set<const LadderInfo *> usedLadders;

	Int selectedPos = 0;
	AsciiString lastLadderAddr = pref.getLastLadderAddr();
	UnsignedShort lastLadderPort = pref.getLastLadderPort();
	const LadderInfo *info = TheLadderList->findLadder( lastLadderAddr, lastLadderPort );
	if (info && rva0062A7D0Valid(info))
	{
		usedLadders.insert(info);
		index = GadgetComboBoxAddEntry( m_rva244, info->name, specialColor );
		GadgetComboBoxSetItemData( m_rva244, index, (void *)(info->index) );
		selectedPos = index;

		// we selected a ladder?  No game size choice for us...
		GadgetComboBoxSetSelectedPos(m_rva23c, info->playersPerTeam-1);
		m_rva23c->winEnable( FALSE );
	}
	else
	{
		m_rva23c->winEnable( TRUE );
	}

	LadderPreferences ladPref;
	ladPref.loadProfile( localProfile );
	const LadderPrefMap recentLadders = ladPref.getRecentLadders();
	for (LadderPrefMap::const_iterator cit = recentLadders.begin(); cit != recentLadders.end(); ++cit)
	{
		AsciiString addr = cit->second.address;
		UnsignedShort port = cit->second.port;
		if (addr.compare(lastLadderAddr) == 0 && port == lastLadderPort)
			continue;
		const LadderInfo *info = TheLadderList->findLadder( addr, port );
		if (info && rva0062A7D0Valid(info) && usedLadders.find(info) == usedLadders.end())
		{
			usedLadders.insert(info);
			index = GadgetComboBoxAddEntry( m_rva244, info->name, normalColor );
			GadgetComboBoxSetItemData( m_rva244, index, (void *)(info->index) );
		}
	}

	index = GadgetComboBoxAddEntry( m_rva244, TheGameText->fetch("GUI:ChooseLadder"), normalColor );
	GadgetComboBoxSetItemData( m_rva244, index, (void *)-1 );

	GadgetComboBoxSetSelectedPos( m_rva244, selectedPos );
	isPopulatingLadderBox = false;

	(((Rva005082D0Owner*)this)->*rva005082D0Method())(pref.getSide(),rva00508C80LadderInfo());
}

typedef std::map<int, unsigned int> Rva0062A7D0Wins;
class PSPlayerStats
{
public:
	int id;
	Rva0062A7D0Wins wins;
	char m_rva0010[0x1b4];
	~PSPlayerStats();
};
typedef char Rva0062A7D0StatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];
// The retail header names this type GameSpyPSMessageQueueInterface; no game
// header declares it, so the local stand-in carries that name to give the
// global below retail's exact mangling.
class GameSpyPSMessageQueueInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual PSPlayerStats findPlayerStatsByID(int id);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

bool Rva0062A7D0Owner::method()
{
	if (!this)
		goto failed;
	if (*(int *)((char *)this + 0x38) <= 0)
		goto failed;
	if (*(unsigned char *)((char *)this + 0x1a) == 0)
		goto failed;

	{
		PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
		int totalWins = 0;
		for (Rva0062A7D0Wins::const_iterator it = stats.wins.begin(); it != stats.wins.end(); ++it)
			totalWins += it->second;

		int maxWins = *(int *)((char *)this + 0x14);
		if (maxWins != 0 && maxWins < totalWins)
			goto failed;
		int minWins = *(int *)((char *)this + 0x10);
		if (minWins != 0 && minWins > totalWins)
			goto failed;
	}
	return true;

failed:
	return false;
}
