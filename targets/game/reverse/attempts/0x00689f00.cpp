// ?OnGameOptions@LANAPI@@UAEXPAUBfmeNetAddress@@IVAsciiString@@@Z
// partial score=0.5889 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

#include <stdlib.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class GameSlot
{
public:
	void *m_vptr;
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	unsigned char m_beforeColor;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_team;
	unsigned char m_beforeAddress[0x30 - 0x1c];
	BfmeNetAddress m_address;
	unsigned char m_rest[0x44 - 0x38];

	void setPlayerTemplate(Int value);
};

class LANGameSlot : public GameSlot
{
public:
	unsigned char m_userAndSerial[0x20];
	UnsignedInt m_lastHeard;

	void setLogin(AsciiString name);
	void setHost(AsciiString name);
};

class LANGameInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void resetAccepted(void) = 0;

	unsigned char m_beforeProgress[0x0d - 4];
	Bool m_inProgress;
	unsigned char m_beforeSlots[0x58 - 0x0e];
	LANGameSlot m_LANSlot[8];

	void setPlayerLastHeard(Int slot, UnsignedInt time);
};

struct Rva0068D3E0Slot;
class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

static __forceinline LANGameSlot *slotAt(Int index, LANGameInfo *game)
{
	return (LANGameSlot *)((Rva0068D3E0Arr *)game)->at(index);
}

class BfmeThing935B
{
public:
	char bfmeGo935B(void);
};

class BfmeKeyXW
{
public:
	Int bfmeDiffersXW(const BfmeKeyXW *other) const;
};

class MultiplayerSettings
{
public:
	Int getNumColors(void);
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount(void) const;
};

extern MultiplayerSettings *TheMultiplayerSettings;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern void __cdecl j_0001c21a(void);

class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void _bfme_requestSerializedGameInfo(Bool, BfmeNetAddress *) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void OnGameOptions(BfmeNetAddress *, UnsignedInt, AsciiString) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;

	unsigned char m_beforeLobby[0x3d - 4];
	Bool m_inLobby;
	unsigned char m_beforeCurrentGame[2];
	LANGameInfo *m_currentGame;
};

static __forceinline Bool isRemotePeer(LANAPI *api, BfmeNetAddress *peer)
{
	return api->AmIHost() &&
		((BfmeKeyXW *)api->_bfme_localAddress())->bfmeDiffersXW(
			(const BfmeKeyXW *)peer);
}

void LANAPI::OnGameOptions(BfmeNetAddress *sender, UnsignedInt playerSlot,
	AsciiString options)
{
	register BfmeNetAddress *peer = sender;
	register LANAPI *api = this;
	if (!api->m_currentGame)
		return;

	BfmeNetAddress *slotAddress =
		&api->m_currentGame->m_LANSlot[playerSlot].m_address;
	if (slotAddress->m_ip != peer->m_ip ||
		slotAddress->m_port != peer->m_port)
		return;

	if (api->m_currentGame->m_inProgress)
		return;

	if (playerSlot == 0 &&
		!((BfmeThing935B *)api->m_currentGame)->bfmeGo935B())
		return;

	{
		AsciiString key;
		AsciiString munkee = options;
		munkee.nextToken(&key, "=");

		LANGameSlot *slot = slotAt(playerSlot, api->m_currentGame);
		if (!slot)
			return;

		if (key.compare("User") == 0)
		{
			slot->setLogin(munkee.str() + 1);
			return;
		}
		else if (key.compare("Host") == 0)
		{
			slot->setHost(munkee.str() + 1);
			return;
		}
	}

	if (isRemotePeer(api, peer))
	{
		if (options.compare("HELLO") == 0)
		{
			api->m_currentGame->setPlayerLastHeard(playerSlot, timeGetTime());
		}
		else
		{
			api->m_currentGame->setPlayerLastHeard(playerSlot, timeGetTime());
			Bool change = false;
			Bool shouldUnaccept = false;
			AsciiString key;
			options.nextToken(&key, "=");
			Int val = atoi(options.str() + 1);
			LANGameSlot *slot = slotAt(playerSlot, api->m_currentGame);
			if (!slot)
				return;

			if (key.compare("Color") == 0)
		{
			if (val >= -1 && val < TheMultiplayerSettings->getNumColors() &&
				val != slot->m_color && slot->m_playerTemplate != -2)
			{
				Bool colorAvailable = true;
				if (val != -1)
				{
					for (Int i = 0; i < 8; i++)
					{
						LANGameSlot *checkSlot =
							slotAt(i, api->m_currentGame);
						if (val == checkSlot->m_color && slot != checkSlot)
						{
							colorAvailable = false;
							break;
						}
					}
				}
				if (colorAvailable)
					slot->m_color = val;
				change = true;
			}
		}
		else if (key.compare("PlayerTemplate") == 0)
		{
			if (val >= -2 &&
				val < ThePlayerTemplateStore->getPlayerTemplateCount() &&
				val != slot->m_playerTemplate)
			{
				slot->setPlayerTemplate(val);
				if (val == -2)
				{
					slot->m_color = -1;
					slot->m_startPos = -1;
					slot->m_team = -1;
				}
				change = true;
				shouldUnaccept = true;
			}
		}
		else if (key.compare("StartPos") == 0 &&
			slot->m_playerTemplate != -2)
		{
			if (val >= -1 && val < 8 && val != slot->m_startPos)
			{
				Bool startPosAvailable = true;
				if (val != -1)
				{
					for (Int i = 0; i < 8; i++)
					{
						LANGameSlot *checkSlot =
							slotAt(i, api->m_currentGame);
						if (val == checkSlot->m_startPos && slot != checkSlot)
						{
							startPosAvailable = false;
							break;
						}
					}
				}
				if (startPosAvailable)
					slot->m_startPos = val;
				change = true;
				shouldUnaccept = true;
			}
		}
		else if (key.compare("Team") == 0)
		{
			if (val >= -1 && val < 4 && val != slot->m_team &&
				slot->m_playerTemplate != -2)
			{
				slot->m_team = val;
				change = true;
				shouldUnaccept = true;
			}
		}
		else if (key.compare("NAT") == 0)
		{
			if (val >= 1 && val <= 64)
			{
				*(Int *)((char *)slot + 0x38) = val;
				change = true;
			}
		}

			if (change)
			{
				if (shouldUnaccept)
					api->m_currentGame->resetAccepted();
				BfmeNetAddress noAddress;
				noAddress.m_ip = 0;
				noAddress.m_port = 0;
				_bfme_requestSerializedGameInfo(true, &noAddress);
				j_0001c21a();
			}
		}
	}
}
