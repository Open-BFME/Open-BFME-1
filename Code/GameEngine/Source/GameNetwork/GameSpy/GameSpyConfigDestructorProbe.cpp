// stlport
// BFME GameSpyConfig layout probe for the 0x00629F90 destructor body.

#include <list>
#include <set>
#include <vector>

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class GameSpyConfigInterfaceDtorBase
{
public:
	virtual ~GameSpyConfigInterfaceDtorBase() {}
};

class BfmeGameSpyConfigDestructor : public GameSpyConfigInterfaceDtorBase
{
public:
	virtual ~BfmeGameSpyConfigDestructor();

private:
	std::list<AsciiString> m_pingServers;
	int m_pingReps;
	int m_pingTimeout;
	int m_pingCutoffGood;
	int m_pingCutoffBad;

	int m_natRetryInterval;
	int m_natMaxManglerRetries;
	int m_natManglerRetryInterval;
	int m_natKeepaliveInterval;
	int m_natPortTimeout;
	int m_natRoundTimeout;

	std::vector<AsciiString> m_manglerHosts;
	std::vector<unsigned short> m_manglerPorts;

	std::list<AsciiString> m_qmMaps;
	int m_qmBotID;
	int m_qmChannel;
	unsigned char m_restrictGamesToLobby;

	std::set<int> m_vip;
	int m_rankPoints[10];
	AsciiString m_leftoverConfig;
};

BfmeGameSpyConfigDestructor::~BfmeGameSpyConfigDestructor()
{
}

