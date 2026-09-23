// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/gameinfo /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// stlport
// BfmeAptScreenLanLobby secondary-vtable slot 6 at 0x00517B60.
// The address-derived name preserves the unknown semantic method identity.
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameInfo.h"

struct TransportAddress
{
	TransportAddress() : m_ip( 0 ), m_port( 0 ) {}
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANGameInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual Int getLocalSlotNum() const;
	virtual void resetAccepted();
};

class LANAPI
{
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
	virtual void RequestGameOptions( AsciiString options, bool isPublic,
		const TransportAddress &address = TransportAddress() );
	virtual void requestSerializedGameInfo( bool unused, void *destination );
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void OnPlayerLeave( UnicodeString player );
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual LANGameInfo *GetMyGame();
};

extern LANAPI *TheLAN;

class BfmeAptScreenLanLobby
{
public:
	bool rva00517B60( GameSlot *slot, SlotState state, Int unused );
};

bool BfmeAptScreenLanLobby::rva00517B60(
	GameSlot *slot, SlotState state, Int unused )
{
	if( !TheLAN )
		return false;

	LANGameInfo *game = TheLAN->GetMyGame();
	if( !game )
		return false;

	GameSlotConnectInfo info;
	if( slot->getState() == SLOT_PLAYER )
	{
		UnicodeString player = slot->getName();
		info.m_nat = FirewallHelperClass::FIREWALL_TYPE_UNKNOWN;
		info.m_port = 0;
		slot->setState( state, UnicodeString::TheEmptyString, &info );
		game->resetAccepted();
		TheLAN->OnPlayerLeave( player );
	}
	else
	{
		bool wasAI = slot->isAI();
		info.m_nat = FirewallHelperClass::FIREWALL_TYPE_UNKNOWN;
		info.m_port = 0;
		slot->setState( state, UnicodeString::TheEmptyString, &info );
		bool isAI = slot->isAI();
		if( wasAI || isAI )
			game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo( true, &address );
	}
	return true;
}
