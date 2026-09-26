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
// BFME LANAPI::handleRequestLocations, RVA 0x0068AEF0, complete 600 bytes.
// LANAPI::update maps MSG_REQUEST_LOCATIONS (0) through table 0x00687A28
// to arm 0x006871F7. Its call at 0x006871FF follows ILT 0x00011AA9 here,
// passing a pointer to the sender's IP/port pair. RET 8 at 0x0068B145 ends
// before INT3 padding at 0x0068B148.
// Original semantic body: LANAPIhandlers.cpp. BFME uses the matched
// fillCurrentLANGameInfo helper for the 406-byte options buffer and compares
// both host address fields, as the matched RequestGameAnnounce path does.
// Player layout/virtual slots are shared with the matched RequestSetName.
// The StringBase view below exposes the existing eight-byte string header
// so str() inlines without adding an exception state to the game-name copy.
typedef unsigned short wchar_t;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
extern "C" __declspec(dllimport) wchar_t *__cdecl wcsncpy(wchar_t *, const wchar_t *, unsigned int);
#include "Common/AsciiString.h"
// Local StringBase adapter also exposes str() for the inlined game-name copy.
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
    void set(const UnicodeString &that) {
        ((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
    }
    void translate(const AsciiString &that);
    const wchar_t *str() const {
        return m_data ? reinterpret_cast<const wchar_t *>(m_data) + 4 : L"";
    }
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
        wchar_t gameName[17]; // +0x22
        Bool inProgress;     // +0x44
        Bool isDirectConnect;// +0x45
        char options[406];   // +0x46
    } GameInfo;
};
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
class LANGameInfo {
public:
    UnicodeString getName();
    unsigned char head[0x0d];
    Bool inProgress;
    unsigned char beforeAddress[0x88 - 0x0e];
    BfmeNetAddress hostAddress;
};
void __cdecl fillCurrentLANGameInfo(char *, unsigned int);
class LANPlayer
{
public:
	LANPlayer()
	{
		m_lastHeard = 0;
		m_next = 0;
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}

	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};
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
	virtual void _bfme_slot11(void) = 0;
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
	virtual void _bfme_slot27(void) = 0;
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
	virtual void _bfme_slot42(void) = 0;
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
	void handleRequestLocations(LANMessage *msg, BfmeNetAddress *sender);
	void sendMessage(LANMessage *, UnsignedInt ip = 0);
	void removePlayer(LANPlayer *player);					// ILT thunk 0x0003BDF4
	void addPlayer(LANPlayer *player);					// ILT thunk 0x00045363

    unsigned char beforeResend[0x38 - 4];
    UnsignedInt lastResendTime;
    unsigned char beforeLobby[1];
    Bool inLobby;
    LANGameInfo *currentGame;

};
typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];
typedef char BfmePlayerSizeCheck[sizeof(LANPlayer) == 0x1C ? 1 : -1];
typedef char BfmeMessageSizeCheck[sizeof(LANMessage) == 0x1DC ? 1 : -1];

void LANAPI::handleRequestLocations(LANMessage *msg, BfmeNetAddress *sender)
{
    if (inLobby) {
        LANMessage reply;
        fillInLANMessage(&reply);
        reply.messageType = 2;
        sendMessage(&reply);
        lastResendTime = timeGetTime();
    } else {
        LANGameInfo *game = currentGame;
        if (game) {
            const BfmeNetAddress *local = _bfme_localAddress();
            if (game->hostAddress.m_ip == local->m_ip &&
                game->hostAddress.m_port == local->m_port) {
                LANMessage reply;
                fillInLANMessage(&reply);
                reply.messageType = 1;
                fillCurrentLANGameInfo(reply.GameInfo.options, 406);
                wcsncpy(reply.GameInfo.gameName, currentGame->getName().str(), 16);
                reply.GameInfo.gameName[16] = 0;
                reply.GameInfo.inProgress = currentGame->inProgress;
                sendMessage(&reply);
            }
        }
    }
    LANPlayer *player = LookupPlayer(sender);
    if (!player) {
        player = new LANPlayer;
        player->m_address = *sender;
    } else {
        removePlayer(player);
    }
    player->m_name.set(UnicodeString(msg->name));
    player->m_host.translate(AsciiString(msg->hostName));
    player->m_login.translate(AsciiString(msg->userName));
    player->m_lastHeard = timeGetTime();
    addPlayer(player);
    OnNameChange(&player->m_address, player->m_name);
}
