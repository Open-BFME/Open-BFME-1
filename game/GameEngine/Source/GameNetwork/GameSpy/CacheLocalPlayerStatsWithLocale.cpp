// ?_bfme_cacheLocalPlayerStatsWithLocale@@YAXXZ
// Retail 0x0055CD80 (452 bytes), reached through ILT 0x0003CC54 from 0x00547761 and 0x00554AC2.
// GameSpyInfo vtable 0x011188D0: +0x70 returns [this+0x70], +0x8C is setCachedLocalPlayerStats (ret 0x1C4).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "../../../../../inputs/reference/shims/stringinline/StringInline.h"
#include <string>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class PSPlayerStats
{
public:
	PSPlayerStats(const PSPlayerStats &other);
	~PSPlayerStats();

	Int id;
	char m_beforeLocale[0x144];
	Int locale;
	char m_afterLocale[0x78];
};
typedef char PSPlayerStatsSizeCheck[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual Bool isThreadRunning();
	virtual void addRequest(const void *request);
	virtual Bool getRequest(void *request);
	virtual void addResponse(const void *response);
	virtual Bool getResponse(void *response);
	virtual void trackPlayerStats(PSPlayerStats stats);
	virtual PSPlayerStats findPlayerStatsByID(Int profileID);
	static std::string formatPlayerKVPairs(PSPlayerStats stats);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

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
	Int getLocale();
	void setCachedStats(AsciiString value);
};

class Rva0055CD80GameSpyInfo
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual Int getLocalProfileID();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void setCachedLocalPlayerStats(PSPlayerStats stats);
};

extern Rva0055CD80GameSpyInfo *TheGameSpyInfo;


void _bfme_cacheLocalPlayerStatsWithLocale()
{
	if (TheGameSpyInfo)
	{
		Int localID = TheGameSpyInfo->getLocalProfileID();
		if (localID)
		{
			PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(localID);
			GameSpyMiscPreferences mPref;
			if (stats.id == 0)
				return;
			stats.locale = mPref.getLocale();
			TheGameSpyPSMessageQueue->trackPlayerStats(stats);
			PSPlayerStats refreshed = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
			if (refreshed.id)
			{
				mPref.setCachedStats(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(refreshed).c_str());
				mPref.write();
				TheGameSpyInfo->setCachedLocalPlayerStats(refreshed);
			}
		}
	}
}
