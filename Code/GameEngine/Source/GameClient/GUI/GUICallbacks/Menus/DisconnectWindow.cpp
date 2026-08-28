// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib

class BFMEDisconnectWindowLayout
{
public:
	virtual void runInit( void *userData );
	virtual ~BFMEDisconnectWindowLayout();
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
};

#define BFME_INGAME_UI_SLOT(n) virtual void slot##n();
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	BFME_INGAME_UI_SLOT(0) BFME_INGAME_UI_SLOT(1) BFME_INGAME_UI_SLOT(2) BFME_INGAME_UI_SLOT(3)
	BFME_INGAME_UI_SLOT(4) BFME_INGAME_UI_SLOT(5) BFME_INGAME_UI_SLOT(6) BFME_INGAME_UI_SLOT(7)
	BFME_INGAME_UI_SLOT(8) BFME_INGAME_UI_SLOT(9) BFME_INGAME_UI_SLOT(10) BFME_INGAME_UI_SLOT(11)
	BFME_INGAME_UI_SLOT(12) BFME_INGAME_UI_SLOT(13) BFME_INGAME_UI_SLOT(14) BFME_INGAME_UI_SLOT(15)
	BFME_INGAME_UI_SLOT(16) BFME_INGAME_UI_SLOT(17) BFME_INGAME_UI_SLOT(18) BFME_INGAME_UI_SLOT(19)
	BFME_INGAME_UI_SLOT(20) BFME_INGAME_UI_SLOT(21) BFME_INGAME_UI_SLOT(22) BFME_INGAME_UI_SLOT(23)
	BFME_INGAME_UI_SLOT(24) BFME_INGAME_UI_SLOT(25) BFME_INGAME_UI_SLOT(26) BFME_INGAME_UI_SLOT(27)
	BFME_INGAME_UI_SLOT(28) BFME_INGAME_UI_SLOT(29) BFME_INGAME_UI_SLOT(30) BFME_INGAME_UI_SLOT(31)
	BFME_INGAME_UI_SLOT(32) BFME_INGAME_UI_SLOT(33) BFME_INGAME_UI_SLOT(34) BFME_INGAME_UI_SLOT(35)
	BFME_INGAME_UI_SLOT(36) BFME_INGAME_UI_SLOT(37) BFME_INGAME_UI_SLOT(38) BFME_INGAME_UI_SLOT(39)
	BFME_INGAME_UI_SLOT(40) BFME_INGAME_UI_SLOT(41) BFME_INGAME_UI_SLOT(42) BFME_INGAME_UI_SLOT(43)
	BFME_INGAME_UI_SLOT(44) BFME_INGAME_UI_SLOT(45) BFME_INGAME_UI_SLOT(46) BFME_INGAME_UI_SLOT(47)
	BFME_INGAME_UI_SLOT(48) BFME_INGAME_UI_SLOT(49) BFME_INGAME_UI_SLOT(50) BFME_INGAME_UI_SLOT(51)
	BFME_INGAME_UI_SLOT(52) BFME_INGAME_UI_SLOT(53) BFME_INGAME_UI_SLOT(54) BFME_INGAME_UI_SLOT(55)
	BFME_INGAME_UI_SLOT(56) BFME_INGAME_UI_SLOT(57) BFME_INGAME_UI_SLOT(58) BFME_INGAME_UI_SLOT(59)
	BFME_INGAME_UI_SLOT(60) BFME_INGAME_UI_SLOT(61) BFME_INGAME_UI_SLOT(62) BFME_INGAME_UI_SLOT(63)
	BFME_INGAME_UI_SLOT(64) BFME_INGAME_UI_SLOT(65) BFME_INGAME_UI_SLOT(66) BFME_INGAME_UI_SLOT(67)
	BFME_INGAME_UI_SLOT(68) BFME_INGAME_UI_SLOT(69) BFME_INGAME_UI_SLOT(70) BFME_INGAME_UI_SLOT(71)
	BFME_INGAME_UI_SLOT(72) BFME_INGAME_UI_SLOT(73) BFME_INGAME_UI_SLOT(74) BFME_INGAME_UI_SLOT(75)
	BFME_INGAME_UI_SLOT(76) BFME_INGAME_UI_SLOT(77) BFME_INGAME_UI_SLOT(78) BFME_INGAME_UI_SLOT(79)
	BFME_INGAME_UI_SLOT(80) BFME_INGAME_UI_SLOT(81) BFME_INGAME_UI_SLOT(82) BFME_INGAME_UI_SLOT(83)
	virtual void setQuitMenuVisible( bool visible );
};
#undef BFME_INGAME_UI_SLOT

static BFMEDisconnectWindowLayout *disconnectMenuLayout;
extern InGameUI *TheInGameUI;

void HideDisconnectWindow( void )
{
	if (disconnectMenuLayout != 0)
	{
		disconnectMenuLayout->runShutdown( 0 );
		if (disconnectMenuLayout != 0)
			delete disconnectMenuLayout;
		// The published layout must be cleared before the UI observes that the menu closed.
		*reinterpret_cast<BFMEDisconnectWindowLayout * volatile *>( &disconnectMenuLayout ) = 0;
		TheInGameUI->setQuitMenuVisible( false );
	}
}
