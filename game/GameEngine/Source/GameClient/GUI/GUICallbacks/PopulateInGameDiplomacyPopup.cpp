// BFME-layout-specific implementation of PopulateInGameDiplomacyPopup.
// cl: /O2 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringinline
// Retail 0x004C3800..0x004C3CB2 is 1203 bytes, not the 1194-address inventory.
// Matched Diplomacy update/system callers reach this body through ILT 0x8F4E.
// BFME uses the slot's +0x2C player key string and skips absent players;
// Network/Victory virtual calls use +0xAC/+0x2C respectively.
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef int Color;
enum NameKeyType {
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

enum { MAX_SLOTS = 8 };

inline Color GameMakeColor( unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha )
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

class Player;
struct BFMEGameSlotView
{
	unsigned char beforeMuted[0x0a];
	Bool muted;
	unsigned char beforeTeam[0x0d];
	Int teamNumber;
	unsigned char beforePlayerName[0x10];
	AsciiString playerName;
};

class GameSlot
{
public:
	virtual void reset();
	Bool isHuman() const;
	Bool isOccupied() const;
	Bool isAI() const;
	Int getApparentColor() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;
	UnicodeString getName() const;
	Int getTeamNumber() const
	{
		return ((const BFMEGameSlotView *)this)->teamNumber;
	}
	Bool isMuted() const
	{
		return ((const BFMEGameSlotView *)this)->muted;
	}
};

class GameInfo
{
public:
	GameSlot *getSlot( Int slotNum );
	const GameSlot *getConstSlot( Int slotNum ) const;
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Int getLocalSlotNum() const;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey( NameKeyType key );
};

class Player
{
public:
	Bool isPlayerObserver() const;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class MultiplayerColorDefinition
{
public:
	Color getColor() const
	{
		return *(const Color *)((const char *)this + 0x10);
	}
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int which );
};

class GameWindow
{
public:
	Int winHide( Bool hide );
	void winSetEnabledTextColors( Color enabled, Color disabled );
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );
};

class BFMENetworkInterfaceView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8c();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9c();
	virtual void slota0();
	virtual void slota4();
	virtual void slota8();
	virtual Bool isPlayerConnected( Int slotNum );
};

class BFMEVictoryConditionsView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual Bool hasSinglePlayerBeenDefeated( Player *player );
};

extern GameInfo *TheGameInfo;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern MultiplayerSettings *TheMultiplayerSettings;
extern GameTextInterface *TheGameText;
extern GameWindow *staticTextPlayer[MAX_SLOTS];
extern GameWindow *staticTextSide[MAX_SLOTS];
extern GameWindow *staticTextTeam[MAX_SLOTS];
extern GameWindow *staticTextStatus[MAX_SLOTS];
extern GameWindow *buttonMute[MAX_SLOTS];
extern GameWindow *buttonUnMute[MAX_SLOTS];
extern Int slotNumInRow[MAX_SLOTS];

class NetworkInterface {};
extern NetworkInterface *TheNetwork;
class VictoryConditionsInterface;
extern VictoryConditionsInterface *TheVictoryConditions;

void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

template<> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString( const UnicodeString &that )
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

inline UnicodeString &UnicodeString::operator=( const UnicodeString &that )
{
	((StringBase<unsigned short> *)this)->set(
		*(const StringBase<unsigned short> *)&that);
	return *this;
}

