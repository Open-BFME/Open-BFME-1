// ?_bfme_onSerializedGameInfo_00689170@LANAPI@@UAE_NPAUTransportAddress@@HPADI@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib
// LANAPI vtable slot 39 (vtable 0x0111AF50 + 0x9C).  The serialized
// game-info receive handler _bfme_handleSerializedGameInfo_0068ADE0
// (retail 0x0068ADE0, matched in LANAPIBfmeSlotHandlers.cpp) walks the current
// game's eight slots and forwards a matching sender's serialized payload
// through this slot.  The body refuses the message unless the sender matches
// the addressed slot, the game has not started, the slot is the host's, and
// the game-info guard at +0x00 accepts; a resident serialized block is then
// re-parsed into the game, the slot's last-heard stamp at +0x39c is set, and
// the retained global (or its no-global/fallback arm) is signalled through the
// BFME-only thunks below.

#include "string_base.h"

// class-gate: allow AsciiString this unit is a byte-proved reconstruction whose private
// StringBase<char>/AsciiString pair reproduces retail's inlined string ABI at 0x00689170
// (build.sh exact 480/480); adopting the canonical ascii_string.h is a separate
// reconciliation, not a drop-in for this body.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class UnicodeString
{
public:
	UnicodeString(void) { m_data = 0; }
	__forceinline UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString(void) {}

private:
	void *m_data;
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

#include "../../Include/Common/ScalarTypes.h"





extern Int g_Va012F7734;
extern const char g_Rva0107301CEmptyString[];

enum
{
	LAN_SERIALIZED_GAME_INFO_LENGTH = 0x196,
	LAN_MAX_SLOTS = 8
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
// The two payloads overlap: 0x0068ADE0 reads the serialized game-info block
// that starts at +0x22, and the map status byte 0x0068ACF0 reads at +0x44 falls
// inside it, so the same 0x1DC-byte message carries either one.
struct LANMessage
{
	Int m_type;						// +0x00
	UnsignedByte m_bfmeHeader[0x22 - 4];

	union
	{
		char m_serializedGameInfo[LAN_SERIALIZED_GAME_INFO_LENGTH];	// +0x22

		struct
		{
			UnsignedByte m_bfmeBeforeStatus[0x44 - 0x22];
			UnsignedByte m_status;				// +0x44
		};
	};

	UnsignedByte m_bfmeTail[0x1DC - 0x22 - LAN_SERIALIZED_GAME_INFO_LENGTH];
};

struct BfmeLANSlot
{
	TransportAddress m_address;
	UnsignedByte m_bfmeRest[0x68 - 8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnsignedByte m_bfmeHeadA[0x0d];
	Bool m_inProgress;					// +0x0d
	UnsignedByte m_bfmeHeadB[0x88 - 0x0e];
	BfmeLANSlot m_slot[LAN_MAX_SLOTS];			// +0x88

	void setLastHeard(UnsignedInt time)
	{
		*(UnsignedInt *)((UnsignedByte *)this + 0x39c) = time;
	}
};

class GameInfo;

class BfmeSerializedInfoGuard
{
public:
	char check(void);
};

union BfmeGuardCheckCall
{
	void *asVoid;
	char (BfmeSerializedInfoGuard::*asMember)(void);
};

class Gen_000970a0
{
public:
	int bfmeEquals(const Gen_000970a0 *other) const;
};

union BfmeEqualsCall
{
	void *asVoid;
	int (Gen_000970a0::*asMember)(const Gen_000970a0 *) const;
};

extern AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);


extern Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options,
	char *buffer, UnsignedInt size);

struct BfmeObj935C
{
	UnsignedByte m_bfmeBeforeFlag[0x26c];
	UnsignedByte m_bfmeFlag;
	void bfmeSerializedInfoGlobal(void);
};

union BfmeGlobalCall
{
	void *asVoid;
	void (BfmeObj935C::*asMember)(void);
};

// Retail 0x012F4998: use the existing data owner; retain the local pointee view.
extern class BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

extern void j_000329b1(void);
extern void j_0002a72a(void);
extern void j_00039202(void);
extern void j_0001c9d6(void);
extern void j_000467bd(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
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
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_afterAddress(UnicodeString name) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual Bool _bfme_onSerializedGameInfo_00689170(TransportAddress *from,
		Int playerSlot, char *buffer, UnsignedInt size) = 0;	// slot 39, vtable+0x9C
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;					// slot 46, vtable+0xB8
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_forwardMapStatus(UnsignedByte status) = 0;	// slot 52, vtable+0xD0
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual TransportAddress *_bfme_localAddress(void) = 0;		// slot 55, vtable+0xDC

protected:
	void _bfme_handleHasMap_0068ACF0(LANMessage *message,
		const TransportAddress *sender);
	void _bfme_handleSerializedGameInfo_0068ADE0(LANMessage *message,
		const TransportAddress *sender);

	UnsignedByte m_bfmeBeforeLobbyPlayers[0x08 - 4];
	void *m_lobbyPlayers;
	UnsignedByte m_bfmeBeforeName[0x10 - 0x0c];
	UnicodeString m_name;
	UnsignedByte m_bfmeBeforeLobby[0x3d - 0x14];
	Bool m_inLobby;						// +0x3d
	UnsignedByte m_bfmeBeforeCurrentGame[2];
	LANGameInfo *m_currentGame;				// +0x40
};

// ?_bfme_onSerializedGameInfo_00689170@LANAPI@@UAE_NPAUTransportAddress@@HPADI@Z
Bool LANAPI::_bfme_onSerializedGameInfo_00689170(
	TransportAddress *from, Int playerSlot, char *buffer, UnsignedInt size)
{
	if (!m_currentGame)
		return false;

	BfmeLANSlot *slot = (BfmeLANSlot *)((UnsignedByte *)m_currentGame +
		0x88 + playerSlot * 0x68);
	if (slot->m_address.m_ip != from->m_ip ||
		slot->m_address.m_port != from->m_port ||
		m_currentGame->m_inProgress || playerSlot != 0)
		return false;

	BfmeGuardCheckCall guardCheck;
	guardCheck.asVoid = reinterpret_cast<void *>(j_000329b1);
	if ((reinterpret_cast<BfmeSerializedInfoGuard *>(m_currentGame)
		->*guardCheck.asMember)())
		return false;

	m_currentGame->setLastHeard(timeGetTime());
	char *bufferCopy = buffer;
	UnsignedInt sizeCopy = size;
	const AsciiString oldOptions(GameInfoToAsciiString(
		(const GameInfo *)(UnsignedInt)m_currentGame, true));
	if (ParseGameOptionsString(m_currentGame,
		AsciiString(g_Rva0107301CEmptyString), bufferCopy, sizeCopy))
	{
		for (Int offset = 0x68; offset < 0x340; offset += 0x68)
		{
			const char *slot = (const char *)
				((UnsignedInt)m_currentGame + (UnsignedInt)offset + 0x88);
			BfmeEqualsCall equalsCall;
			equalsCall.asVoid = reinterpret_cast<void *>(j_0002a72a);
			if ((UnsignedByte)(((Gen_000970a0 *)slot)
				->*equalsCall.asMember)(
				(const Gen_000970a0 *)_bfme_localAddress()))
				goto accepted;
		}
	}

	++g_Va012F7734;
	ParseGameOptionsString(m_currentGame, oldOptions, 0, 0);
	if (g_Va012F7734 > 0x10)
	{
		_bfme_afterAddress(m_name);
		g_Va012F7734 = 0;
	}
	return false;

accepted:
	if (reinterpret_cast<BfmeObj935C *>(g_rva012F4998LanLobby))
		reinterpret_cast<BfmeObj935C *>(g_rva012F4998LanLobby)->m_bfmeFlag = 1;
	else
		j_00039202();

	BfmeObj935C *global = reinterpret_cast<BfmeObj935C *>(g_rva012F4998LanLobby);
	if (!global)
		j_0001c9d6();
	else
	{
		BfmeGlobalCall globalCall;
		globalCall.asVoid = reinterpret_cast<void *>(j_000467bd);
		(global->*globalCall.asMember)();
	}
	g_Va012F7734 = 0;
	return true;
}
