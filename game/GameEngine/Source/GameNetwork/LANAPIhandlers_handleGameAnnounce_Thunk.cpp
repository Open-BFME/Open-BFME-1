// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
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
// BFME LANAPI::handleGameAnnounce, RVA 0x0068C110, complete 596 bytes.
// LANAPI::update maps MSG_GAME_ANNOUNCE (1) through table 0x00687A28
// to arm 0x00687209. The call at 0x00687211 follows ILT 0x0004233E here,
// passing the sender's IP/port pair by pointer. RET 8 at 0x0068C361 ends
// before INT3 padding at 0x0068C364.
// Original semantic body: GeneralsMD GameNetwork/LANAPIhandlers.cpp.
// BFME compares both address fields and supplies the packed options buffer
// and length to ParseGameOptionsString, alongside the empty text argument.
// That parser retains the reference's TheLAN/game guards, local-slot lookup,
// old-map/CRC capture and two maps preserving login/host names. Its additional
// packet arguments are independently visible in both retail call sites.
// LANGameInfo layout follows its matched constructor, naming and list methods;
// its constructor/destructor remain external to this local field view.
typedef unsigned short wchar_t;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
extern "C" __declspec(dllimport) wchar_t *__cdecl wcsncpy(wchar_t *, const wchar_t *, unsigned int);
#include "Common/AsciiString.h"
// Local StringBase adapter matches the BFME by-value string construction.
class UnicodeString {
public:
    UnicodeString() { m_data = 0; }
    UnicodeString(const UnicodeString &that) {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t> *)&that);
    }
    explicit UnicodeString(const wchar_t *str) {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str);
    }
    ~UnicodeString();
private:
    void *m_data;
};
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
struct LANMessage
{
    unsigned int messageType; // +0x00
    wchar_t name[13];          // +0x04
    char userName[2];          // +0x1E
    char hostName[2];          // +0x20
    struct {
        wchar_t gameName[17];
        Bool inProgress;
        Bool isDirectConnect;    // +0x45 in LANMessage
        char options[406];
    } GameInfo;
};
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
class LANGameInfo {
public:
    LANGameInfo();
    ~LANGameInfo();
    void setName(UnicodeString name);
    unsigned char head[0x0d];
    Bool inProgress;
    unsigned char beforeNext[0x398 - 0x0e];
    LANGameInfo *next;        // +0x398
    UnsignedInt lastHeard;    // +0x39C
    unsigned char gameName[4];// +0x3A0
    Bool isDirectConnect;    // +0x3A4
};
Bool ParseGameOptionsString(LANGameInfo *, AsciiString, char *, unsigned int);
class LANPlayer;
class LANAPI
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void RequestGameJoin(LANGameInfo *, BfmeNetAddress *) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void RequestSetName(UnicodeString newName);			// slot 24
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void OnGameList(LANGameInfo *) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void OnNameChange(BfmeNetAddress *from, UnicodeString newName) = 0;	// slot 41, vtable+0xA4
	virtual LANGameInfo *LookupGame(UnicodeString) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;			// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;		// slot 54, vtable+0xD8
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;			// slot 55, vtable+0xDC

protected:
    void handleGameAnnounce(LANMessage *msg, BfmeNetAddress *sender);
    void addGame(LANGameInfo *);
    void removeGame(LANGameInfo *);
    unsigned char beforeGames[0x0c - 4];
    LANGameInfo *games;
    unsigned char beforeDirect[0x30 - 0x10];
    BfmeNetAddress directRemote;
    unsigned char beforeCurrent[0x40 - 0x38];
    LANGameInfo *currentGame;

};
typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];
typedef char BfmeMessageSizeCheck[sizeof(LANMessage) == 0x1DC ? 1 : -1];

typedef char BfmeGameSizeCheck[sizeof(LANGameInfo) == 0x3A8 ? 1 : -1];
void LANAPI::handleGameAnnounce(LANMessage *msg, BfmeNetAddress *sender)
{
    const BfmeNetAddress *local = _bfme_localAddress();
    if (sender->m_ip == local->m_ip && sender->m_port == local->m_port) {
        return;
    } else if (currentGame && currentGame->inProgress) {
        return;
    } else if (sender->m_ip == directRemote.m_ip && sender->m_port == directRemote.m_port) {
        if (currentGame == 0) {
            LANGameInfo *game = LookupGame(UnicodeString(msg->GameInfo.gameName));
            if (!game) {
                game = new LANGameInfo;
                game->setName(UnicodeString(msg->GameInfo.gameName));
                addGame(game);
            }
            Bool success = ParseGameOptionsString(game,AsciiString(""),msg->GameInfo.options,406);
            game->inProgress = msg->GameInfo.inProgress;
            game->isDirectConnect = msg->GameInfo.isDirectConnect;
            game->lastHeard = timeGetTime();
            if (!success) {
                removeGame(game);
                delete game;
                game = 0;
                return;
            }
            RequestGameJoin(game,&directRemote);
        }
    } else {
        LANGameInfo *game = LookupGame(UnicodeString(msg->GameInfo.gameName));
        if (!game) {
            game = new LANGameInfo;
            game->setName(UnicodeString(msg->GameInfo.gameName));
            addGame(game);
        }
        Bool success = ParseGameOptionsString(game,AsciiString(""),msg->GameInfo.options,406);
        game->inProgress = msg->GameInfo.inProgress;
        game->isDirectConnect = msg->GameInfo.isDirectConnect;
        game->lastHeard = timeGetTime();
        if (!success) {
            removeGame(game);
            delete game;
            game = 0;
        }
        OnGameList(games);
    }
}
