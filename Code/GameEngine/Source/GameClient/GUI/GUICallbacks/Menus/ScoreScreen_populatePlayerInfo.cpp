// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/stringbaseunicode /Ireference/shims/psplayerstats /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// BFME populatePlayerInfo, RVA 0x004E5DF0, including its owned switch table.
// Identity: ILT 0x000074B4; callers 0x004E8237 and 0x004E8393;
// Zero Hour ScoreScreen.cpp:1396 and eleven ScoreScreen.wnd child identifiers.
// This TU isolates BFME layouts from the ZH declarations of ScoreScreen.cpp,
// whose existing 17 claims remain untouched. Witnesses: build/unclaimed_map/astra_B/LAYOUTS.md.
// The native stats view is the independently recovered PersistentStorageThread
// layout; its field order differs from the compatibility PSPlayerStats shim.
// updateMPBattleHonors and StringBase::isNotEmpty are the existing natural C++
// bodies, also individually byte-verified, so the compiler can see their ABI/EH.
#include <map>
#include <string>
#include "Lib/BaseType.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#define PSRequest Rva004E5DF0ReferencePSRequest
#define PSResponse Rva004E5DF0ReferencePSResponse
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#undef PSRequest
#undef PSResponse
#undef max
typedef Int Color;
template<> inline bool StringBase<char>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
template<> __declspec(noinline) bool StringBase<char>::isNotEmpty() const
{
    return !isEmpty();
}

