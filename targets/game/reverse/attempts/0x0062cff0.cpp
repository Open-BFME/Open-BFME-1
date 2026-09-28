// ?gameTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.974 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Copyright 2025 Electronic Arts Inc. SPDX-License-Identifier: GPL-3.0-or-later
// BFME gameTooltip 0062CFF0..0062D668 (1656 B). Saved whole-body reconstruction.
// Source twin: GeneralsMD LobbyUtils.cpp; retail tooltip literals and complete call order.
// Retail-derived views: GameSpyInfoInterface lookup slot 0x9c; room password 0x428;
// CRC fields 0x430/434/438; ladder port 0x450; slot wins/losses 0x58/5c.
// String payload +8 and forwarding copy ctor are native, unlike the previous ZH bank.
// reverseFind below is independently exact at 00072C40 (56 B); making it visible
// removes two otherwise-spurious EH state stores in the caller.
// Residue: 2 leading NULL-action EH states absent, then register scheduling.
// Canonical unicode_string.h currently has no inherited StringBase model; this
// native forwarding view is confined to banked evidence, not a shared-header edit.
#include <wchar.h>
#include "ascii_string.h"

template<> inline const char *StringBase<char>::str() const {return m_data ? m_data->data : "";}
template<> inline const unsigned short *StringBase<unsigned short>::str() const {return m_data ? m_data->data : (const unsigned short*)L"";}
template<> __declspec(noinline) const char *StringBase<char>::reverseFind(char c) const {
const char *start=m_data ? m_data->data : "";
const char *p=start+(m_data ? m_data->length : 0);
while(p!=start){--p;if(*p==c)return p;}return 0;
}
template<> inline StringBase<char>::~StringBase() {releaseBuffer();}
template<> inline StringBase<unsigned short>::StringBase(){m_data=0;}
template<> inline StringBase<unsigned short>::~StringBase(){releaseBuffer();}
class UnicodeString : public StringBase<unsigned short> {
public:
 static UnicodeString TheEmptyString;
 UnicodeString() {}
 UnicodeString(const UnicodeString&s):StringBase<unsigned short>(s){}
 ~UnicodeString(){}
 UnicodeString &operator=(const UnicodeString&s){set(s);return *this;}
 const wchar_t *str()const{return (const wchar_t*)StringBase<unsigned short>::str();}
 void __cdecl format(UnicodeString,...);
 void translate(const AsciiString&);
};
static inline int compareWide(const UnicodeString&s,const wchar_t*t){return ((const StringBase<unsigned short>*)&s)->compare((const unsigned short*)t);}
static inline void setWide(UnicodeString&s,const wchar_t*t){((StringBase<unsigned short>*)&s)->set((const unsigned short*)t);}
// StringBase<unsigned short>::concat(const StringBase&) is 00086500, via 00018AA2.

static inline void concat(UnicodeString&s,const UnicodeString&t){((StringBase<unsigned short>*)&s)->concat(*(const StringBase<unsigned short>*)&t);}
static inline void concatChar(UnicodeString&s,wchar_t c){unsigned int tmp=c;((StringBase<unsigned short>*)&s)->concat((const unsigned short*)&tmp,1);}
typedef int Int; typedef unsigned int UnsignedInt; typedef bool Bool; typedef wchar_t WideChar;
#define NULL 0
#define MAX_SLOTS 8
#define LOLONGTOSHORT(x) ((x)&0xffff)
#define HILONGTOSHORT(x) ((x)>>16)
#define DEBUG_CRASH(x)
#define DEBUG_ASSERTCRASH(x,y)
enum {COLUMN_PING=6,COLUMN_NUMPLAYERS=3,COLUMN_PASSWORD=4};
enum SlotState {SLOT_EASY_AI=2,SLOT_MED_AI=3,SLOT_BRUTAL_AI=4};
class GameWindow; class WinInstanceData; struct RGBColor;
int GadgetListBoxGetEntryBasedOnXY(GameWindow*,int,int,int&,int&);
void *GadgetListBoxGetItemData(GameWindow*,int,int);
class Mouse {public: void setCursorTooltip(UnicodeString,int=-1,const RGBColor * =0,float=1.0f);};
extern Mouse *TheMouse;

