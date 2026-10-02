// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The matched startPings body at 0x005019A0 proves the loop and request ABI.
// This namespace names the duplicate retail implementation at 0x00550500.

#include <list>
#include <string>
#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		const StringBase<char>::Header *data = m_data;
		return data ? data->data : "";
	}

};

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface() {}
	virtual std::list<AsciiString> getPingServers() = 0;
	virtual Int getNumPingRepetitions() = 0;
	virtual Int getPingTimeoutInMs() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

class PingRequest
{
public:
	_STL::string hostname;
	Int repetitions;
	Int timeout;
};

class PingerInterface
{
public:
	virtual ~PingerInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual Bool areThreadsRunning() = 0;
	virtual void addRequest(const PingRequest &request) = 0;
};

extern PingerInterface *ThePinger;

namespace Rva00550500
{
	void startPings()
	{
		std::list<AsciiString> pingServers = TheGameSpyConfig->getPingServers();
		Int timeout = TheGameSpyConfig->getPingTimeoutInMs();
		Int reps = TheGameSpyConfig->getNumPingRepetitions();

		for (std::list<AsciiString>::const_iterator it = pingServers.begin(); it != pingServers.end(); ++it)
		{
			AsciiString pingServer = *it;
			PingRequest req;
			req.hostname = pingServer.str();
			req.repetitions = reps;
			req.timeout = timeout;
			ThePinger->addRequest(req);
		}
	}
}