#define TRUE true
#define FALSE false
const Int MAX_SLOTS=8;
enum { SCORESCREEN_SINGLEPLAYER, SCORESCREEN_SKIRMISH, SCORESCREEN_LAN, SCORESCREEN_INTERNET, SCORESCREEN_REPLAY };
enum { PLAYERTEMPLATE_RANDOM=-1, PLAYERTEMPLATE_OBSERVER=-2 };
template<class T> inline const T& max(const T& a,const T& b) { return a>b?a:b; }
template<class T> inline const T& rvaField(const void* p,unsigned n) { return *(const T*)((const char*)p+n); }
class Image;
class GameWindow
{
public:
    Int winHide(Bool);
    Int winGetEnabledTextBorderColor();
    void winSetEnabledTextColors(Int,Int);
    void winSetEnabledImage(Int,const Image*);
};
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char*);
    NameKeyType nameToKey(const AsciiString& name) { return nameToKey(name.str()); }
};
class ScoreKeeper
{
public:
    Int rva0000;
    Int moneyEarned;
    char rva0008[0x84];
    Int unitsBuilt, unitsLost;
    char rva0094[0x80];
    Int buildingsBuilt, buildingsLost;
    Int getTotalUnitsBuilt() {return unitsBuilt;}
    Int getTotalUnitsLost() {return unitsLost;}
    Int getTotalUnitsDestroyed();
    Int getTotalBuildingsBuilt() {return buildingsBuilt;}
    Int getTotalBuildingsLost() {return buildingsLost;}
    Int getTotalBuildingsDestroyed();
    Int getTotalMoneyEarned() {return moneyEarned;}
};
class PlayerTemplate
{
public:
    const AsciiString& getSide() const {return rvaField<AsciiString>(this,8);}
    const Image* getSideIconImage() const;
};
class Player
{
public:
    Int getPlayerColor() const {return rvaField<Int>(this,0x1c4);}
    ScoreKeeper* getScoreKeeper() {return (ScoreKeeper*)((char*)this+0x348);}
    const PlayerTemplate* getPlayerTemplate() const {return rvaField<const PlayerTemplate*>(this,4);}
    UnicodeString getPlayerDisplayName();
    Bool isLocalPlayer() const;
    Bool isPlayerActive() const;
};
enum SlotState {SLOT_OPEN,SLOT_CLOSED,SLOT_EASY_AI,SLOT_MED_AI,SLOT_BRUTAL_AI,SLOT_PLAYER};
class GameSlot
{
public:
    SlotState getState() const {return rvaField<SlotState>(this,4);}
    Bool isOccupied() const;
    Bool isAI() const;
    Bool isHuman() const;
    Bool disconnected() const;
    UnsignedInt lastFrameInGame() const {return rvaField<UnsignedInt>(this,0x3c);}
    Int getPlayerTemplate() const {return rvaField<Int>(this,0x14);}
    Int getOriginalPlayerTemplate() const {return rvaField<Int>(this,0x24);}
};
class GameSpyGameSlot:public GameSlot {};
class GameInfo
{
public:
    virtual void rvaSlot0()=0; virtual void rvaSlot4()=0; virtual void rvaSlot8()=0;
    virtual void rvaSlotC()=0; virtual void rvaSlot10()=0;
    virtual Int getLocalSlotNum()=0;
    virtual void rvaSlot18()=0; virtual void rvaSlot1C()=0; virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0; virtual void rvaSlot28()=0; virtual void rvaSlot2C()=0;
    virtual Bool isSandbox()=0;
    const GameSlot* getConstSlot(Int) const;
    Int _bfme_getMapIsOfficial() const;
    Bool haveWeSurrendered() const {return rvaField<Bool>(this,0xe);}
};
class GameSpyStagingRoom:public GameInfo
{
public:
    GameSpyGameSlot* getGameSpySlot(Int);
    AsciiString getLadderIP() const;
    UnsignedShort getLadderPort() const {return rvaField<UnsignedShort>(this,0x450);}
    Bool isQMGame() const {return rvaField<Bool>(this,0x43c);}
    AsciiString generateLadderGameResultsPacket();
    AsciiString generateGameSpyGameResultsPacket(Bool);
};
class PlayerTemplateStore
{
public:
    const PlayerTemplate* getNthPlayerTemplate(Int) const;
    Int getPlayerTemplateCount() const {return (rvaField<const char*>(this,0xc)-rvaField<const char*>(this,8))/0x124;}
};
class GameLogic
{
public:
    Bool sawCRCMismatch() const {return rvaField<Bool>(this,0x6c);}
    UnsignedInt getFrame() const {return rvaField<UnsignedInt>(this,0x3c);}
};
class GameResultsRequest
{
public:
    GameResultsRequest();
    ~GameResultsRequest();
    std::string hostname;
    UnsignedShort port;
    std::string results;
};
class PSRequest
{
public:
    PSRequest();
    enum {PSREQUEST_READPLAYERSTATS,PSREQUEST_UPDATEPLAYERSTATS,PSREQUEST_UPDATEPLAYERLOCALE,PSREQUEST_READCDKEYSTATS,PSREQUEST_SENDGAMERESTOGAMESPY} requestType;
    PSPlayerStats player;
    std::string cdkey,nick,password,email;
    Bool addDiscon,addDesync;
    Int lastHouse;
    Int rva0200;
    std::string results;
};
// deque cursor stride at 00656BD0 is 0x1F0. The stats subobject at +4 is
// independently 0x1C4; remaining response payload is intentionally opaque.
class PSResponse
{
public:
    enum {PSRESPONSE_PLAYERSTATS,PSRESPONSE_COULDNOTCONNECT,PSRESPONSE_PREORDER} responseType;
    PSPlayerStats player;
    char rva01c8[0x28];
};
class Rva004E5DF0Queue
{
public:
    virtual void rvaSlot0()=0; virtual void rvaSlot4()=0; virtual void rvaSlot8()=0; virtual void rvaSlotC()=0;
    virtual void addRequest(const PSRequest&)=0;
    virtual Bool getRequest(PSRequest&)=0;
    virtual void addResponse(const PSResponse&)=0;
    virtual Bool getResponse(PSResponse&)=0;
    virtual void trackPlayerStats(PSPlayerStats)=0;
    virtual PSPlayerStats findPlayerStatsByID(Int)=0;
};
class SkirmishPreferences
{
public:
    SkirmishPreferences(); virtual ~SkirmishPreferences();
    UnicodeString getUserName();
    char rva0004[0x18];
};
class SkirmishBattleHonors
{
public:
    SkirmishBattleHonors(UnicodeString); virtual ~SkirmishBattleHonors();
    char rva0004[0x38];
    Real getTimePlayed(AsciiString) const; void setTimePlayed(AsciiString,Real);
    Int getPoints(AsciiString) const; void setPoints(AsciiString,Int);
    Int getWins(AsciiString) const; void setWins(AsciiString,Int);
    Int getLosses(AsciiString) const; void setLosses(AsciiString,Int);
    Int getWinStreak(AsciiString) const; void setWinStreak(AsciiString,Int);
    Int getBestWinStreak(AsciiString) const; void setBestWinStreak(AsciiString,Int);
    Int getLossStreak(AsciiString) const; void setLossStreak(AsciiString,Int);
    Int getWorstLossStreak(AsciiString) const; void setWorstLossStreak(AsciiString,Int);
    Int getOverallWinStreak() const; void setOverallWinStreak(Int);
    Int getOverallBestWinStreak() const; void setOverallBestWinStreak(Int);
    Int getOverallLossStreak() const; void setOverallLossStreak(Int);
    Int getOverallWorstLossStreak() const; void setOverallWorstLossStreak(Int);
    Int getChallengeMedals() const; void setChallengeMedals(Int);
    AsciiString getLastGeneral() const; void setLastGeneral(AsciiString);
    Int getNumGamesLoyal() const; void setNumGamesLoyal(Int);
    virtual Bool write();
};
class UserPreferences {public: virtual ~UserPreferences(); virtual Bool write(); char rva0004[0x10];};
class GameSpyMiscPreferences: public UserPreferences
{
public:
    GameSpyMiscPreferences(); virtual ~GameSpyMiscPreferences();
    void setCachedStats(AsciiString);
};
class OptionPreferences {public: Int getIdealStaticGameDetail();};