class GameTextInterface {public:
virtual void slot_00();
virtual void slot_04();
virtual void slot_08();
virtual void slot_0c();
virtual void slot_10();
virtual void slot_14();
virtual void slot_18();
virtual void slot_1c();
virtual void slot_20();
virtual void slot_24();
virtual UnicodeString fetch(const char*,bool * =0);
};
extern GameTextInterface *TheGameText;
class GameSlot {public:
char vptr[4];SlotState m_state;
Bool isHuman() const; Bool isAI()const; UnicodeString getName()const;
SlotState getState()const{return m_state;}
};
class GameSpyGameSlot : public GameSlot {public:
char field_08[0x58-8]; int m_wins,m_losses;
int getWins()const{return m_wins;} int getLosses()const{return m_losses;}
};
class GameInfo {public: AsciiString getMap()const;};
class GameSpyStagingRoom : public GameInfo {public:
char field_000[0x428];bool m_requiresPassword;char field_429[7];
unsigned m_exeCRC,m_iniCRC,m_bfme438;char field_43c[0x14];unsigned short m_ladderPort;
UnicodeString getGameName();AsciiString getLadderIP()const;
GameSpyGameSlot *getGameSpySlot(int);
};
class GameSpyInfoInterface {public:
virtual void slot_00();
virtual void slot_04();
virtual void slot_08();
virtual void slot_0c();
virtual void slot_10();
virtual void slot_14();
virtual void slot_18();
virtual void slot_1c();
virtual void slot_20();
virtual void slot_24();
virtual void slot_28();
virtual void slot_2c();
virtual void slot_30();
virtual void slot_34();
virtual void slot_38();
virtual void slot_3c();
virtual void slot_40();
virtual void slot_44();
virtual void slot_48();
virtual void slot_4c();
virtual void slot_50();
virtual void slot_54();
virtual void slot_58();
virtual void slot_5c();
virtual void slot_60();
virtual void slot_64();
virtual void slot_68();
virtual void slot_6c();
virtual void slot_70();
virtual void slot_74();
virtual void slot_78();
virtual void slot_7c();
virtual void slot_80();
virtual void slot_84();
virtual void slot_88();
virtual void slot_8c();
virtual void slot_90();
virtual void slot_94();
virtual void slot_98();
virtual GameSpyStagingRoom *findStagingRoomByID(int);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class MapMetaData {public:UnicodeString m_displayName;};
class MapCache {public: const MapMetaData *findMap(AsciiString);};
extern MapCache *TheMapCache;
class LadderInfo {public:UnicodeString name;};
class LadderList {public: const LadderInfo *findLadder(const AsciiString&,unsigned short);};
extern LadderList *TheLadderList;
class GlobalData;extern GlobalData *TheGlobalData;
int Rva0009B4B0(int,int);
void gameTooltip(GameWindow *window,
													WinInstanceData *instData,
													UnsignedInt mouse)
{
	Int x, y, row, col;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, col);

