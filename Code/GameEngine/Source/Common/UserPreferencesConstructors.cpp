// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"

#include "Common/CustomMatchPreferences.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/IgnorePreferences.h"
#include "Common/LadderPreferences.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

class BfmeGameSpyInfoLocalProfileView
{
public:
	virtual void unused00() = 0, unused01() = 0, unused02() = 0, unused03() = 0;
	virtual void unused04() = 0, unused05() = 0, unused06() = 0, unused07() = 0;
	virtual void unused08() = 0, unused09() = 0, unused10() = 0, unused11() = 0;
	virtual void unused12() = 0, unused13() = 0, unused14() = 0, unused15() = 0;
	virtual void unused16() = 0, unused17() = 0, unused18() = 0, unused19() = 0;
	virtual void unused20() = 0, unused21() = 0, unused22() = 0, unused23() = 0;
	virtual void unused24() = 0, unused25() = 0, unused26() = 0, unused27() = 0;
	virtual Int getLocalProfileID() = 0;
};

UserPreferences::UserPreferences( void )
{
}

QuickMatchPreferences::QuickMatchPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\QMPref%d.ini", localProfile);
	load(userPrefFilename);
}

CustomMatchPreferences::CustomMatchPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\CustomPref%d.ini", localProfile);
	load(userPrefFilename);
}

GameSpyMiscPreferences::GameSpyMiscPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\GSMiscPref%d.ini", localProfile);
	load(userPrefFilename);
}

IgnorePreferences::IgnorePreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\IgnorePref%d.ini", localProfile);
	load(userPrefFilename);
}

LadderPreferences::LadderPreferences()
{
}