extern GameWindow* Rva012F415C;
extern Bool Rva012F4180;
extern Int Rva012F4134;
extern NameKeyGenerator* TheNameKeyGenerator;
extern GameInfo* TheGameInfo;
extern GameSpyStagingRoom* TheGameSpyGame;
extern GameLogic* TheGameLogic;
extern PlayerTemplateStore* ThePlayerTemplateStore;
extern OptionPreferences* Rva012ED5AC;
void GadgetStaticTextSetText(GameWindow*,UnicodeString);
void updateChallengeMedals(Int&);
static void updateMPBattleHonors(Int&,PSPlayerStats&);
class GameWindowManager { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void rvaSlot30()=0;
    virtual void rvaSlot34()=0;
    virtual void rvaSlot38()=0;
    virtual void rvaSlot3C()=0;
    virtual void rvaSlot40()=0;
    virtual void rvaSlot44()=0;
    virtual void rvaSlot48()=0;
    virtual void rvaSlot4C()=0;
    virtual void rvaSlot50()=0;
    virtual void rvaSlot54()=0;
    virtual void rvaSlot58()=0;
    virtual void rvaSlot5C()=0;
    virtual void rvaSlot60()=0;
    virtual void rvaSlot64()=0;
    virtual void rvaSlot68()=0;
    virtual void rvaSlot6C()=0;
    virtual void rvaSlot70()=0;
    virtual void rvaSlot74()=0;
    virtual void rvaSlot78()=0;
    virtual void rvaSlot7C()=0;
    virtual void rvaSlot80()=0;
    virtual void rvaSlot84()=0;
    virtual void rvaSlot88()=0;
    virtual void rvaSlot8C()=0;
    virtual void rvaSlot90()=0;
    virtual void rvaSlot94()=0;
    virtual void rvaSlot98()=0;
    virtual void rvaSlot9C()=0;
    virtual void rvaSlotA0()=0;
    virtual void rvaSlotA4()=0;
    virtual void rvaSlotA8()=0;
    virtual void rvaSlotAC()=0;
    virtual void rvaSlotB0()=0;
    virtual void rvaSlotB4()=0;
    virtual void rvaSlotB8()=0;
    virtual void rvaSlotBC()=0;
    virtual void rvaSlotC0()=0;
    virtual void rvaSlotC4()=0;
    virtual void rvaSlotC8()=0;
    virtual void rvaSlotCC()=0;
    virtual void rvaSlotD0()=0;
    virtual void rvaSlotD4()=0;
    virtual void rvaSlotD8()=0;
    virtual GameWindow* winGetWindowFromId(GameWindow*,NameKeyType)=0;
};
class GameText { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual UnicodeString fetch(const char*,Bool* = 0)=0;
};
class VictoryConditions { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void rvaSlot30()=0;
    virtual Bool isLocalAlliedVictory()=0;
    virtual Bool isLocalAlliedDefeat()=0;
    virtual Bool isLocalDefeat()=0;
    virtual Bool amIObserver()=0;
    virtual UnsignedInt getEndFrame()=0;
};
class NetworkInterface { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void rvaSlot30()=0;
    virtual void rvaSlot34()=0;
    virtual void rvaSlot38()=0;
    virtual void rvaSlot3C()=0;
    virtual void rvaSlot40()=0;
    virtual void rvaSlot44()=0;
    virtual void rvaSlot48()=0;
    virtual void rvaSlot4C()=0;
    virtual void rvaSlot50()=0;
    virtual void rvaSlot54()=0;
    virtual void rvaSlot58()=0;
    virtual void rvaSlot5C()=0;
    virtual void rvaSlot60()=0;
    virtual void rvaSlot64()=0;
    virtual void rvaSlot68()=0;
    virtual void rvaSlot6C()=0;
    virtual void rvaSlot70()=0;
    virtual void rvaSlot74()=0;
    virtual void rvaSlot78()=0;
    virtual void rvaSlot7C()=0;
    virtual UnsignedInt getPingFrame()=0;
    virtual Int getPingsSent()=0;
    virtual Int getPingsRecieved()=0;
};
class Rva004E5DF0GameSpyInfo { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void rvaSlot30()=0;
    virtual void rvaSlot34()=0;
    virtual void rvaSlot38()=0;
    virtual void rvaSlot3C()=0;
    virtual void rvaSlot40()=0;
    virtual void rvaSlot44()=0;
    virtual void rvaSlot48()=0;
    virtual void rvaSlot4C()=0;
    virtual void rvaSlot50()=0;
    virtual void rvaSlot54()=0;
    virtual void rvaSlot58()=0;
    virtual void rvaSlot5C()=0;
    virtual void rvaSlot60()=0;
    virtual void rvaSlot64()=0;
    virtual void rvaSlot68()=0;
    virtual void rvaSlot6C()=0;
    virtual Int getLocalProfileID()=0;
    virtual AsciiString getLocalEmail()=0;
    virtual void rvaSlot78()=0;
    virtual AsciiString getLocalPassword()=0;
    virtual void rvaSlot80()=0;
    virtual void rvaSlot84()=0;
    virtual AsciiString getLocalBaseName()=0;
};
class GameResultsInterface { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void addRequest(const GameResultsRequest&)=0;
};
class Display { public:
    virtual void rvaSlot00()=0;
    virtual void rvaSlot04()=0;
    virtual void rvaSlot08()=0;
    virtual void rvaSlot0C()=0;
    virtual void rvaSlot10()=0;
    virtual void rvaSlot14()=0;
    virtual void rvaSlot18()=0;
    virtual void rvaSlot1C()=0;
    virtual void rvaSlot20()=0;
    virtual void rvaSlot24()=0;
    virtual void rvaSlot28()=0;
    virtual void rvaSlot2C()=0;
    virtual void rvaSlot30()=0;
    virtual void rvaSlot34()=0;
    virtual void rvaSlot38()=0;
    virtual void rvaSlot3C()=0;
    virtual void rvaSlot40()=0;
    virtual void rvaSlot44()=0;
    virtual void rvaSlot48()=0;
    virtual void rvaSlot4C()=0;
    virtual void rvaSlot50()=0;
    virtual void rvaSlot54()=0;
    virtual void rvaSlot58()=0;
    virtual void rvaSlot5C()=0;
    virtual void rvaSlot60()=0;
    virtual void rvaSlot64()=0;
    virtual void rvaSlot68()=0;
    virtual void rvaSlot6C()=0;
    virtual void rvaSlot70()=0;
    virtual void rvaSlot74()=0;
    virtual void rvaSlot78()=0;
    virtual void rvaSlot7C()=0;
    virtual void rvaSlot80()=0;
    virtual void rvaSlot84()=0;
    virtual void rvaSlot88()=0;
    virtual void rvaSlot8C()=0;
    virtual void rvaSlot90()=0;
    virtual void rvaSlot94()=0;
    virtual void rvaSlot98()=0;
    virtual void rvaSlot9C()=0;
    virtual void rvaSlotA0()=0;
    virtual void rvaSlotA4()=0;
    virtual void rvaSlotA8()=0;
    virtual void rvaSlotAC()=0;
    virtual void rvaSlotB0()=0;
    virtual void rvaSlotB4()=0;
    virtual void rvaSlotB8()=0;
    virtual void rvaSlotBC()=0;
    virtual void rvaSlotC0()=0;
    virtual void rvaSlotC4()=0;
    virtual void rvaSlotC8()=0;
    virtual void rvaSlotCC()=0;
    virtual void rvaSlotD0()=0;
    virtual void rvaSlotD4()=0;
    virtual void rvaSlotD8()=0;
    virtual void rvaSlotDC()=0;
    virtual void rvaSlotE0()=0;
    virtual void rvaSlotE4()=0;
    virtual void rvaSlotE8()=0;
    virtual void rvaSlotEC()=0;
    virtual void rvaSlotF0()=0;
    virtual void rvaSlotF4()=0;
    virtual void rvaSlotF8()=0;
    virtual void rvaSlotFC()=0;
    virtual void rvaSlot100()=0;
    virtual void rvaSlot104()=0;
    virtual void rvaSlot108()=0;
    virtual void rvaSlot10C()=0;
    virtual void rvaSlot110()=0;
    virtual void rvaSlot114()=0;
    virtual void rvaSlot118()=0;
    virtual void rvaSlot11C()=0;
    virtual void rvaSlot120()=0;
    virtual void rvaSlot124()=0;
    virtual void rvaSlot128()=0;
    virtual void rvaSlot12C()=0;
    virtual void rvaSlot130()=0;
    virtual void rvaSlot134()=0;
    virtual void rvaSlot138()=0;
    virtual void rvaSlot13C()=0;
    virtual void rvaSlot140()=0;
    virtual void rvaSlot144()=0;
    virtual Real getAverageFPS()=0;
};
extern GameWindowManager* TheWindowManager;
extern GameText* TheGameText;
extern VictoryConditions* TheVictoryConditions;
extern NetworkInterface* TheNetwork;
extern Rva004E5DF0GameSpyInfo* TheGameSpyInfo;
extern GameResultsInterface* TheGameResultsQueue;
extern Display* TheDisplay;
struct Rva004E5DF0Stats
{
	Int id;                             // +0x000
	PerGeneralMap wins;                 // +0x004
	PerGeneralMap losses;               // +0x010
	PerGeneralMap currentWinStreaks;    // +0x01c
	PerGeneralMap currentLossStreaks;   // +0x028
	PerGeneralMap worstLossStreaks;     // +0x034
	PerGeneralMap bestWinStreaks;       // +0x040
	PerGeneralMap games;                // +0x04c
	PerGeneralMap duration;             // +0x058
	PerGeneralMap unitsKilled;          // +0x064
	PerGeneralMap unitsLost;            // +0x070
	PerGeneralMap unitsBuilt;           // +0x07c
	PerGeneralMap buildingsKilled;      // +0x088
	PerGeneralMap buildingsLost;        // +0x094
	PerGeneralMap buildingsBuilt;       // +0x0a0
	PerGeneralMap earnings;             // +0x0ac
	PerGeneralMap discons;              // +0x0b8
	PerGeneralMap desyncs;              // +0x0c4
	PerGeneralMap surrenders;           // +0x0d0
	PerGeneralMap gamesOf2p;            // +0x0dc
	PerGeneralMap gamesOf3p;            // +0x0e8
	PerGeneralMap gamesOf4p;            // +0x0f4
	PerGeneralMap gamesOf5p;            // +0x100
	PerGeneralMap gamesOf6p;            // +0x10c
	PerGeneralMap gamesOf7p;            // +0x118
	PerGeneralMap gamesOf8p;            // +0x124
	PerGeneralMap customGames;          // +0x130
	PerGeneralMap QMGames;              // +0x13c
	Int locale;                         // +0x148
	std::string dateCreated;            // +0x14c
	Int gamesAsRandom;                  // +0x158
	std::string options;                // +0x15c
	std::string systemSpec;             // +0x168
	Real lastFPS;                       // +0x174
	Int lastSide;                       // +0x178
	Int gamesInRowWithLastSide;         // +0x17c
	Int challengeMedals;                // +0x180
	Int battleHonors;                   // +0x184
	Int winsInARow;                     // +0x188
	Int maxWinsInARow;                  // +0x18c
	Int lossesInARow;                   // +0x190
	Int maxLossesInARow;                // +0x194
	Int gamesOn1_1_Ladder;              // +0x198
	Int gamesOn2_2_Ladder;              // +0x19c
	Int disconsInARow;                  // +0x1a0
	Int maxDisconsInARow;               // +0x1a4
	Int desyncsInARow;                  // +0x1a8
	Int maxDesyncsInARow;               // +0x1ac
	Int best1v1LadderRank;              // +0x1b0
	Int best2v2LadderRank;              // +0x1b4
	std::string lastLadderPlayed;       // +0x1b8
};