	if (row == -1 || col == -1)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString);//TheGameText->fetch("TOOLTIP:GamesBeingFormed") );
		return;
	}

	Int gameID = (Int)GadgetListBoxGetItemData(window, row, 0);
	GameSpyStagingRoom *room = TheGameSpyInfo->findStagingRoomByID(gameID);
	if (!room)
	{
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:UnknownGame") );
		return;
	}

	if (col == COLUMN_PING)
	{
#if 0 //def DEBUG_LOGGING
		UnicodeString s;
		s.format(L"Ping is %d ms (cutoffs are %d ms and %d ms\n%hs local pings\n%hs remote pings",
			room->getPingAsInt(), TheGameSpyConfig->getPingCutoffGood(), TheGameSpyConfig->getPingCutoffBad(),
			TheGameSpyInfo->getPingString().str(), room->getPingString().str()
		);
		TheMouse->setCursorTooltip( s, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
#else
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:PingInfo"), 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
#endif
		return;
	}
	if (col == COLUMN_NUMPLAYERS)
	{
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:NumberOfPlayers"), 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
		return;
	}
	if (col == COLUMN_PASSWORD)
	{
		if (room->m_requiresPassword)
		{
			UnicodeString checkTooltip =TheGameText->fetch("TOOTIP:Password");
			if(!compareWide(checkTooltip,L"Password required to joing game"))
				setWide(checkTooltip,L"Password required to join game");
			TheMouse->setCursorTooltip( checkTooltip, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
		}
		else
			TheMouse->setCursorTooltip( UnicodeString::TheEmptyString );
		return;
	}
	// BFME has no use-stats tooltip column.

	UnicodeString tooltip;

	UnicodeString mapName;
	const MapMetaData *md = TheMapCache->findMap(room->getMap());
	if (md)
	{
		mapName = md->m_displayName;
	}
	else
	{
		const char *start = room->getMap().reverseFind('\\');
		if (start)
		{
			++start;
		}
		else
		{
			start = room->getMap().str();
		}
		mapName.translate( start );
	}
	UnicodeString tmp;
	tooltip.format(TheGameText->fetch("TOOLTIP:GameInfoGameName"), room->getGameName().str());
	const GameSpyStagingRoom *bfmeRoom = room;
	if (bfmeRoom->m_ladderPort != 0)
	{
		const LadderInfo *linfo = TheLadderList->findLadder(bfmeRoom->getLadderIP(), bfmeRoom->m_ladderPort);
		if (linfo)
		{
			tmp.format(TheGameText->fetch("TOOLTIP:GameInfoLadderName"), linfo->name.str());
			concat(tooltip,tmp);
		}
	}
	// BFME GlobalData words: +0xBD0 feeds the CRC hook, +0xBC8 and +0xBD4 are
	// compared directly.
	
	const UnsignedInt exeCRC = bfmeRoom->m_exeCRC;
	if (exeCRC != (UnsignedInt)Rva0009B4B0(((const UnsignedInt *)TheGlobalData)[0xbd0/4], ((const UnsignedInt *)TheGlobalData)[0xbd0/4]) ||
			bfmeRoom->m_iniCRC != ((const UnsignedInt *)TheGlobalData)[0xbc8/4] ||
			bfmeRoom->m_bfme438 != ((const UnsignedInt *)TheGlobalData)[0xbd4/4])
	{
		tmp.format(TheGameText->fetch("TOOLTIP:InvalidGameVersion"), mapName.str());
		concat(tooltip,tmp);
	}
	tmp.format(TheGameText->fetch("TOOLTIP:GameInfoMap"), mapName.str());
	concat(tooltip,tmp);

	AsciiString aPlayer;
	UnicodeString player;
	Int numPlayers = 0;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = room->getGameSpySlot(i);
		if (i == 0 && (!slot || !slot->isHuman()))
		{
			DEBUG_CRASH(("About to tooltip a non-hosted game!\n"));
		}
		if (slot && slot->isHuman())
		{
			tmp.format(TheGameText->fetch("TOOLTIP:GameInfoPlayer"), slot->getName().str(), slot->getWins(), slot->getLosses());
			concat(tooltip,tmp);
			++numPlayers;
		}
		else if (slot && slot->isAI())
		{
			++numPlayers;
			switch(slot->getState())
			{
			case SLOT_EASY_AI:
				concatChar(tooltip, L'\n');
				concat(tooltip,TheGameText->fetch("GUI:EasyAI"));
				break;
			case SLOT_MED_AI:
				concatChar(tooltip, L'\n');
				concat(tooltip,TheGameText->fetch("GUI:MediumAI"));
				break;
			case SLOT_BRUTAL_AI:
				concatChar(tooltip, L'\n');
				concat(tooltip,TheGameText->fetch("GUI:HardAI"));
				break;
			}
		}
	}
	DEBUG_ASSERTCRASH(numPlayers, ("Tooltipping a 0-player game!\n"));

	TheMouse->setCursorTooltip( tooltip, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
}
