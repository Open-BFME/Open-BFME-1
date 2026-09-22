// ?_bfme_cacheLocalPlayerStatsWithLocale@@YAXXZ
// partial score=0.69 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "../../../../../reference/shims/stringinline/StringInline.h"
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
		Int localID = ((Rva0055CD80GameSpyInfo *)TheGameSpyInfo)->getLocalProfileID();
		if (localID)
		{
			PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(localID);
			GameSpyMiscPreferences mPref;
			if (stats.id)
			{
				stats.locale = mPref.getLocale();
				TheGameSpyPSMessageQueue->trackPlayerStats(stats);
				PSPlayerStats refreshed = TheGameSpyPSMessageQueue->findPlayerStatsByID(
					((Rva0055CD80GameSpyInfo *)TheGameSpyInfo)->getLocalProfileID());
				if (refreshed.id)
				{
					mPref.setCachedStats(
						GameSpyPSMessageQueueInterface::formatPlayerKVPairs(refreshed).c_str());
					mPref.write();
					((Rva0055CD80GameSpyInfo *)TheGameSpyInfo)->setCachedLocalPlayerStats(refreshed);
				}
			}
		}
	}
}