typedef char CheckResponseSize[sizeof(PSResponse)==0x1f0 ? 1:-1];
#include <bitset>
class PlayerList; extern PlayerList* ThePlayerList;
enum
{
	KINDOF_VEHICLE = 9,
	KINDOF_AIRCRAFT = 12
};

struct BfmeA1112
{
	public:
		enum BogusInitType { kInit = 0 };
		BfmeA1112() {}
		BfmeA1112(BogusInitType, Int bit) { m_bits.set(bit); }
		void clear() { m_bits.reset(); }
		void set(Int bit) { m_bits.set(bit); }

	private:
		_STL::bitset<192> m_bits;
};

struct BfmeB1112
{
	public:
		enum BogusInitType { kInit = 0 };
		BfmeB1112() {}
		BfmeB1112(BogusInitType, Int bit) { m_bits.set(bit); }
		void clear() { m_bits.reset(); }
		void set(Int bit) { m_bits.set(bit); }

	private:
		_STL::bitset<192> m_bits;
};

class BfmeV1112
{
public:
	Int bfmeGo1112A(BfmeA1112 validMask, BfmeB1112 invalidMask);

private:
	char m_pad[0x144];
	void *m_map;
	char m_tail[0x88];
};

static __declspec(noinline) void updateMPBattleHonors(Int &honors, PSPlayerStats &stats)
{
	Player *localPlayer = rvaField<Player*>(ThePlayerList,0xc);
	BfmeV1112 *s = (BfmeV1112*)localPlayer->getScoreKeeper();

	if (rvaField<Int>(&stats,0x188) >= 3)
		honors |= 2;
	if (rvaField<Int>(&stats,0x188) >= 10)
		honors |= 8;
	if (rvaField<Int>(&stats,0x188) >= 25)
		honors |= 0x10;

	if (rvaField<Int>(&stats,0x17c) >= 20 && rvaField<AsciiString>(localPlayer,0x28).compare("America") == 0)
		honors |= 0x20;
	if (rvaField<Int>(&stats,0x17c) >= 20 && rvaField<AsciiString>(localPlayer,0x28).compare("China") == 0)
		honors |= 0x40;
	if (rvaField<Int>(&stats,0x17c) >= 20 && rvaField<AsciiString>(localPlayer,0x28).compare("GLA") == 0)
		honors |= 0x200;

	BfmeA1112 validMask(BfmeA1112::kInit, KINDOF_VEHICLE);
	BfmeB1112 invalidMask(BfmeB1112::kInit, KINDOF_AIRCRAFT);
	if (s->bfmeGo1112A(validMask, invalidMask) >= 50)
		honors |= 0x80;

	validMask.clear();
	validMask.set(KINDOF_AIRCRAFT);
	invalidMask.clear();
	if (s->bfmeGo1112A(validMask, invalidMask) >= 20)
		honors |= 0x100;

	if (TheGameLogic->getFrame() / 5 / 60 < 5)
		honors |= 0x4000;
	if (TheGameLogic->getFrame() / 5 / 60 < 10)
		honors |= 0x8000;
}

