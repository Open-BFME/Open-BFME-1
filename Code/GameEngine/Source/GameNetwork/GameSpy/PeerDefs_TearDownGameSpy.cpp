// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Real607B teardown ends with ret at6335EE (exclusive6335EF).
// Named WOLLoginMenuUpdate/WOLLobbyMenuUpdate and SetUpGameSpy call it.
// Matched GameSpyInfo ctor636D90 installs vtableVA11188D0: +70 is
// ILT43B12->637120 (profile ID at+70); +14C is ILT1B6EE->6371A0
// (internal IP at+248). Raw SetUpGameSpy637A64 calls ILT37155 to the
// actual206B RankPoints ctor4DAFA0 after allocating0x30 bytes.
// All singleton ownership and by-value string/stat lifetimes are retained.

#include "../../../../../reference/shims/stringinline/StringInline.h"
#include <string>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGOUT = 0x13 };

class PSPlayerStats
{
public:
	PSPlayerStats( const PSPlayerStats &other );
	~PSPlayerStats();

	Int id;
	char m_unmodelled[0x1c0];
};
typedef char PSPlayerStatsSizeCheck[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

class GameSpyInfoInterface
{
public:
	virtual ~GameSpyInfoInterface();
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual Bool isThreadRunning();
	virtual void addRequest( const void *request );
	virtual Bool getRequest( void *request );
	virtual void addResponse( const void *response );
	virtual Bool getResponse( void *response );
	virtual void trackPlayerStats( PSPlayerStats stats );
	virtual PSPlayerStats findPlayerStatsByID( Int profileID );
	static std::string formatPlayerKVPairs( PSPlayerStats stats );
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class PingerInterface
{
public:
	virtual ~PingerInterface();
	virtual void startThreads();
	virtual void endThreads();
};
extern PingerInterface *ThePinger;

// SetUpGameSpy6377D0 allocates0x30 at+27B and stores the constructed
// RankPoints in VA12F401C; matched CalculateRank4DA530 reads multipliers
// at+28/+2C. All fields are scalar, so deletion has no destructor call.
struct RankPoints
{
	int m_ranks[10];
	float m_winMultiplier;
	float m_lostMultiplier;
};
typedef char RankPointsSize30[(sizeof(RankPoints) == 0x30) ? 1 : -1];
extern RankPoints *TheRankPointValues;

struct BfmePreferenceMap
{
	char m_tree[12];
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual Bool write();

private:
	BfmePreferenceMap m_preferences;
	AsciiString m_filename;
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
	void setCachedStats( AsciiString val );
};

class LadderList
{
public:
	~LadderList();
};
extern LadderList *TheLadderList;

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface();
};
extern GameSpyConfigInterface *TheGameSpyConfig;

extern void SignalUIInteraction( Int interaction );
extern void deleteNotificationBox( void );

// BFME's GameSpyInfo vtable has seven slots before getLocalProfileID and four
// net additional slots before getInternalIP relative to the shared interface
// view.  This declaration-only view is used only for the two retail calls in
// TearDownGameSpy; ownership and deletion remain on the real global type.
class BfmeGameSpyInfoTeardownView
{
public:
#define BFME_GSI_TEARDOWN_SLOT(n) virtual void slot##n( void ) = 0;
	BFME_GSI_TEARDOWN_SLOT(00)
	BFME_GSI_TEARDOWN_SLOT(01)
	BFME_GSI_TEARDOWN_SLOT(02)
	BFME_GSI_TEARDOWN_SLOT(03)
	BFME_GSI_TEARDOWN_SLOT(04)
	BFME_GSI_TEARDOWN_SLOT(05)
	BFME_GSI_TEARDOWN_SLOT(06)
	BFME_GSI_TEARDOWN_SLOT(07)
	BFME_GSI_TEARDOWN_SLOT(08)
	BFME_GSI_TEARDOWN_SLOT(09)
	BFME_GSI_TEARDOWN_SLOT(10)
	BFME_GSI_TEARDOWN_SLOT(11)
	BFME_GSI_TEARDOWN_SLOT(12)
	BFME_GSI_TEARDOWN_SLOT(13)
	BFME_GSI_TEARDOWN_SLOT(14)
	BFME_GSI_TEARDOWN_SLOT(15)
	BFME_GSI_TEARDOWN_SLOT(16)
	BFME_GSI_TEARDOWN_SLOT(17)
	BFME_GSI_TEARDOWN_SLOT(18)
	BFME_GSI_TEARDOWN_SLOT(19)
	BFME_GSI_TEARDOWN_SLOT(20)
	BFME_GSI_TEARDOWN_SLOT(21)
	BFME_GSI_TEARDOWN_SLOT(22)
	BFME_GSI_TEARDOWN_SLOT(23)
	BFME_GSI_TEARDOWN_SLOT(24)
	BFME_GSI_TEARDOWN_SLOT(25)
	BFME_GSI_TEARDOWN_SLOT(26)
	BFME_GSI_TEARDOWN_SLOT(27)
	virtual Int getLocalProfileID( void ) = 0;
	BFME_GSI_TEARDOWN_SLOT(29)
	BFME_GSI_TEARDOWN_SLOT(30)
	BFME_GSI_TEARDOWN_SLOT(31)
	BFME_GSI_TEARDOWN_SLOT(32)
	BFME_GSI_TEARDOWN_SLOT(33)
	BFME_GSI_TEARDOWN_SLOT(34)
	BFME_GSI_TEARDOWN_SLOT(35)
	BFME_GSI_TEARDOWN_SLOT(36)
	BFME_GSI_TEARDOWN_SLOT(37)
	BFME_GSI_TEARDOWN_SLOT(38)
	BFME_GSI_TEARDOWN_SLOT(39)
	BFME_GSI_TEARDOWN_SLOT(40)
	BFME_GSI_TEARDOWN_SLOT(41)
	BFME_GSI_TEARDOWN_SLOT(42)
	BFME_GSI_TEARDOWN_SLOT(43)
	BFME_GSI_TEARDOWN_SLOT(44)
	BFME_GSI_TEARDOWN_SLOT(45)
	BFME_GSI_TEARDOWN_SLOT(46)
	BFME_GSI_TEARDOWN_SLOT(47)
	BFME_GSI_TEARDOWN_SLOT(48)
	BFME_GSI_TEARDOWN_SLOT(49)
	BFME_GSI_TEARDOWN_SLOT(50)
	BFME_GSI_TEARDOWN_SLOT(51)
	BFME_GSI_TEARDOWN_SLOT(52)
	BFME_GSI_TEARDOWN_SLOT(53)
	BFME_GSI_TEARDOWN_SLOT(54)
	BFME_GSI_TEARDOWN_SLOT(55)
	BFME_GSI_TEARDOWN_SLOT(56)
	BFME_GSI_TEARDOWN_SLOT(57)
	BFME_GSI_TEARDOWN_SLOT(58)
	BFME_GSI_TEARDOWN_SLOT(59)
	BFME_GSI_TEARDOWN_SLOT(60)
	BFME_GSI_TEARDOWN_SLOT(61)
	BFME_GSI_TEARDOWN_SLOT(62)
	BFME_GSI_TEARDOWN_SLOT(63)
	BFME_GSI_TEARDOWN_SLOT(64)
	BFME_GSI_TEARDOWN_SLOT(65)
	BFME_GSI_TEARDOWN_SLOT(66)
	BFME_GSI_TEARDOWN_SLOT(67)
	BFME_GSI_TEARDOWN_SLOT(68)
	BFME_GSI_TEARDOWN_SLOT(69)
	BFME_GSI_TEARDOWN_SLOT(70)
	BFME_GSI_TEARDOWN_SLOT(71)
	BFME_GSI_TEARDOWN_SLOT(72)
	BFME_GSI_TEARDOWN_SLOT(73)
	BFME_GSI_TEARDOWN_SLOT(74)
	BFME_GSI_TEARDOWN_SLOT(75)
	BFME_GSI_TEARDOWN_SLOT(76)
	BFME_GSI_TEARDOWN_SLOT(77)
	BFME_GSI_TEARDOWN_SLOT(78)
	BFME_GSI_TEARDOWN_SLOT(79)
	BFME_GSI_TEARDOWN_SLOT(80)
	BFME_GSI_TEARDOWN_SLOT(81)
	BFME_GSI_TEARDOWN_SLOT(82)
	virtual UnsignedInt getInternalIP( void ) = 0;
#undef BFME_GSI_TEARDOWN_SLOT
};

void TearDownGameSpy( void )
{
	// save off cached stats
	if (TheGameSpyInfo && reinterpret_cast<BfmeGameSpyInfoTeardownView *>(TheGameSpyInfo)->getLocalProfileID())
	{
		PSPlayerStats localPSStats = TheGameSpyPSMessageQueue->findPlayerStatsByID(reinterpret_cast<BfmeGameSpyInfoTeardownView *>(TheGameSpyInfo)->getLocalProfileID());
		if (localPSStats.id != 0)
		{
			GameSpyMiscPreferences mPref;
			mPref.setCachedStats(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(localPSStats).c_str());
			mPref.write();
		}
	}

	// End our threads before we kill off the singletons they reference.
	if (TheGameSpyPSMessageQueue)
		TheGameSpyPSMessageQueue->endThread();
	if (TheGameSpyBuddyMessageQueue)
		TheGameSpyBuddyMessageQueue->endThread();
	if (TheGameSpyPeerMessageQueue)
		TheGameSpyPeerMessageQueue->endThread();
	if (ThePinger)
		ThePinger->endThreads();

	if (TheRankPointValues)
	{
		delete TheRankPointValues;
		TheRankPointValues = NULL;
	}
	if (TheGameSpyPSMessageQueue)
	{
		delete TheGameSpyPSMessageQueue;
		TheGameSpyPSMessageQueue = NULL;
	}

	if (TheGameSpyBuddyMessageQueue)
	{
		delete TheGameSpyBuddyMessageQueue;
		TheGameSpyBuddyMessageQueue = NULL;
	}

	if (TheGameSpyPeerMessageQueue)
	{
		delete TheGameSpyPeerMessageQueue;
		TheGameSpyPeerMessageQueue = NULL;
	}

	if (TheGameSpyInfo)
	{
		if (reinterpret_cast<BfmeGameSpyInfoTeardownView *>(TheGameSpyInfo)->getInternalIP())
			SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGOUT);
		delete TheGameSpyInfo;
		TheGameSpyInfo = NULL;
	}

	if (ThePinger)
	{
		delete ThePinger;
		ThePinger = NULL;
	}

	if (TheLadderList)
	{
		delete TheLadderList;
		TheLadderList = NULL;
	}

	if (TheGameSpyConfig)
	{
		delete TheGameSpyConfig;
		TheGameSpyConfig = NULL;
	}

	deleteNotificationBox();
}
