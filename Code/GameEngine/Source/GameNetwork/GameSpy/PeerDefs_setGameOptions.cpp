// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// GameSpyInfo::setGameOptions, RVA 0x00635D90, 1786 bytes.
// Identity: native GameSpyInfo vtable slot 0xCC, PeerDefs.cpp source twin,
// Pings/ and %04d=%s literals, and GameSpyInfo TU neighbors.
// Native PeerRequest extent 0x194; BFME writes all arrays at the original
// slot index and publishes a separate type-24 encoded-name request per human.
// The extra option is named by its request offset, not guessed semantics.
// GameSpyGameSlot::getPingString const is witnessed by StagingRoomGameInfo.h,
// its caller's Pings/ message, and the +0x50 member in the matched setter.
// See build/unclaimed_map/astra_P/LAYOUTS.md for instruction witnesses.
#include <map>
#include <string>
#include <vector>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
template <class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline const wchar_t *StringBase<wchar_t>::str() const { return m_data ? m_data->data : L""; }
template <class T> inline T StringBase<T>::getCharAt(int i) const { return m_data ? m_data->data[i] : 0; }
template <class T> inline void StringBase<T>::concat(T c) { concat(&c, 1); }
template <> inline void StringBase<char>::concat(const char *s) { concat(s,strlen(s)); }
template <> inline void StringBase<char>::concat(const StringBase<char>& s) { concat(s.str(),s.getLength()); }
typedef int Int;
#define MAX_SLOTS 8
#define TRUE true
#define PLAYERTEMPLATE_OBSERVER -2
#define SLOT_EASY_AI 2
#define SLOT_MED_AI 3
#define SLOT_BRUTAL_AI 4
class PlayerInfo { public:
    PlayerInfo(); PlayerInfo(const PlayerInfo&); ~PlayerInfo();
    AsciiString m_name, m_baseName, m_locale;
    int m_wins, m_losses, m_profileID, m_flags, m_rankPoints;
    int field_20, field_24, field_28, m_side, m_preorder;
};
struct AsciiComparator { bool operator()(AsciiString,AsciiString) const; };
typedef std::map<AsciiString,PlayerInfo,AsciiComparator> PlayerInfoMap;
class PeerRequest { public:
    PeerRequest(); ~PeerRequest();
    enum { PEERREQUEST_SETGAMEOPTIONS=10, PEERREQUEST_UTMROOM=14, Rva00635D90Request24=24 } peerRequestType;
    std::string nick; std::wstring text; std::string password, email, id, options, ladderIP, hostPingStr, gameOptsMapName;
    std::string gameOptsPlayerNames[MAX_SLOTS];
    std::vector<bool> qmMaps;
    union {
        struct { int wins[8], losses[8], profileID[8], faction[8], color[8]; int numPlayers,maxPlayers,numObservers,field_190; } gameOptions;
        struct { bool isStagingRoom; } UTM;
    };
};
class GameSlot { public:
    virtual void reset();
    bool isOccupied() const; bool isOpen() const; bool isHuman() const; bool isAI() const;
    UnicodeString getName() const;
    int getState() const { return m_state; }
    int getPlayerTemplate() const { return m_playerTemplate; }
    int getColor() const { return m_color; }
    int m_state; int field_08; int m_color; int field_10; int m_playerTemplate;
    unsigned char field_18[0x2c];
};
class GameSpyGameSlot : public GameSlot { public:
    __declspec(noinline) AsciiString getPingString() const;
    int m_profileID; AsciiString m_gameSpyLogin, m_gameSpyLocale, m_pingString;
};
AsciiString GameSpyGameSlot::getPingString() const { return m_pingString; }
class GameInfo { public:
    AsciiString getMap() const;
    const GameSlot *getConstSlot(int) const;
    unsigned char field_00[0x54];
    int field_54;
};
class GameSpyStagingRoom : public GameInfo { public:
    GameSpyGameSlot *getGameSpySlot(int);
};
class GameState { public: AsciiString realMapPathToPortableMapPath(const AsciiString &) const; };
AsciiString GameInfoToAsciiString(const GameInfo *,bool);
std::string WideCharStringToMultiByte(const wchar_t *);
class GameSpyPeerMessageQueueInterface { public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void addRequest(const PeerRequest&)=0;
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameSpyStagingRoom *TheGameSpyGame;
extern GameState *TheGameState;
class GameSpyInfo { public:
    virtual void rva00635D90_slot00();
    virtual void rva00635D90_slot04();
    virtual void rva00635D90_slot08();
    virtual void rva00635D90_slot0C();
    virtual void rva00635D90_slot10();
    virtual void rva00635D90_slot14();
    virtual void rva00635D90_slot18();
    virtual void rva00635D90_slot1C();
    virtual void rva00635D90_slot20();
    virtual void rva00635D90_slot24();
    virtual void rva00635D90_slot28();
    virtual void rva00635D90_slot2C();
    virtual void rva00635D90_slot30();
    virtual void rva00635D90_slot34();
    virtual void rva00635D90_slot38();
    virtual void rva00635D90_slot3C();
    virtual void rva00635D90_slot40();
    virtual void rva00635D90_slot44();
    virtual void rva00635D90_slot48();
    virtual void rva00635D90_slot4C();
    virtual void rva00635D90_slot50();
    virtual void rva00635D90_slot54();
    virtual void rva00635D90_slot58();
    virtual void rva00635D90_slot5C();
    virtual void rva00635D90_slot60();
    virtual void rva00635D90_slot64();
    virtual void rva00635D90_slot68();
    virtual void rva00635D90_slot6C();
    virtual void rva00635D90_slot70();
    virtual void rva00635D90_slot74();
    virtual void rva00635D90_slot78();
    virtual void rva00635D90_slot7C();
    virtual void rva00635D90_slot80();
    virtual void rva00635D90_slot84();
    virtual void rva00635D90_slot88();
    virtual void rva00635D90_slot8C();
    virtual void rva00635D90_slot90();
    virtual void rva00635D90_slot94();
    virtual void rva00635D90_slot98();
    virtual void rva00635D90_slot9C();
    virtual void rva00635D90_slotA0();
    virtual void rva00635D90_slotA4();
    virtual void rva00635D90_slotA8();
    virtual void rva00635D90_slotAC();
    virtual void rva00635D90_slotB0();
    virtual void rva00635D90_slotB4();
    virtual void rva00635D90_slotB8();
    virtual void rva00635D90_slotBC();
    virtual void rva00635D90_slotC0();
    virtual void rva00635D90_slotC4();
    virtual void rva00635D90_slotC8();
    virtual void setGameOptions();
    char field_04[0x48];
    PlayerInfoMap m_playerInfoMap;
    char field_58[0x200];
    bool m_isHosting;
    GameSpyStagingRoom m_localStagingRoom;
};
typedef char RequestSize[sizeof(PeerRequest)==0x194?1:-1];
typedef char SlotSize[sizeof(GameSlot)==0x44?1:-1];
void GameSpyInfo::setGameOptions( void )
{
	if (!m_isHosting)
		return;

	// set options for game lists, and UTM players in-game
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_SETGAMEOPTIONS;
	req.options = GameInfoToAsciiString(&m_localStagingRoom, false).str();

	Int i;
	AsciiString mapName = TheGameState->realMapPathToPortableMapPath(m_localStagingRoom.getMap());
	AsciiString newMapName;
	for (i=0; i<mapName.getLength(); ++i)
	{
		char c = mapName.getCharAt(i);
		if (c != '\\')
			newMapName.concat(c);
		else
			newMapName.concat('/');
	}
	req.gameOptsMapName = newMapName.str();

	req.gameOptions.field_190 = m_localStagingRoom.field_54;
	req.gameOptions.numPlayers = 0;
	req.gameOptions.numObservers = 0;
	Int numOpenSlots = 0;
	AsciiString playerInfo = "";
	for (i=0; i<MAX_SLOTS; ++i)
	{
		Int wins = 0, losses = 0, profileID = 0;
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
		req.gameOptsPlayerNames[i] = "";
        req.gameOptions.wins[i] = 0;
        req.gameOptions.losses[i] = 0;
        req.gameOptions.profileID[i] = slot->getState();
        req.gameOptions.faction[i] = slot->getPlayerTemplate();
        req.gameOptions.color[i] = slot->getColor();
		if (!slot->isOccupied())
		{
			if (slot->isOpen())
				++numOpenSlots;
		}
		else
		{
			AsciiString playerName;
			if (slot->isHuman())
			{
				playerName.translate(slot->getName());
				req.gameOptsPlayerNames[i] = playerName.str();
				PlayerInfoMap::iterator it = m_playerInfoMap.find(playerName);
				if (it != m_playerInfoMap.end())
				{
					wins = it->second.m_wins;
					losses = it->second.m_losses;
					profileID = it->second.m_profileID;
				}
				req.gameOptions.wins[i] = wins;
				req.gameOptions.losses[i] = losses;
				req.gameOptions.profileID[i] = profileID;
				req.gameOptions.faction[i] = slot->getPlayerTemplate();
				req.gameOptions.color[i] = slot->getColor();
				if (slot->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER)
				{
					++req.gameOptions.numObservers;
				}
				else
				{
					++req.gameOptions.numPlayers;
				}
			}
			else if (slot->isAI())
			{
				// add in AI players
				switch (slot->getState())
				{
				case SLOT_EASY_AI:
					((StringBase<char>*)&playerName)->set("CE", 2);
					break;
				case SLOT_MED_AI:
					((StringBase<char>*)&playerName)->set("CM", 2);
					break;
				case SLOT_BRUTAL_AI:
					((StringBase<char>*)&playerName)->set("CH", 2);
					break;
				}
				req.gameOptsPlayerNames[i] = playerName.str(); // name is unused - we go off of the profileID
				req.gameOptions.wins[i] = 0;
				req.gameOptions.losses[i] = 0;
				req.gameOptions.profileID[i] = slot->getState();
				req.gameOptions.faction[i] = slot->getPlayerTemplate();
				req.gameOptions.color[i] = slot->getColor();
				++req.gameOptions.numPlayers;
			}
		}
	}
	req.gameOptions.maxPlayers = numOpenSlots + req.gameOptions.numPlayers + req.gameOptions.numObservers;
	TheGameSpyPeerMessageQueue->addRequest(req);

    for (unsigned int j = 0; j < MAX_SLOTS; ++j) {
        const GameSlot *slot = m_localStagingRoom.getConstSlot(j);
        if (slot->isHuman()) {
            AsciiString encoded;
            encoded.format("%04d=%s", j, WideCharStringToMultiByte(slot->getName().str()).c_str());
            PeerRequest playerRequest;
            playerRequest.peerRequestType = PeerRequest::Rva00635D90Request24;
            playerRequest.options = encoded.str();
            TheGameSpyPeerMessageQueue->addRequest(playerRequest);
        }
    }

	req.peerRequestType = PeerRequest::PEERREQUEST_UTMROOM;
	req.UTM.isStagingRoom = TRUE;
	req.id = "Pings/";
	AsciiString pings;
	for (i=0; i<MAX_SLOTS; ++i)
	{
		if (i!=0)
			pings.concat(",");

		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
		if (slot && slot->isHuman())
		{
			pings.concat(slot->getPingString());
		}
		else
		{
			pings.concat("0");
		}
	}
	req.options = pings.str();
	TheGameSpyPeerMessageQueue->addRequest(req);
}