void PopulateInGameDiplomacyPopup( void )
{
	if (!TheGameInfo)
		return;

	Int rowNum = 0;
	for (Int slotNum=0; slotNum<MAX_SLOTS; ++slotNum)
	{
		const GameSlot *slot = TheGameInfo->getConstSlot(slotNum);
		if (slot && slot->isOccupied())
		{
			Bool isInGame = false;
			if (TheNetwork &&
				((BFMENetworkInterfaceView *)TheNetwork)->isPlayerConnected(slotNum)) {
				isInGame = true;
			} else if ((TheNetwork == NULL) && slot->isHuman()) {
				isInGame = true;
			}
			if (slot->isAI())
				isInGame = true;

			AsciiString playerName =
				((BFMEGameSlotView *)TheGameInfo->getSlot(slotNum))->playerName;
			Player *player = ThePlayerList->findPlayerWithNameKey(
				TheNameKeyGenerator->nameToKey(playerName.str()));
			if (!player)
				continue;
			Bool isAlive = !((BFMEVictoryConditionsView *)TheVictoryConditions)->hasSinglePlayerBeenDefeated(player);
			Bool isObserver = player->isPlayerObserver();

			if (slot->isHuman() && TheGameInfo->getLocalSlotNum() != slotNum && isInGame)
			{
				if (buttonMute[rowNum])
					buttonMute[rowNum]->winHide(slot->isMuted());
				if (buttonUnMute[rowNum])
					buttonUnMute[rowNum]->winHide(!slot->isMuted());
			}
			else
			{
				if (buttonMute[rowNum])
					buttonMute[rowNum]->winHide(true);
				if (buttonUnMute[rowNum])
					buttonUnMute[rowNum]->winHide(true);
			}

			Color playerColor = TheMultiplayerSettings->getColor(slot->getApparentColor())->getColor();
			Color backColor = GameMakeColor(0, 0, 0, 255);
			Color aliveColor = GameMakeColor(0, 255, 0, 255);
			Color deadColor = GameMakeColor(255, 0, 0, 255);
			Color observerInGameColor = GameMakeColor(255, 255, 255, 255);
			Color goneColor = GameMakeColor(196, 0, 0, 255);
			Color observerGoneColor = GameMakeColor(196, 196, 196, 255);

			if (staticTextPlayer[rowNum])
			{
				staticTextPlayer[rowNum]->winSetEnabledTextColors( playerColor, backColor );
				GadgetStaticTextSetText(staticTextPlayer[rowNum], slot->getName());
			}
			if (staticTextSide[rowNum])
			{
				staticTextSide[rowNum]->winSetEnabledTextColors( playerColor, backColor );
				GadgetStaticTextSetText(staticTextSide[rowNum], slot->getApparentPlayerTemplateDisplayName() );
			}
			if (staticTextTeam[rowNum])
			{
				staticTextTeam[rowNum]->winSetEnabledTextColors( playerColor, backColor );
				AsciiString teamStr;
				teamStr.format("Team:%d", slot->getTeamNumber() + 1);
				if (slot->isAI() && slot->getTeamNumber() == -1)
					teamStr = "Team:AI";
				GadgetStaticTextSetText(staticTextTeam[rowNum], TheGameText->fetch(teamStr) );
			}
			if (staticTextStatus[rowNum])
			{
				staticTextStatus[rowNum]->winHide(false);
				if (isInGame)
				{
					if (isAlive)
					{
						staticTextStatus[rowNum]->winSetEnabledTextColors( aliveColor, backColor );
						GadgetStaticTextSetText(staticTextStatus[rowNum], TheGameText->fetch("GUI:PlayerAlive"));
					}
					else
					{
						if (isObserver)
						{
							staticTextStatus[rowNum]->winSetEnabledTextColors( observerInGameColor, backColor );
							GadgetStaticTextSetText(staticTextStatus[rowNum], TheGameText->fetch("GUI:PlayerObserver"));
						}
						else
						{
							staticTextStatus[rowNum]->winSetEnabledTextColors( deadColor, backColor );
							GadgetStaticTextSetText(staticTextStatus[rowNum], TheGameText->fetch("GUI:PlayerDead"));
						}
					}
				}
				else
				{
					if (isObserver)
					{
						staticTextStatus[rowNum]->winSetEnabledTextColors( observerGoneColor, backColor );
						GadgetStaticTextSetText(staticTextStatus[rowNum], TheGameText->fetch("GUI:PlayerObserverGone"));
					}
					else
					{
						staticTextStatus[rowNum]->winSetEnabledTextColors( goneColor, backColor );
						GadgetStaticTextSetText(staticTextStatus[rowNum], TheGameText->fetch("GUI:PlayerGone"));
					}
				}
			}

			slotNumInRow[rowNum++] = slotNum;
		}
	}

	while (rowNum < MAX_SLOTS)
	{
		slotNumInRow[rowNum] = -1;
		if (staticTextPlayer[rowNum])
			staticTextPlayer[rowNum]->winHide(true);
		if (staticTextSide[rowNum])
			staticTextSide[rowNum]->winHide(true);
		if (staticTextTeam[rowNum])
			staticTextTeam[rowNum]->winHide(true);
		if (staticTextStatus[rowNum])
			staticTextStatus[rowNum]->winHide(true);
		if (buttonMute[rowNum])
			buttonMute[rowNum]->winHide(true);
		if (buttonUnMute[rowNum])
			buttonUnMute[rowNum]->winHide(true);

		++rowNum;
	}
}
