// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Keep the factory's AsciiString ABI view local to this translation unit.
#define AsciiString BfmeAsciiString
#include "Common/AsciiString.h"
#undef AsciiString

class BfmeStringArgBase
{
	friend class AsciiString;

	private:
	BfmeStringArgBase(const BfmeStringArgBase& other);
	~BfmeStringArgBase();
};

#include "ascii_string.h"

#include "PreRTS.h"

#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/RankPointValue.h"

class GameSpyConfig : public GameSpyConfigInterface
{
public:
	GameSpyConfig(AsciiString config);
	~GameSpyConfig() {}

	virtual std::list<AsciiString> getPingServers(void);
	virtual Int getNumPingRepetitions(void);
	virtual Int getPingTimeoutInMs(void);
	virtual Int getPingCutoffGood(void);
	virtual Int getPingCutoffBad(void);
	virtual std::list<AsciiString> getQMMaps(void);
	virtual Int getQMBotID(void);
	virtual Int getQMChannel(void);
	virtual void setQMChannel(Int channel);
	virtual Int getPointsForRank(Int rank);
	virtual Bool isPlayerVIP(Int id);
	virtual Bool getManglerLocation(Int index, AsciiString& host, UnsignedShort& port);
	virtual AsciiString getLeftoverConfig(void);
	virtual Int getTimeBetweenRetries(void);
	virtual Int getMaxManglerRetries(void);
	virtual time_t getRetryInterval(void);
	virtual time_t getKeepaliveInterval(void);
	virtual time_t getPortTimeout(void);
	virtual time_t getRoundTimeout(void);
	virtual Bool restrictGamesToLobby(void);

protected:
	std::list<AsciiString> m_pingServers;
	Int m_pingReps;
	Int m_pingTimeout;
	Int m_pingCutoffGood;
	Int m_pingCutoffBad;

	Int m_natRetryInterval;
	Int m_natMaxManglerRetries;
	time_t m_natManglerRetryInterval;
	time_t m_natKeepaliveInterval;
	time_t m_natPortTimeout;
	time_t m_natRoundTimeout;

	std::vector<AsciiString> m_manglerHosts;
	std::vector<UnsignedShort> m_manglerPorts;

	std::list<AsciiString> m_qmMaps;
	Int m_qmBotID;
	Int m_qmChannel;

	Bool m_restrictGamesToLobby;

	std::set<Int> m_vip;

	Int m_rankPoints[MAX_RANKS];

	AsciiString m_leftoverConfig;
};

GameSpyConfigInterface* GameSpyConfigInterface::create(AsciiString config)
{
	return NEW GameSpyConfig(config);
}