typedef char CheckPSSize[sizeof(PSPlayerStats)==0x1c4 ? 1:-1];
typedef char CheckRequestSize[sizeof(PSRequest)==0x210 ? 1:-1];
void populatePlayerInfo( Player *player, Int pos)
{
	if(!player || pos > MAX_SLOTS)
		return;
	Color color = player->getPlayerColor();
	ScoreKeeper *scoreKpr = player->getScoreKeeper();
	if(!scoreKpr)
	{

		return;
	}
	AsciiString winName;
	UnicodeString winValue;
	GameWindow *win;

	winName.format("ScoreScreen.wnd:StaticTextPlayer%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	if(Rva012F4180)
	{
		GadgetStaticTextSetText(win, TheGameText->fetch("GUI:Player"));
	}
	else
		GadgetStaticTextSetText(win, player->getPlayerDisplayName());
	win->winHide(FALSE);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());

	winName.format("ScoreScreen.wnd:StaticTextObserver%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	win->winHide(TRUE);

	winName.format("ScoreScreen.wnd:StaticTextUnitsBuilt%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalUnitsBuilt());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextUnitsLost%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalUnitsLost());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextUnitsDestroyed%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalUnitsDestroyed());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextBuildingsBuilt%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalBuildingsBuilt());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextBuildingsLost%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalBuildingsLost());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextBuildingsDestroyed%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalBuildingsDestroyed());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextBuildingsDestroyed%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalBuildingsDestroyed());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:StaticTextResources%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	winValue.format(UnicodeString(L"%d"), scoreKpr->getTotalMoneyEarned());
	GadgetStaticTextSetText(win, winValue);
	win->winSetEnabledTextColors(color, win->winGetEnabledTextBorderColor());
	win->winHide(FALSE);

	winName.format("ScoreScreen.wnd:GameWindowWinner%d", pos);
	win =  TheWindowManager->winGetWindowFromId( Rva012F415C, TheNameKeyGenerator->nameToKey( winName ) );

	win->winHide(FALSE);

	const PlayerTemplate *fact = player->getPlayerTemplate();
	if(fact != NULL)
	{
		win->winSetEnabledImage(0, fact->getSideIconImage());
	}

	if ( Rva012F4134 == SCORESCREEN_SKIRMISH && player->isLocalPlayer() )
	{
		if (TheGameInfo->isSandbox() || !(TheVictoryConditions->isLocalAlliedDefeat() || TheVictoryConditions->isLocalAlliedVictory()))
		{

			if (player->isPlayerActive())
			{

				return;
			}
		}

        SkirmishPreferences prefs;
        SkirmishBattleHonors stats(prefs.getUserName());
        AsciiString side = fact->getSide();
        Real duration = TheVictoryConditions->getEndFrame() * (1.0f / 5.0f);
        stats.setTimePlayed(side, stats.getTimePlayed(side) + duration);
        if (TheVictoryConditions->isLocalAlliedVictory())
        {
            Bool anyEasy = FALSE, anyMedium = FALSE, anyBrutal = FALSE;
            Int numBrutal = 0;
            for (Int i=0; i<MAX_SLOTS; ++i)
            {
                const GameSlot *slot=TheGameInfo->getConstSlot(i);
                SlotState state=slot->getState();
                if (slot->isOccupied() && state==SLOT_EASY_AI) anyEasy=TRUE;
                if (slot->isOccupied() && state==SLOT_MED_AI) anyMedium=TRUE;
                if (slot->isOccupied() && state==SLOT_BRUTAL_AI) { anyBrutal=TRUE; ++numBrutal; }
            }
            if (TheGameInfo->_bfme_getMapIsOfficial()-1 == numBrutal) stats.setPoints(side,stats.getPoints(side)+4);
            else if(anyBrutal) stats.setPoints(side,stats.getPoints(side)+3);
            else if(anyMedium) stats.setPoints(side,stats.getPoints(side)+2);
            else if(anyEasy) stats.setPoints(side,stats.getPoints(side)+1);
            stats.setWins(side,stats.getWins(side)+1);
            stats.setWinStreak(side,stats.getWinStreak(side)+1);
            stats.setBestWinStreak(side,max(stats.getBestWinStreak(side),stats.getWinStreak(side)));
            stats.setOverallWinStreak(stats.getOverallWinStreak()+1);
            stats.setOverallBestWinStreak(max(stats.getOverallBestWinStreak(),stats.getOverallWinStreak()));
            stats.setLossStreak(side,0);
            stats.setOverallLossStreak(0);
            Int challengeMedals=stats.getChallengeMedals();
            updateChallengeMedals(challengeMedals);
            stats.setChallengeMedals(challengeMedals);
        }
        else
        {
            stats.setLosses(side,stats.getLosses(side)+1);
            stats.setLossStreak(side,stats.getLossStreak(side)+1);
            stats.setWorstLossStreak(side,max(stats.getWorstLossStreak(side),stats.getLossStreak(side)));
            stats.setOverallLossStreak(stats.getOverallLossStreak()+1);
            stats.setOverallWorstLossStreak(max(stats.getOverallWorstLossStreak(),stats.getOverallLossStreak()));
            stats.setWinStreak(side,0);
            stats.setOverallWinStreak(0);
        }

		AsciiString lastGeneral = stats.getLastGeneral();
		stats.setLastGeneral(player->getPlayerTemplate()->getSide());
		if (lastGeneral.compare(stats.getLastGeneral()) != 0)
		{
			stats.setNumGamesLoyal(0);
		}
		else
		{
			stats.setNumGamesLoyal(stats.getNumGamesLoyal()+1);
		}

		stats.write();
	}

	if ( Rva012F4134 == SCORESCREEN_INTERNET )
	{

		Int localID = TheGameSpyInfo->getLocalProfileID();
		if (localID)
		{
			Int localSlotNum = TheGameSpyGame->getLocalSlotNum();
			if (player->isLocalPlayer())
			{
				GameSpyGameSlot *localSlot = TheGameSpyGame->getGameSpySlot(localSlotNum);
				if (localSlot)
				{
					if (TheVictoryConditions->amIObserver())
					{

						return;
					}

					PSPlayerStats stats = ((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->findPlayerStatsByID(localID);
                    Rva004E5DF0Stats &statsView = *(Rva004E5DF0Stats*)&stats;

					UnsignedInt latestHumanInGame = 0;
					UnsignedInt lastFrameOfGame = 0;
					Bool gameEndedInDisconnect = TRUE;
					Bool sawAnyDisconnects = FALSE;
					Bool anyNonAI = FALSE;

					for (Int i=0; i<MAX_SLOTS; ++i)
					{
						const GameSlot *slot = TheGameInfo->getConstSlot(i);
						if (slot->isOccupied() && i != localSlotNum )
						{
							if (!slot->isAI())
								anyNonAI = TRUE;
						}
						if (slot->isOccupied())
						{
							lastFrameOfGame = max(lastFrameOfGame, slot->lastFrameInGame());
						}
						if (slot->isHuman())
						{
							if (i != localSlotNum)
							{
								latestHumanInGame = max(latestHumanInGame, slot->lastFrameInGame());
							}
						}
					}

					for (i=0; i<MAX_SLOTS; ++i)
					{
						const GameSlot *slot = TheGameInfo->getConstSlot(i);

						if (slot->isOccupied() && slot->disconnected())
						{

							sawAnyDisconnects = TRUE;
						}
						if (slot->isOccupied() && !slot->disconnected() && i != localSlotNum &&
							(slot->isAI() || (slot->lastFrameInGame() >= lastFrameOfGame-1)))
						{

							gameEndedInDisconnect = FALSE;
						}
					}

					if (!sawAnyDisconnects)
					{

						gameEndedInDisconnect = FALSE;
					}

					if (gameEndedInDisconnect)
					{
						if (latestHumanInGame == TheNetwork->getPingFrame())
						{

							if (TheNetwork->getPingsRecieved() < max(1, TheNetwork->getPingsSent()/2)) 
							{

							}
							else
							{

								gameEndedInDisconnect = FALSE;
							}
						}
						else
						{

						}
					}

					if (!anyNonAI)
					{

						return;
					}

					Bool sawEndOfGame = FALSE;
					if (TheVictoryConditions->isLocalAlliedDefeat() || TheVictoryConditions->isLocalAlliedVictory())
					{
						sawEndOfGame = TRUE;
					}
					if (TheVictoryConditions->isLocalDefeat())
					{
						sawEndOfGame = TRUE;
					}
					if (TheGameLogic->sawCRCMismatch() || gameEndedInDisconnect)
					{
						sawEndOfGame = TRUE;
					}
					if (!sawEndOfGame)
					{

						return;
					}

					if (TheGameSpyGame->getLadderPort() && TheGameSpyGame->getLadderIP().isNotEmpty())
					{
						GameResultsRequest gameResReq;
						gameResReq.hostname = TheGameSpyGame->getLadderIP().str();
						gameResReq.port = TheGameSpyGame->getLadderPort();
						gameResReq.results = TheGameSpyGame->generateLadderGameResultsPacket().str();

						if (TheGameResultsQueue)
						{
							TheGameResultsQueue->addRequest(gameResReq);
						}
					}
					if (TheVictoryConditions->getEndFrame() < 125 && TheVictoryConditions->getEndFrame())
					{
 						return;
					}

					AsciiString resultsPacket = TheGameSpyGame->generateGameSpyGameResultsPacket(gameEndedInDisconnect);

					PSRequest grReq;
					grReq.requestType = PSRequest::PSREQUEST_SENDGAMERESTOGAMESPY;
					grReq.results = resultsPacket.str();
					((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->addRequest(grReq);

					Int ptIdx;
					const PlayerTemplate *myTemplate = player->getPlayerTemplate();

					for (ptIdx = 0; ptIdx < ThePlayerTemplateStore->getPlayerTemplateCount(); ++ptIdx)
					{
						const PlayerTemplate *nthTemplate = ThePlayerTemplateStore->getNthPlayerTemplate(ptIdx);

						if (nthTemplate == myTemplate)
						{
							break;
						}
					}

					if (statsView.id == 0)
					{

						if (gameEndedInDisconnect || TheGameLogic->sawCRCMismatch())
						{

							PSRequest req;
							req.requestType = PSRequest::PSREQUEST_UPDATEPLAYERSTATS;
							req.email = TheGameSpyInfo->getLocalEmail().str();
							req.nick = TheGameSpyInfo->getLocalBaseName().str();
							req.password = "";
							req.player = stats;
							req.addDesync = TheGameLogic->sawCRCMismatch();
 							req.addDiscon = gameEndedInDisconnect;
							req.lastHouse = ptIdx;
							((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->addRequest(req);
						}

						return;
					}

					if (TheGameLogic->sawCRCMismatch())
					{
						++statsView.desyncs[ptIdx];
					}
					else if (gameEndedInDisconnect)
					{
						++statsView.discons[ptIdx];
					}
					else if (TheVictoryConditions->isLocalAlliedDefeat() || !TheVictoryConditions->getEndFrame())
					{
						++statsView.losses[ptIdx];
					}
					else
					{
						++statsView.wins[ptIdx];
					}

					ScoreKeeper *s = player->getScoreKeeper();
					statsView.buildingsBuilt[ptIdx] += s->getTotalBuildingsBuilt();
					statsView.buildingsKilled[ptIdx] += s->getTotalBuildingsDestroyed();
					statsView.buildingsLost[ptIdx] += s->getTotalBuildingsLost();

					if (TheGameSpyGame->isQMGame())
					{
						statsView.QMGames[ptIdx]++;
					}
					else
					{
						statsView.customGames[ptIdx]++;
					}

					if (TheGameLogic->sawCRCMismatch())
					{
						statsView.lossesInARow = 0;
						statsView.desyncsInARow++;
						statsView.disconsInARow = 0;
						statsView.winsInARow = 0;
						statsView.maxDesyncsInARow = max(statsView.desyncsInARow, statsView.maxDesyncsInARow);
					}
					else if (gameEndedInDisconnect)
					{
						statsView.lossesInARow = 0;
						statsView.desyncsInARow = 0;
						statsView.disconsInARow++;
						statsView.winsInARow = 0;
						statsView.maxDisconsInARow = max(statsView.disconsInARow, statsView.maxDisconsInARow);
					}
					else if (TheVictoryConditions->isLocalAlliedVictory())
					{
						statsView.lossesInARow = 0;
						statsView.desyncsInARow = 0;
						statsView.disconsInARow = 0;
						statsView.winsInARow++;
						statsView.maxWinsInARow = max(statsView.winsInARow, statsView.maxWinsInARow);
					}
					else
					{
						statsView.lossesInARow++;
						statsView.desyncsInARow = 0;
						statsView.disconsInARow = 0;
						statsView.winsInARow = 0;
						statsView.maxLossesInARow = max(statsView.lossesInARow, statsView.maxLossesInARow);
					}

					statsView.earnings[ptIdx] += s->getTotalMoneyEarned();
					statsView.duration[ptIdx] += TheGameLogic->getFrame() / 5 / 60; 
					statsView.games[ptIdx]++;

					statsView.gamesAsRandom += (localSlot->getOriginalPlayerTemplate() == PLAYERTEMPLATE_RANDOM);

					if (statsView.lastSide != ptIdx)
						statsView.gamesInRowWithLastSide = 0;
					statsView.gamesInRowWithLastSide++;
					statsView.lastSide = ptIdx;

					Int gameSize = 0;
					for (i=0; i<MAX_SLOTS; ++i)
					{
						if (TheGameSpyGame->getConstSlot(i)->isOccupied() && TheGameSpyGame->getConstSlot(i)->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
							++gameSize;
					}
					switch (gameSize)
					{
					case 2:
						statsView.gamesOf2p[ptIdx]++;
						break;
					case 3:
						statsView.gamesOf3p[ptIdx]++;
						break;
					case 4:
						statsView.gamesOf4p[ptIdx]++;
						break;
					case 5:
						statsView.gamesOf5p[ptIdx]++;
						break;
					case 6:
						statsView.gamesOf6p[ptIdx]++;
						break;
					case 7:
						statsView.gamesOf7p[ptIdx]++;
						break;
					case 8:
						statsView.gamesOf8p[ptIdx]++;
						break;
					default:
						return; 
					}

					statsView.lastFPS = TheDisplay->getAverageFPS(); 

					statsView.surrenders[ptIdx] += TheGameInfo->haveWeSurrendered()  || !TheVictoryConditions->getEndFrame();

					AsciiString systemSpec;
					systemSpec.format("LOD%d", Rva012ED5AC->getIdealStaticGameDetail());
					const char *spec = systemSpec.str();
                    const char *endSpec = spec + strlen(spec);
                    statsView.systemSpec.assign(spec, endSpec);

					statsView.unitsBuilt[ptIdx] += s->getTotalUnitsBuilt();
					statsView.unitsKilled[ptIdx] += s->getTotalUnitsDestroyed();
					statsView.unitsLost[ptIdx] += s->getTotalUnitsLost();

					if (!TheGameLogic->sawCRCMismatch() && !gameEndedInDisconnect && !TheVictoryConditions->isLocalAlliedDefeat() && TheVictoryConditions->getEndFrame())
					{
						updateMPBattleHonors(statsView.battleHonors, stats);
						updateChallengeMedals(statsView.challengeMedals);
					}

					PSRequest req;
					req.requestType = PSRequest::PSREQUEST_UPDATEPLAYERSTATS;
					req.email = TheGameSpyInfo->getLocalEmail().str();
					req.nick = TheGameSpyInfo->getLocalBaseName().str();
					req.password = TheGameSpyInfo->getLocalPassword().str();
					req.player = stats;
					req.addDesync = TheGameLogic->sawCRCMismatch();
 					req.addDiscon = gameEndedInDisconnect;
					req.lastHouse = ptIdx;
					((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->addRequest(req);
					((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->trackPlayerStats(stats);

					PSResponse newResp;
					newResp.responseType = PSResponse::PSRESPONSE_PLAYERSTATS;
					newResp.player = stats;
					((Rva004E5DF0Queue*)TheGameSpyPSMessageQueue)->addResponse(newResp);

					GameSpyMiscPreferences mPref;
					mPref.setCachedStats(GameSpyPSMessageQueueInterface::formatPlayerKVPairs(stats).c_str());
					mPref.write();
				}
			}
		}
	}
}

