// ?OnGameStart@LANAPI@@UAEXXZ
// partial score=0.2 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// LANAPI::OnGameStart, retail 0x0068A3E0, 1041 bytes.
//
// The Zero Hour callback in LANAPICallbacks.cpp is not the BFME body: BFME
// grows LANAPI's prefix to put m_currentGame at +0x40, normalises the local
// and participant transport ports, and hands a transport-address record to
// NetworkInterface.  Keep that ABI slice local to this body.

#include "PreRTS.h"

#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/MessageStream.h"
#include "Common/QuotedPrintable.h"
#include "Common/RandomValue.h"
#include "Common/UserPreferences.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "GameClient/MessageBox.h"
#include "GameNetwork/FileTransfer.h"

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
	UnsignedShort m_pad;
};

typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];

class GameInfo
{
public:
	AsciiString getMap(void) const;
};

class BfmeGameSlot
{
public:
	Bool isHuman(void) const;

private:
	UnsignedByte m_beforeAddress[0x30 - 4];

public:
	BfmeNetAddress m_address;
};

class BfmeGameInfo : public GameInfo
{
public:
	BfmeGameSlot *getSlot(Int slot);
};

// The body at 0x0068D3E0 is the bounds-checked eight-slot array accessor
// (object +0x58, stride 0x68), reached here through ILT 0x000234D4.
class Rva0068D3E0Slot
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual Int getColor(void) const = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual Int getPlayerTemplate(void) const = 0;
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

class LANGameInfo : public BfmeGameInfo
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual Int getLocalSlotNum(void) const = 0;

	~LANGameInfo(void);

	Int getSeed(void) const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x4c);
	}
};

class BfmeThing935B
{
public:
	char bfmeGo935B(void);
};

class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool unused);
};

class NetworkInterface
{
public:
	virtual ~NetworkInterface(void);
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
	virtual void parseUserList(const GameInfo *game) = 0;
	virtual void setLocalAddress(const BfmeNetAddress *address) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void initTransport(void) = 0;
};

extern NetworkInterface *TheNetwork;
extern void createTheNetwork(void);

struct BfmeGameInfoAddressView
{
	UnsignedByte m_beforeAddress[0x34];
	BfmeNetAddress m_address;
};

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
	virtual void OnPlayerLeave(UnicodeString player) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void OnChat(UnicodeString player, UnsignedInt ip,
		UnicodeString message, Int chatType) = 0;
	virtual void OnGameStart(void);
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
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *getLocalAddress(void) = 0;

protected:
	void removeGame(LANGameInfo *game);

	UnsignedByte m_beforeName[0x10 - 4];
	UnicodeString m_name;
	UnsignedByte m_beforeMenu[0x3c - 0x14];
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_beforeCurrentGame[2];
	LANGameInfo *m_currentGame;
};

struct BfmeGameSlotAddressView
{
	UnsignedByte m_beforeAddress[0x30];
	BfmeNetAddress m_address;
};

// ?OnGameStart@LANAPI@@UAEXXZ
void LANAPI::OnGameStart(void)
{
	if (m_currentGame)
	{
		LANPreferences pref;
		AsciiString option;
		option.format("%d", ((Rva0068D3E0Arr *)m_currentGame)->at(
			m_currentGame->getLocalSlotNum())->getPlayerTemplate());
		pref["PlayerTemplate"] = option;
		option.format("%d", ((Rva0068D3E0Arr *)m_currentGame)->at(
			m_currentGame->getLocalSlotNum())->getColor());
		pref["Color"] = option;
		if (((BfmeThing935B *)m_currentGame)->bfmeGo935B())
		{
			pref["Map"] = AsciiStringToQuotedPrintable(m_currentGame->getMap());
		}
		pref.write();

		m_isInLANMenu = FALSE;

		createTheNetwork();
		BfmeNetAddress localAddress = *getLocalAddress();
		localAddress.m_port = (UnsignedShort)(localAddress.m_port + 8);
		TheNetwork->setLocalAddress(&localAddress);
		TheNetwork->initTransport();

		((BfmeGameInfoAddressView *)m_currentGame)->m_address = localAddress;
		for (Int player = 0; player < 8; ++player)
		{
			BfmeGameSlot *slot = ((BfmeGameInfo *)m_currentGame)->getSlot(player);
			if (slot->isHuman())
			{
				BfmeGameSlotAddressView *address =
					(BfmeGameSlotAddressView *)slot;
				BfmeNetAddress slotAddress = address->m_address;
				slotAddress.m_port = (UnsignedShort)(slotAddress.m_port + 8);
				address->m_address = slotAddress;
			}
		}

		TheNetwork->parseUserList(m_currentGame);
		((BfmeGameLogicPause *)TheGameLogic)->clearGameData(FALSE, FALSE);
		Bool filesOk = DoAnyMapTransfers(m_currentGame);

		TheMapCache->updateCache();
		if (!filesOk || TheMapCache->findMap(m_currentGame->getMap()) == NULL)
		{
			OnPlayerLeave(m_name);
			removeGame(m_currentGame);
			LANGameInfo *game = m_currentGame;
			m_currentGame = NULL;
			m_inLobby = TRUE;
			if (TheNetwork != NULL)
			{
				delete TheNetwork;
				TheNetwork = NULL;
			}
			MessageBoxOk(TheGameText->fetch("GUI:ErrorStartingGame"),
				TheGameText->fetch("GUI:CouldNotTransferMap"), NULL);
			OnChat(UnicodeString::TheEmptyString, 0,
				TheGameText->fetch("GUI:CouldNotTransferMap"), 2);
			(void)game;
			return;
		}

		TheWritableGlobalData->m_pendingFile = m_currentGame->getMap();
		GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_NEW_GAME);
		msg->appendIntegerArgument(GAME_LAN);
		InitGameLogicRandom(m_currentGame->getSeed());
	}
}
