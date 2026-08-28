// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?RequestGameJoin@LANAPI@@UAEXPAVLANGameInfo@@I@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// LANAPI::RequestGameJoin, 0x00688770, 387 bytes -- LANAPI vtable slot 11.
//
// The slot is not a guess. Slot 10 is RequestLocations and slot 14 is
// RequestAccept, both already ledgered, and the reference puts exactly three
// entries between them: RequestGameJoin, RequestGameJoinDirectConnect and
// RequestGameLeave. Slot 11 is the first of the three, and it is the only one
// of them the reference gives two parameters -- retail's `ret 8` agrees.
//
// The reference's body with three BFME departures:
//
//   - OnGameJoin takes a third argument. Both early returns push three, and
//     the reference declares two. It stays unnamed here; the call is virtual,
//     so nothing has to be pinned for it.
//   - m_exeCRC is not read directly. It goes through the obfuscation-hook
//     wrapper at 0x0009B4B0 -- see BigObfHookWrappers.cpp -- called with the
//     member's value as both arguments.
//   - a fourth CRC-shaped GlobalData dword at +0xBD4 is copied into the
//     message after iniCRC, where the reference stops at two. Neither it nor
//     the message field it lands in is named.
//
// AsciiString comes from reference/shims/stringbaseascii for the reason
// Transport_init_AsciiString.cpp uses it: the two by-value arguments to
// GetStringFromRegistry are built in the outgoing argument slots, and only a
// copy constructor that visibly delegates to StringBase<char> puts the
// __$SEHRec$ store ahead of `mov ecx, esp` the way retail has it.

#include "Common/AsciiString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0

extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dest, const char *src, unsigned int count);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

enum { LAN_GAME_NAME_LENGTH = 16 };
enum { MAX_SERIAL_LENGTH = 0x17 };

enum LANMessageType
{
	LANMSG_REQUEST_JOIN = 3
};

enum ReturnType
{
	RET_GAME_GONE = 8,
	RET_BUSY = 9
};

enum PendingActionType
{
	ACT_NONE = 0,
	ACT_JOIN = 1,
	ACT_JOINDIRECTCONNECT = 2
};

// Packed, and that is load-bearing: unpacked, the four-dword GameToJoin
// payload forces the union to 4-byte alignment and every field in it lands two
// bytes high of where retail addresses it.
#pragma pack(push, 1)
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	Int LANMessageType;					// +0x00
	UnsignedByte m_bfmeHeader[0x22 - 4];			// filled in by fillInLANMessage
	struct
	{
		UnsignedInt gameIP;				// +0x22
		UnsignedInt exeCRC;				// +0x26
		UnsignedInt iniCRC;				// +0x2A
		UnsignedInt bfmeExtraCRC;			// +0x2E, not yet named
		char serial[MAX_SERIAL_LENGTH];			// +0x32
	} GameToJoin;
	UnsignedByte m_bfmeTail[0x1DC - 0x49];
};
#pragma pack(pop)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	UnsignedInt getIP(void) const { return m_IP; }

	UnsignedByte m_bfmeHead[0x30];
	UnsignedInt m_IP;					// this+0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(Int slot);				// ILT thunk 0x0001EC18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	UnsignedByte m_bfmeHead[0xBC8];
	UnsignedInt m_iniCRC;					// this+0xBC8
	UnsignedByte m_bfmeGap[4];
	UnsignedInt m_exeCRC;					// this+0xBD0
	UnsignedInt m_bfmeExtraCRC;				// this+0xBD4, not yet named
};

extern GlobalData *TheWritableGlobalData;			// retail [0x012ED5C8]

// The obfuscation-hook wrapper an obfuscated GlobalData member is read
// through; see Code/GameEngine/Source/Common/BigObfHookWrappers.cpp.
Int Rva0009B4B0(Int a, Int b);					// ILT thunk 0x000019F6

Bool GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val);	// ILT thunk 0x0000249B

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
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
	virtual void RequestGameJoin(LANGameInfo *game, UnsignedInt ip);	// slot 11
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
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	// slot 29, vtable+0x74. BFME passes a third argument the reference does not.
	virtual void OnGameJoin(Int ret, LANGameInfo *theGame, void *bfmeExtra) = 0;
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
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;		// slot 49, vtable+0xC4

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip);		// ILT thunk 0x0002B599

	UnsignedByte m_bfmeHead[0x24 - 4];
	Int m_pendingAction;						// this+0x24
	UnsignedInt m_expiration;					// this+0x28
	UnsignedInt m_actionTimeout;					// this+0x2C
};

// ?RequestGameJoin@LANAPI@@UAEXPAVLANGameInfo@@I@Z
void LANAPI::RequestGameJoin( LANGameInfo *game, UnsignedInt ip )
{
	if ((m_pendingAction != ACT_NONE) && (m_pendingAction != ACT_JOINDIRECTCONNECT))
	{
		OnGameJoin( RET_BUSY, NULL, NULL );
		return;
	}

	if (!game)
	{
		OnGameJoin( RET_GAME_GONE, NULL, NULL );
		return;
	}

	LANMessage msg;
	msg.LANMessageType = LANMSG_REQUEST_JOIN;
	fillInLANMessage( &msg );
	msg.GameToJoin.gameIP = game->getSlot(0)->getIP();
	msg.GameToJoin.exeCRC = Rva0009B4B0(TheWritableGlobalData->m_exeCRC, TheWritableGlobalData->m_exeCRC);
	msg.GameToJoin.iniCRC = TheWritableGlobalData->m_iniCRC;
	msg.GameToJoin.bfmeExtraCRC = TheWritableGlobalData->m_bfmeExtraCRC;

	AsciiString s = "";
	GetStringFromRegistry("\\ergc", "", s);
	strncpy(msg.GameToJoin.serial, s.str(), MAX_SERIAL_LENGTH);
	msg.GameToJoin.serial[MAX_SERIAL_LENGTH-1] = '\0';

	sendMessage(&msg, ip);

	m_pendingAction = ACT_JOIN;
	m_expiration = timeGetTime() + m_actionTimeout;
}
